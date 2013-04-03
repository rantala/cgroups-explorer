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

#ifndef CGROUPTASKMODEL_H
#define CGROUPTASKMODEL_H

#include <QStringListModel>

class CgroupTaskModel : public QStringListModel
{
	Q_OBJECT
	Q_PROPERTY(QString cgroup
			READ cgroup
			WRITE setCgroup
			NOTIFY cgroupChanged)

public:
	enum ModelRoles {
		TitleRole = Qt::UserRole + 1,
		SubtitleRole
	};
	CgroupTaskModel(QObject *parent = 0);
	Q_INVOKABLE QString cgroup() const;
	Q_INVOKABLE void setCgroup(const QString &newCgroup);
	Q_INVOKABLE void update();
	QVariant data(const QModelIndex &index, int role) const;

signals:
	void cgroupChanged();

private:
	QString _cgroup;
};

#endif /* CGROUPTASKMODEL_H */
