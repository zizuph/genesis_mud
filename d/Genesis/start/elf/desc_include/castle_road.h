/*
 * Some standard definitions for the rooms along the castle road:
 */

#define CASTLE_ROAD_NAT_SHORT "Along the Castle Road"
#define CASTLE_ROAD_FOR_SHORT "Along the castle road"

#define CASTLE_ROAD_NAT_LONG \
  "You are using the stone-paved Castle Road, which connects the "+\
  "Royal Castle in the south with the village in the north. "+\
  "The wide road is lined with young, "+\
  "sturdy oaks, standing straight like a military guard of honour on both "+\
  "sides of the road.\n"

#define CASTLE_ROAD_FOR_LONG \
  "You are using a wide, stone-paved road that connects the castle in the "+\
  "south with the village in the north. "+\
  "The road is lined with high trees on both "+\
  "sides.\n"

/*
 * Room items:
 */

#define ROAD_ITEM ({"road", "street", "stone", "stones", "pavement"})
#define ROAD_NDESC \
  "The road is paved with wide, smooth slabs of pink marble. Some are "    +\
  "large enough to almost reach across the road, but all are of irregular "+\
  "gemetric shape, fitting together with just hair-fine cracks between "   +\
  "them. Their surfaces are flat and almost unworn.\n"
#define ROAD_FDESC \
  "The road is paved with wide, smooth slabs of pink stone.\n"

#define TREE_ITEM ({"oaks", "oak", "tree", "trees"})
#define TREE_NDESC \
  "The oaks reach high and straight, as young oaks are wont to do.\n"
#define TREE_FDESC \
  "The trees might be oaks.\n"
  

#define CASTLE_ROAD_STD_ITEMS \
  add_item(TREE_ITEM,   N_KNOW(WRAP(TREE_NDESC),   WRAP(TREE_FDESC)));     \
  add_item(ROAD_ITEM,   N_KNOW(WRAP(ROAD_NDESC),   WRAP(ROAD_FDESC)))
