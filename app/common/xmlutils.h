/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2020 Olive Team

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#ifndef XMLREADLOOP_H
#define XMLREADLOOP_H

#include <QXmlStreamReader>

#include "node/param.h"
#include "project/item/footage/stream.h"
#include "undo/undocommand.h"

namespace olive {

class Block;
class Item;
class Node;
class NodeInput;

#define XMLAttributeLoop(reader, item) \
  foreach (const QXmlStreamAttribute& item, reader->attributes())

struct XMLNodeData {
  struct SerializedConnection {
    NodeInput input;
    quintptr output_node;
    QString output;
  };

  struct BlockLink {
    Node* block;
    quintptr link;
  };

  QHash<quintptr, Node*> node_ptrs;
  QList<SerializedConnection> desired_connections;
  QList<BlockLink> block_links;
  QHash<quintptr, Item*> item_ptrs;

};

void XMLConnectNodes(const XMLNodeData& xml_node_data, MultiUndoCommand *command = nullptr);

bool XMLReadNextStartElement(QXmlStreamReader* reader);

void XMLLinkBlocks(const XMLNodeData& xml_node_data);

}

#endif // XMLREADLOOP_H
