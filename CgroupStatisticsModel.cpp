#include "CgroupStatisticsModel.h"
#include <QDebug>
#include <QFile>
#include <QHash>

static QStringList
getStats(const QString &group)
{
	QStringList result;
	static char *line = NULL;
	static size_t line_n = 0;
	FILE *fp = NULL;
	QString fn;
	if (group.isEmpty())
		goto out;
	fn = QLatin1String("/syspart") + group + QLatin1String("/memory.stat");
	fp = fopen(fn.toAscii(), "r");
	if (!fp) {
		//qDebug() << Q_FUNC_INFO << ": unable to open" << fn;
		goto out;
	}
	while (getline(&line, &line_n, fp) != -1) {
		QString l(line);
		l.chop(1);
		//qDebug() << Q_FUNC_INFO << ":" << l;
		QStringList keyval = l.split(' ');
		QString key = keyval[0];
		qulonglong val = keyval[1].toULongLong();
		if (val == (qulonglong)-1) {
			result << QObject::tr("%1: %2").arg(key).arg(": unlimited");
		} else if (key == "pgpgin" or
		           key == "pgpgout" or
		           key == "total_pgpgin" or
		           key == "total_pgpgout") {
			result << QObject::tr("%1: %2").arg(key).arg(val);
		} else {
			result << QObject::tr("%1: %2 kB").arg(key).arg(val/1024);
		}
	}
out:
	if (fp)
		fclose(fp);
	//qDebug() << Q_FUNC_INFO << ":" << group << "=>" << result;
	return result;
}

CgroupStatisticsModel::CgroupStatisticsModel(QObject *parent)
	: QStringListModel(parent)
{
	QHash<int, QByteArray> roles;
	roles[TitleRole] = "title";
	roles[SubtitleRole] = "subtitle";
	setRoleNames(roles);
}

QString CgroupStatisticsModel::cgroup() const
{
	return _cgroup;
}

void CgroupStatisticsModel::setCgroup(const QString &newCgroup)
{
	//qDebug() << Q_FUNC_INFO << ":" << newCgroup;
	if (newCgroup == _cgroup)
		return;
	_cgroup = newCgroup;
	emit cgroupChanged();
	update();
}

void CgroupStatisticsModel::update()
{
	setStringList(getStats(_cgroup));
}

static QHash<QString, QString> *cgroupSubtitles;

static const QString &cgroupSubtitle(const QString &group)
{
	if (!cgroupSubtitles) {
		cgroupSubtitles = new QHash<QString, QString>;
		(*cgroupSubtitles)["cache"] = "Page cache memory.";
		(*cgroupSubtitles)["rss"] = "Anonymous + swap cache memory.";
		(*cgroupSubtitles)["mapped_file"] = "Mapped files (includes tmpfs/shmem).";
		(*cgroupSubtitles)["pgpgin"] = "Number of pages paged in.";
		(*cgroupSubtitles)["pgpgout"] = "Number of pages paged out.";
		(*cgroupSubtitles)["swap"] = "Swap usage (in-memory compressed).";
		(*cgroupSubtitles)["inactive_anon"] = "Anonymous + swap cache on inactive LRU list.";
		(*cgroupSubtitles)["active_anon"] = "Anonymous + swap cache on active LRU list.";
		(*cgroupSubtitles)["inactive_file"] = "File-backed memory on inactive LRU list.";
		(*cgroupSubtitles)["active_file"] = "File-backed memory on active LRU list.";
		(*cgroupSubtitles)["unevictable"] = "Non-reclaimable memory (memory locked et. al.).";
		(*cgroupSubtitles)["hierarchical_memory_limit"] = "Memory limit with respect to group hierarchy.";
		(*cgroupSubtitles)["hierarchical_memsw_limit"] = "Memory + swap limit with respect to group hierarchy.";
		(*cgroupSubtitles)["total_cache"] = "Sum of child group's 'cache'.";
		(*cgroupSubtitles)["total_rss"] = "Sum of child group's 'rss'.";
		(*cgroupSubtitles)["total_mapped_file"] = "Sum of child group's 'mapped_file'.";
		(*cgroupSubtitles)["total_pgpgin"] = "Sum of child group's 'pgpgin'.";
		(*cgroupSubtitles)["total_pgpgout"] = "Sum of child group's 'pgpgout'.";
		(*cgroupSubtitles)["total_swap"] = "Sum of child group's 'swap'.";
		(*cgroupSubtitles)["total_inactive_anon"] = "Sum of child group's 'inactive_anon'.";
		(*cgroupSubtitles)["total_active_anon"] = "Sum of child group's 'active_anon'.";
		(*cgroupSubtitles)["total_inactive_file"] = "Sum of child group's 'inactive_file'.";
		(*cgroupSubtitles)["total_active_file"] = "Sum of child group's 'active_file'.";
		(*cgroupSubtitles)["total_unevictable"] = "Sum of child group's 'unevictable'.";
	}
	return (*cgroupSubtitles)[group];
}

QVariant CgroupStatisticsModel::data(const QModelIndex &index, int role) const
{
	if (role == TitleRole) {
		return QStringListModel::data(index, Qt::DisplayRole);
	} else if (role == SubtitleRole) {
		QString keyval = QStringListModel::data(index, Qt::DisplayRole).toString();
		QString key = keyval.split(':')[0];
		return cgroupSubtitle(key);
	} else {
		return QStringListModel::data(index, role);
	}
}
