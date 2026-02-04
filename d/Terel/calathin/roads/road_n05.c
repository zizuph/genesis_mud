/* silv_n_r4.c */
 
/* metaprat - 920622 */

/* Road from northern edge to centre. Connects with forest. */

/* Northern edge of Silvoria, where it intersects with the south of */
/* the forest.  Lightly inhabited here, some trees.  Descs taken    */
/* from Vader's forest, for consistency.                            */
/* Updated and changed to road_n5.c by Shinto 10-24-98 */

/* road_n5.c */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public void
create_room()
 {
   set_short("Road through Silver Forest");
   set_long(
      "You are on a road through a large pine forest.  To the south, you " +
      "can see the roofs of several buildings, just beyond a huge tree " +
      "towering into the sky.  This road continues north, until it enters " +
      "a denser part of the silvery forest.\n"+
      "A light track through the trees to your southwest leads towards some " +
      "well maintained houses, while the houses to the east seem to be " +
      "in bad repair, as does the east path itself.\n");

    add_item(({"trees", "tree"}), "They are tall and green.  Pine trees "
      + "often do well in the cold.\nThey are covered with snow in such a "
      + "way that the light reflected off\nof them gives it a silver color.\n");

    add_item( ({ "huge tree" }), "The tree looks like an ancient pine, about " +
     "100 meters tall or more.\n");

    add_item( ({ "houses", "house" }), 
      "There are houses to your east and west.  It is noticable that the " +
      "eastern houses are in bad shape, while the western houses are well " +
      "maintained by their owners.  All the houses appear to be made out " +
      "of pine logs, probably from the nearby forest.\n");
 
    add_item( ({ "buildings" }), "You can see some snowy roofs, but that's " +
      "all from this distance.\n");

    add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "in the air.\n");

    add_item( ({ "snow" }),
      "There isn't much actual snow here, it's all been trodden into the " +
      "ground by the locals.  Off the road, there are several areas " +
      "covered with icy snow.\n");

    add_item( ({ "ground", "footprint", "footprints", "trail", "road", "path"}),
      "Deeply frozen for the entire year, the ground never holds footprints. "+
      "However, the pattern of erosion from all the feet walking on it over " +
      "years, clearly shows a road leading north/south, and paths leading  " +
      "towards the east and west.\n");

    add_exit(CALATHIN_DIR + "roads/road_n06", "north", 0);
    add_exit(CALATHIN_DIR + "roads/road_n04", "south", 0);
    add_exit(CALATHIN_DIR + "paths/path_n01", "east", 0);
    add_exit(CALATHIN_DIR + "paths/path_w01", "southwest",0);
}
