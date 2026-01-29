/*
 * Some standard definitions for the rooms along the village road:
 */

#define VILL_ROAD_NAT_SHORT "Along the Village Road"
#define VILL_ROAD_FOR_SHORT "Along the village road"

#define VILL_ROAD_NAT_LONG \
  "You are standing on the stone-paved Village Road, which goes all the " + \
  "way around the small park that lies in the middle of the village of " + \
  "Greenoaks. In the south, you can see the towers of the Royal Castle " + \
  "rise towards the sky.\n"

#define VILL_ROAD_FOR_LONG \
  "You are standing on a small, stone-paved road in the middle of a small "+\
  "village. The road follows the side of a park, that seems to lie in the "+\
  "middle of the village. In the south, you can see the towers of a castle "+\
  "rise towards the sky.\n"

/*
 * Room items:
 */

#define ROAD_ITEM ({"road", "street", "stone", "stones", "pavement"})
#define ROAD_NDESC \
  "The road is paved with wide, smooth slabs of white stone. Some are "    +\
  "large enough to almost reach across the road, but all are of irregular "+\
  "gemetric shape, fitting together with just hair-fine cracks between "   +\
  "them. There are ruts in the flat surface from centuries of wear.\n"
#define ROAD_FDESC \
  "The road is paved with wide, smooth slabs of white stone, with some "   +\
  "ruts worn into the smooth surface, probably from iron-shod wagon wheels.\n"

#define PARK_ITEM ({"park", "oaks", "oak"})
#define PARK_NDESC \
  "In the park thrives the oaks that has given the village its name. The " +\
  "current crop is reaching its most majestic and beautiful age, and the " +\
  "garderners have all reason to be satisfied with their work.\n"
#define PARK_FDESC \
  "The park is filled with ancient, huge oaks, their crowns rich and green.\n"
  
#define CASTLE_ITEM ({"castle", "palace", "tower", "towers"})
#define CASTLE_NDESC \
  "The towers of King Oberon's and Queen Titania's castle " + \
  "shimmers from the sunlight reflected and refracted by the thousands of " +\
  "jewels that has been set into the castle walls.\n" 
#define CASTLE_FDESC \
  "The towers of a castle shimmers in the sunlight, as if " +\
  "jewels had been set into its walls.\n"


#define VILL_ROAD_STD_ITEMS \
  add_item(PARK_ITEM,   N_KNOW(WRAP(PARK_NDESC),   WRAP(PARK_FDESC)));     \
  add_item(CASTLE_ITEM, N_KNOW(WRAP(CASTLE_NDESC), WRAP(CASTLE_FDESC)));   \
  add_item(ROAD_ITEM,   N_KNOW(WRAP(ROAD_NDESC),   WRAP(ROAD_FDESC)))
