/*
 * gst-droid
 *
 * Copyright (C) 2014 Mohammed Sameer <msameer@foolab.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

import QtQuick 2.0
import VideoPlayer 1.0

Rectangle {
        color: "black"

        VideoPlayer {
                id: player
                anchors.fill: parent
                source: _source
        }

        Button {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                text: "<<"
                onClicked: player.position = player.position - 5000
        }

        Button {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                text: "P"
                onClicked: {
                        if (player.state != VideoPlayer.StatePlaying) {
                                player.play()
                        }
                        else {
                                player.pause()
                        }
                }
        }

        Button {
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                text: ">>"
                onClicked: player.position = player.position + 5000
        }
}
