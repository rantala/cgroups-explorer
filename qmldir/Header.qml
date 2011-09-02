import QtQuick 1.1
import com.nokia.meego 1.0
import "file:///usr/lib/qt4/imports/com/nokia/meego/UIConstants.js" as UI

Rectangle {
	property alias text: label.text
	signal refresh
	width: parent.width
	height: UI.HEADER_DEFAULT_HEIGHT_PORTRAIT
	clip: true
	color: "#5F20BD"
	z: 10
	Label {
		id: label
		width: parent.width - 2*UI.DEFAULT_MARGIN
		font.pixelSize: UI.FONT_XLARGE
		color: "white"
		z: parent.z + 1
		y: UI.DEFAULT_MARGIN
		x: UI.DEFAULT_MARGIN
	}
}
