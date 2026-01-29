/*
 * Some standard definitions for the rooms along the village road:
 */

#define WINE_ROAD_NAT_SHORT "Along the Village Road"
#define WINE_ROAD_FOR_SHORT "Along the village road"

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

#define HROW_ITEM ({"hedgerow", "hedge", "hedgerows", "hedges"})
#define HROW_DESC \
  "The hedgerows are bushy, brushy, thorny and quite impenetrable.\n"


#define WINE_ROAD_STD_ITEMS \
  add_item(ROAD_ITEM,   N_KNOW(WRAP(ROAD_NDESC),   WRAP(ROAD_FDESC))); \
  add_item(HROW_ITEM,   WRAP(HROW_DESC))
