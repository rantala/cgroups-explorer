#ifndef CGROUPSTATISTICSMODEL_H
#define CGROUPSTATISTICSMODEL_H

#include <QStringListModel>

class CgroupStatisticsModel : public QStringListModel
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
	CgroupStatisticsModel(QObject *parent = 0);
	Q_INVOKABLE QString cgroup() const;
	Q_INVOKABLE void setCgroup(const QString &newCgroup);
	Q_INVOKABLE void update();
	QVariant data(const QModelIndex &index, int role) const;

signals:
	void cgroupChanged();

private:
	QString _cgroup;
};

#endif /* CGROUPSTATISTICSMODEL_H */
