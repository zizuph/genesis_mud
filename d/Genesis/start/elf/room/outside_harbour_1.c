#include "../stddefs.h"
#include "/sys/stdproperties.h"

#pragma save_binary

inherit ELFROOM;

#define SHORT  "Just off the coast"

#define LONG \
  "You are just outside the coast, where high, white limestone cliffs rises "+\
  "from fifty to hundred feet above the water line. Beyond the cliffs "+\
  "the dark tree-crowns of a mighty forest can be seen, and a dark cut "+\
  "hints at the presence of a small cove or bay.\n" +\
  "The raging sea has cut the soft stone into many weird and fantastic "+\
  "shapes. There are arches and pillars, rising from the waves. There are "+\
  "dark caves in the cliff face, semi-submerged and filled with the white "+\
  "foam of the breaking waves. There are those that remind " +\
  "you of strange, crouched beasts or crenelated castles, in the same way "+\
  "that the clouds of summer might.\n" +\
  "Sitting on these rocks, or cavorting around in the surging waves, "+\
  "is a school of mermaids.\n"


#define MERMAIDS_ITEM ({"mermaids"})
#define MERMAIDS_DESC \
  "They seem to be part fish, part teenage girl.\n"

#define ARCHES_ITEM ({"arch", "arches", "pillar", "pillars", "cave", "caves",\
		      "shapes", "castles", "beasts", "rocks", "rock"})
#define ARCHES_DESC \
  "They sure are amazing shapes to be cut by nature's own hand.\n"

#define BAY_ITEM ({"bay", "cove", "small cove"})
#define BAY_DESC \
  "It is hidden from direct view.\n"

#define FOREST_ITEM ({"forest", "crowns", "tree-crowns"})
#define FOREST_DESC \
  "The forest seems to be an old, dark fir forest.\n"

#define LIMESTONE_ITEM ({"limestone", "stone"})
#define LIMESTONE_DESC \
  "It is a soft, white species of rock.\n"

#define COAST_ITEM ({"coast", "cliffs", "cliff face", "cliff"})
#define COAST_DESC \
  "The cost consists of high, white limestone cliffs, rising from the sea.\n"

  
create_room()
{
  set_short(SHORT);
  set_long(WRAP(LONG));

  add_item(   ARCHES_ITEM,    ARCHES_DESC);
  add_item( MERMAIDS_ITEM,  MERMAIDS_DESC);
  add_item(      BAY_ITEM,       BAY_DESC);
  add_item(   FOREST_ITEM,    FOREST_DESC);
  add_item(LIMESTONE_ITEM, LIMESTONE_DESC);
  add_item(    COAST_ITEM,     COAST_DESC);

  add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

  set_noshow_obvious(1);
  stock();
}

stock()
{
  restock_object(MONSTERDIR + "simple_mermaid", 3, "mermaid");
}

reset_room()
{
  stock();
}
