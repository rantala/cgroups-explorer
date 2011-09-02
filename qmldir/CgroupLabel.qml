import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0
import rantala.cgroups 1.0
import "file:///usr/lib/qt4/imports/com/nokia/meego/UIConstants.js" as UI

Item {
	id: root
	property string groupName
	property string groupNameForHeader: groupName
	width: parent.width
	height: contentColumn.height
	function update() {
		cgroupInfo.update();
	}
	Column {
		id: contentColumn
		anchors.margins: 16
		width: parent.width
		spacing: 3
		CgroupInfo {
			id: cgroupInfo
			cgroup: groupName
		}
		Connections {
			target: platformWindow
			onActiveChanged: cgroupInfo.update();
		}
		Label {
			text: groupName
			width: parent.width
			font.pixelSize: UI.FONT_LARGE
		}
		/*ProgressBar {
			width: parent.width
			maximumValue: 100
			minimumValue: 0
			value: Math.floor(100 * (cgroupInfo.memoryUsage / cgroupInfo.memoryLimit))
			visible: cgroupInfo.memoruUsage != -1 && cgroupInfo.memoryLimit != -1
		}*/
		Label {
			width: parent.width
			visible: cgroupInfo.memoruUsage != -1 && cgroupInfo.memoryLimit == -1
			text: qsTr("Memory usage: <b>%1&nbsp;MB</b>")
				.arg(Math.floor(cgroupInfo.memoryUsage / 1024 / 1024))
		}
		Label {
			width: parent.width
			visible: cgroupInfo.memoruUsage != -1 && cgroupInfo.memoryLimit != -1
			text: qsTr("Memory: <b>%1&nbsp;MB</b> out of <b>%2&nbsp;MB</b> (%3%)")
				.arg(Math.floor(cgroupInfo.memoryUsage / 1024 / 1024))
				.arg(Math.floor(cgroupInfo.memoryLimit / 1024 / 1024))
				.arg(Math.floor(100 * (cgroupInfo.memoryUsage / cgroupInfo.memoryLimit)))
		}
		Label {
			width: parent.width
			visible: cgroupInfo.swapUsage != -1
			text: qsTr("Swap usage: <b>%1&nbsp;MB</b>")
				.arg(Math.floor(cgroupInfo.swapUsage / 1024 / 1024))
		}
		Label {
			width: parent.width
			visible: cgroupInfo.taskCount != -1
			text: qsTr("Tasks: <b>%1</b>")
				.arg(cgroupInfo.taskCount)
		}
	}
	MouseArea {
		width: contentColumn.width
		height: contentColumn.height
		enabled: cgroupInfo.taskCount > 0
		onClicked: {
			/*
			pageStack.push(cgroupPage);
			cgroupPage.update();
			*/

			var component = Qt.createComponent("CgroupPage.qml");
			var cgroupPage = component.createObject(parent,
				{ groupName: root.groupName,
				  groupNameForHeader: root.groupNameForHeader });
			pageStack.push(cgroupPage);
		}
	}
	/*
	CgroupPage {
		id: cgroupPage
		groupName: root.groupName
		groupNameForHeader: root.groupNameForHeader
	}
	*/
}
