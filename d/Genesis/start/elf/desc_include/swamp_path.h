/*
 * Some standard definitions for the rooms along the trade path:
 */

#define SWAMP_PATH_NAT_SHORT "Along the Swamp Path"
#define SWAMP_PATH_FOR_SHORT "Along a muddy path"

#define SWAMP_PATH_NAT_LONG \
  "You are carefully walking along the Swamp Path. It is a small path, "+\
  "consisting of only a deep, muddy rut in the ground, "+\
  "winding its way among the surrounding huge firs.\n"
#define SWAMP_PATH_FOR_LONG \
  "You are carefully walking along a small path, "+\
  "consisting of only a deep, muddy rut in the ground, "+\
  "as it winds its way among the surrounding huge firs.\n"

/*
 * Room items:
 */

#define PATH_ITEM ({"path", "swamp path", "muddy rut", "ruts", "rut"})
#define PATH_DESC \
  "The path is only a deep rut of wet mud, winding an ambling "+\
  "way through the forest.\n"

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
#define LICHEN_DESC "The lichen is gray, dry and brittle.\n"

#define MUD_ITEM ({"mud", "wet mud"})
#define MUD_DESC \
  "It is brown, wet and slippery, just the way mud is supposed to be.\n"

#define SWAMP_PATH_STD_ITEMS \
  add_item(FOREST_ITEM, WRAP(FOREST_DESC));   \
  add_item(NEEDLE_ITEM, WRAP(NEEDLE_DESC));   \
  add_item(LICHEN_ITEM, WRAP(LICHEN_DESC));   \
  add_item(   MUD_ITEM, WRAP(   MUD_DESC));   \
  add_item(  PATH_ITEM, WRAP(  PATH_DESC))
