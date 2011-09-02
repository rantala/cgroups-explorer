import QtQuick 1.1
import com.nokia.meego 1.0
import com.nokia.extras 1.0
import rantala.cgroups 1.0
import "file:///usr/lib/qt4/imports/com/nokia/meego/UIConstants.js" as UI

Item {
	property string groupName
	property string groupNameForHeader: groupName
	function update() {
		cgModel.update();
	}
	Header {
		id: header
		text: groupNameForHeader
	}
	ListView {
		id: taskView
		anchors.top: header.bottom
		width: parent.width - UI.DEFAULT_MARGIN
		height: parent.height - header.height
		x: UI.DEFAULT_MARGIN
		model: CgroupTaskModel {
			id: cgModel
			cgroup: groupName
		}
		delegate: ListDelegate {
			height: UI.LIST_ITEM_HEIGHT_SMALL
		}
	}
	ScrollDecorator {
		flickableItem: taskView
	}
}
