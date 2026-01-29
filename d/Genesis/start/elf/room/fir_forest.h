/*
 * Some standard definitions for the rooms inside the fir forest:
 */

/*
 * Room items:
 */

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


#define FIR_FOREST_STD_ITEMS \
  add_item(FOREST_ITEM, WRAP(FOREST_DESC));   \
  add_item(NEEDLE_ITEM, WRAP(NEEDLE_DESC));   \
  add_item(LICHEN_ITEM, WRAP(LICHEN_DESC))

