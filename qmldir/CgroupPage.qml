import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0
import rantala.cgroups 1.0

Page {
	id: mainpage
	property string groupName
	property string groupNameForHeader

	function update() {
		taskTab.update();
		statisticsTab.update();
	}

	tools: ToolBarLayout {
		ToolIcon {
			iconId: "toolbar-back";
			onClicked: pageStack.pop();
		}
		ButtonRow {
			platformStyle: TabButtonStyle { }
			TabButton {
				text: qsTr("Processes")
				tab: taskTab
			}
			TabButton {
				text: qsTr("Statistics")
				tab: statisticsTab
			}
		}
	}

	TabGroup {
		currentTab: taskTab
		CgroupTaskTab {
			id: taskTab
			groupName: mainpage.groupName
			groupNameForHeader: mainpage.groupNameForHeader
			width: mainpage.width
			anchors.fill: parent
		}
		CgroupStatisticsTab {
			id: statisticsTab
			groupName: mainpage.groupName
			groupNameForHeader: mainpage.groupNameForHeader
			width: mainpage.width
			anchors.fill: parent
		}
	}
}
