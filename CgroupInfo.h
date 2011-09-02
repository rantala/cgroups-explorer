#ifndef CGROUPINFO_H
#define CGROUPINFO_H

#include <QObject>

class CgroupInfo : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString cgroup
			READ cgroup
			WRITE setCgroup
			NOTIFY cgroupChanged)
	Q_PROPERTY(int memoryUsage
			READ memoryUsage
			NOTIFY memoryUsageChanged)
	Q_PROPERTY(int swapUsage
			READ swapUsage
			NOTIFY swapUsageChanged)
	Q_PROPERTY(int memoryLimit
			READ memoryLimit
			NOTIFY memoryLimitChanged)
	Q_PROPERTY(int taskCount
			READ taskCount
			NOTIFY taskCountChanged)

public:
	CgroupInfo(QObject *parent = 0) : QObject(parent) {}
	~CgroupInfo() {}
	Q_INVOKABLE QString cgroup() const;
	Q_INVOKABLE void setCgroup(const QString &newCgroup);
	Q_INVOKABLE void update();
	int memoryUsage() const;
	int swapUsage() const;
	int memoryLimit() const;
	int taskCount() const;

signals:
	void cgroupChanged();
	void memoryUsageChanged();
	void swapUsageChanged();
	void memoryLimitChanged();
	void taskCountChanged();

private:
	QString _cgroup;
};

#endif /* CGROUPINFO_H */
