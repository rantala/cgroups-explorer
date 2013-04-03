/*
 * Copyright (C) 2011 Tommi Rantala <tt.rantala@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.
 */

#include "CgroupTaskModel.h"
#include <QDebug>
#include <QFile>
#include <QHash>

static QStringList
getTasks(const QString &group)
{
	QStringList result;
	static char *line = NULL;
	static size_t line_n = 0;
	FILE *fp = NULL;
	QString fn, task;
	if (group.isEmpty())
		goto out;
	fn = QLatin1String("/syspart") + group + QLatin1String("/cgroup.procs");
	fp = fopen(fn.toAscii(), "r");
	if (!fp) {
		qDebug() << Q_FUNC_INFO << ": unable to open" << fn;
		goto out;
	}
	while (getline(&line, &line_n, fp) != -1) {
		task = line;
		task.chop(1);
		result << task;
	}
out:
	if (fp)
		fclose(fp);
	//qDebug() << Q_FUNC_INFO << ":" << group << "=>" << result;
	return result;
}

CgroupTaskModel::CgroupTaskModel(QObject *parent)
	: QStringListModel(parent)
{
	QHash<int, QByteArray> roles;
	roles[TitleRole] = "title";
	roles[SubtitleRole] = "subtitle";
	setRoleNames(roles);
}

QString CgroupTaskModel::cgroup() const
{
	return _cgroup;
}

void CgroupTaskModel::setCgroup(const QString &newCgroup)
{
	if (newCgroup == _cgroup)
		return;
	_cgroup = newCgroup;
	emit cgroupChanged();
	update();
}

void CgroupTaskModel::update()
{
	setStringList(getTasks(_cgroup));
}

QVariant CgroupTaskModel::data(const QModelIndex &index, int role) const
{
	if (role == TitleRole) {
		QString pid = QStringListModel::data(index, Qt::DisplayRole).toString();
		if (pid.isEmpty())
			return QVariant();
		QFile cmdline("/proc/" + pid + "/cmdline");
		if (!cmdline.open(QIODevice::ReadOnly))
			return pid;
		QByteArray cmd = cmdline.readAll();
		cmdline.close();
		cmd.replace('\0', ' ');
		if (cmd.isEmpty()) {
			QFile stat("/proc/" + pid + "/stat");
			if (!stat.open(QIODevice::ReadOnly))
				return pid;
			cmd = stat.readAll();
			stat.close();
			int slice_start = cmd.indexOf('(');
			int slice_end = cmd.lastIndexOf(')');
			cmd.remove(slice_end, cmd.size());
			cmd.remove(0, slice_start+1);
			cmd = '[' + cmd + ']';
		}
		return cmd;
	} else if (role == SubtitleRole) {
		QString pid = QStringListModel::data(index, Qt::DisplayRole).toString();
		if (pid.isEmpty())
			return QVariant();
		return tr("PID: %1").arg(pid);
	} else {
		return QStringListModel::data(index, role);
	}
}
