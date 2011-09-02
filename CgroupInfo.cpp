#include "CgroupInfo.h"
#include <QDebug>
#include <QString>
#include <QStringList>

QString CgroupInfo::cgroup() const
{
	return _cgroup;
}

int CgroupInfo::memoryUsage() const
{
	int usage = -1;
	FILE *fp = NULL;
	QString cg, memlimit;
	cg = cgroup();
	if (cg.isEmpty())
		goto out;
	memlimit = QLatin1String("/syspart") + cg
		+ QLatin1String("/memory.usage_in_bytes");
	fp = fopen(memlimit.toAscii(), "r");
	if (!fp)
		goto out;
	if (fscanf(fp, "%d", &usage) != 1)
		goto out;
out:
	if (fp)
		fclose(fp);
	//qDebug() << Q_FUNC_INFO << ":" << usage;
	return usage;
}

int CgroupInfo::swapUsage() const
{
	//qDebug() << Q_FUNC_INFO;
	int swapUsage = -1;
	int memswUsage = -1;
	FILE *fp = NULL;
	QString cg, memlimit;
	cg = cgroup();
	if (cg.isEmpty())
		goto out;
	memlimit = QLatin1String("/syspart") + cg
		+ QLatin1String("/memory.memsw.usage_in_bytes");
	fp = fopen(memlimit.toAscii(), "r");
	if (!fp) {
		qDebug() << Q_FUNC_INFO << ": unable to open" << memlimit;
		goto out;
	}
	if (fscanf(fp, "%d", &memswUsage) != 1) {
		qDebug() << Q_FUNC_INFO << ": unable to read integer.";
		goto out;
	}
	swapUsage = memswUsage - memoryUsage();
	swapUsage = qMax(0, swapUsage);
out:
	if (fp)
		fclose(fp);
	//qDebug() << Q_FUNC_INFO << ":" << swapUsage;
	return swapUsage;
}

int CgroupInfo::memoryLimit() const
{
	//qDebug() << Q_FUNC_INFO;
	unsigned long long limit = -1;
	FILE *fp = NULL;
	QString cg, memlimit;
	cg = cgroup();
	if (cg.isEmpty())
		goto out;
	memlimit = QLatin1String("/syspart") + cg
		+ QLatin1String("/memory.limit_in_bytes");
	fp = fopen(memlimit.toAscii(), "r");
	if (!fp) {
		qDebug() << Q_FUNC_INFO << ": unable to open" << memlimit;
		goto out;
	}
	if (fscanf(fp, "%llu", &limit) != 1) {
		qDebug() << Q_FUNC_INFO << ": unable to read integer.";
		goto out;
	}
out:
	if (fp)
		fclose(fp);
	//qDebug() << Q_FUNC_INFO << ":" << limit;
	if (limit == (unsigned long long)-1)
		return -1;
	if (limit > INT_MAX)
		return -1;
	return (int)limit;
}

int CgroupInfo::taskCount() const
{
	//qDebug() << Q_FUNC_INFO;
	static char *line = NULL;
	static size_t line_n = 0;
	int task_count = -1;
	FILE *fp = NULL;
	QString cg, fn;
	cg = cgroup();
	if (cg.isEmpty())
		goto out;
	fn = QLatin1String("/syspart") + cg + QLatin1String("/cgroup.procs");
	fp = fopen(fn.toAscii(), "r");
	if (!fp) {
		qDebug() << Q_FUNC_INFO << ": unable to open" << fn;
		goto out;
	}
	task_count = 0;
	while (getline(&line, &line_n, fp) != -1)
		++task_count;
out:
	if (fp)
		fclose(fp);
	//qDebug() << Q_FUNC_INFO << ":" << task_count;
	return task_count;
}

void CgroupInfo::update()
{
	emit memoryUsageChanged();
	emit swapUsageChanged();
	emit memoryLimitChanged();
}

void CgroupInfo::setCgroup(const QString &newCgroup)
{
	if (_cgroup != newCgroup) {
		_cgroup = newCgroup;
		emit cgroupChanged();
	}
}
