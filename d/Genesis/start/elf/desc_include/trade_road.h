/*
 * Some standard definitions for the rooms along the trade road:
 */



#define TRADE_ROAD_NAT_SHORT "Along the Trade Road"
#define TRADE_ROAD_FOR_SHORT "Along a forest road"

#define TRADE_ROAD_NAT_LONG \
  "You are standing on the Trade Road, on which merchants bring their "+\
  "goods from the outside world in the north to the court of King Oberon "+\
  "and Queen Titania. Huge, dark firs surround the road, and the air "+\
  "smells of resin and wood.\n"
  

#define TRADE_ROAD_FOR_LONG \
  "You are standing on a small road in the middle of a dark fir forest.\n"


/*
 * Room items:
 */

#define ROAD_ITEM ({"road", "track", "wagon track", "ruts", "rut"})
#define ROAD_DESC \
  "The road is only two ruts of bare earth, with a string of dark, "+\
  "short grass inbetween.\n"

#define FOREST_ITEM ({"forest", "tree", "trees", "fir", "firs"})
#define FOREST_DESC \
  "The firs are huge, up to a hundred feet high, with broad, dark " +\
  "needles. The ground beneath these majestic trees is bare, covered in "+\
  "a soft carpet of brown, dried needles. From the branches hangs long "+\
  "beards of gray lichen.\n"

#define NEEDLE_ITEM ({"needle", "needles"})
#define NEEDLE_DESC \
  "The needles on the firs are dark and broad. The needles on the "+\
  "ground are brown and dried.\n"

#define LICHEN_ITEM ({"lichen"})
#define LICHEN_DESC "The lichen is gray, dry and brittle. "


#define TRADE_ROAD_STD_ITEMS \
  add_item(FOREST_ITEM, WRAP(FOREST_DESC));   \
  add_item(NEEDLE_ITEM, WRAP(NEEDLE_DESC));   \
  add_item(LICHEN_ITEM, WRAP(LICHEN_DESC));   \
  add_item(ROAD_ITEM, WRAP(ROAD_DESC))
