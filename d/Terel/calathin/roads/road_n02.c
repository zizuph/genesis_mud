/* silv_n_r7.c */

/* metaprat - 920622 */

/* Road from northern edge to centre. Connects with forest. */

/* Northern edge of Silvoria, where it intersects with the south of */
/* the forest.  Lightly inhabited here, some trees.  Descs taken    */
/* from Vader's forest, for consistency.                            */
/* Updated and changed to road_n02.c by Shinto 10-21-98 */

/* road_n02.c */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>

public void
create_room()
{
    set_short("Road through Silver Forest");
    set_long(
      "You are on a road near a large pine forest.  To the south, the road " +
      "turns towards the town square, while to the east, you stare upwards " +
      "at a huge pine tree, whose top disappears into the mist.  The road " +
      "continues northeast around the tree, into a lightly populated area " +
      "of forest.\n");

    add_item(({"trees", "tree"}), "They are tall and green.  Pine trees "
        + "often do well in the cold.\nThey are covered with snow in such a "
        + "way that the light reflected off\nof them gives it a silver color.\n");
 
    add_item( ({ "huge tree", "pine", "huge pine" }),
     "The tree looks like an ancient pine, about 100 meters tall or more. " +
     "It is towering above to to the east.  It is impossible to climb, " +
     "since the nearest branch is about 5 meters above your head.  Just " +
     "looking up at it gives you a terrible sensation of vertigo, and you " +
     "glance back down to the level ground, with relief.\n");

    add_item( ({ "buildings" }),
      "You can see what appears to be a pub of " +
      "some sort at the southern end of the town square, but the other " +
      "buildings to the east of the square are not visible.\n");
 
    add_item( ({ "town square", "square" }),
      "The square is bustling with people.. maybe it's market day here?\n");

    add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "in the air.\n");

    add_item( ({ "snow" }),
      "There isn't much actual snow here, its all been trodden into the " +
      "ground by the locals.  Off the road, there are several areas " +
      "covered with icy snow.\n");

    add_item( ({ "ground", "footprint", "footprints", "trail", "road", "path"}),
      "Deeply frozen for the entire year, the ground never holds footprints. "+
      "However, the pattern of erosion from all the feet walking on it over " +
      "years, clearly shows a path leading between the northeast and south.\n");

    add_exit(CALATHIN_DIR + "roads/road_n03",   "northeast", 0);
    add_exit(CALATHIN_DIR + "roads/road_n01",   "south", 0);
}
