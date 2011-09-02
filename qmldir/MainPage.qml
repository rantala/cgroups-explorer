import QtQuick 1.1
import com.nokia.meego 1.0
import rantala.cgroups 1.0
import "file:///usr/lib/qt4/imports/com/nokia/meego/UIConstants.js" as UI

Page {
	id: mainpage
	anchors.bottomMargin: UI.DEFAULT_MARGIN
	function update() {
		cg1.update(); cg2.update(); cg3.update(); cg4.update();
		cg5.update(); cg6.update(); cg7.update();
	}
	Header { id: header; text: "Cgroups Explorer" }
	Flickable {
		anchors.top: header.bottom
		x: UI.DEFAULT_MARGIN
		width: parent.width - 2*UI.DEFAULT_MARGIN
		height: parent.height - header.height
		contentHeight: content.height
		flickableDirection: Flickable.VerticalFlick
		Column {
			id: content
			width: parent.width
			spacing: 10
			CgroupLabel { id: cg1; groupName: "/"; }
			CgroupLabel { id: cg2; groupName: "/system"; }
			CgroupLabel { id: cg3; groupName: "/system/desktop"; }
			CgroupLabel { id: cg4; groupName: "/system/applications"; }
			CgroupLabel { id: cg5; groupName: "/system/applications/standby"; }
			CgroupLabel {
				id: cg6;
				groupName: "/system/applications/standby/background";
				groupNameForHeader: ".../standby/background";
			}
			CgroupLabel {
				id: cg7;
				groupName: "/system/applications/standby/transient";
				groupNameForHeader: ".../standby/transient";
			}
			Button { width: parent.width; text: qsTr("Update"); onClicked: update(); }
		}
	}
}
