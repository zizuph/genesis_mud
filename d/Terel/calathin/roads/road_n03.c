/* silv_n_r6.c */

/* metaprat - 920622 */

/* Road from northern edge to centre. Connects with forest. */

/* Northern edge of Silvoria, where it intersects with the south of */
/* the forest.  Lightly inhabited here, some trees.  Descs taken    */
/* from Vader's forest, for consistency.                            */
/* Updated and changed to road_n03.c by Shinto 10-21-98 */
/*
    Modified 3 May 2003, by Bleys
        - fixed a typo in the "pine" add_item
*/

/* road_n03.c */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public void
create_room() 
{
   set_short("Road through Silver Forest");
   set_long(
      "You are on a road on the edge of a large pine forest.  To the south" +
      "east, you see a huge pine towering above you into the sky. The road " +
      "travels northeast towards a lightly inhabited forest, and southwest " +
      "towards the town square, which is partially obscured by the huge " +
      "pine.\n"+
      "Two small paths lead north and northwest, towards some well-kept log " +
      "houses.\n");

    add_item(({"trees", "tree"}), "They are tall and green.  Pine trees "
       + "often do well in the cold.\nThey are covered with snow in such a "
       + "way that the light reflected off\nof them gives it a silver color.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
     "The tree looks like an ancient pine, about 100 meters tall or more.  It "+
     "is towering above you to the southwest.  It is impossible to climb, "+
     "since the nearest branch is about 5 meters above your head.  Oddly, a " +
     "faint wisp of smoke seems to be coming from further around the tree, " +
     "to the northeast.\n");


    add_item( ({ "smoke", "wisp", "wisp of smoke" }),
     "You can't see the source from here, but it seems to be coming from " +
     "high\nin the tree, to the northeast.\n");

    add_item( ({ "houses", "house" }),
      "There are houses to your north and northwest, made of pine logs. " +
      "They seem to be well maintained, although it's hard to tell from " +
      "this distance.\n");

    add_item( ({ "buildings" }), "Most of the buildings are hidden behind " +
      "the huge tree, but they seem\nto be part of a town square.\n");

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
      "years, clearly shows a road leading southwest, and several paths " +
      "leading in the northerly directions.  The most worn is the north "+
      "road.\n");

    add_exit(CALATHIN_DIR + "paths/path_w01", "north", 0);
    add_exit(CALATHIN_DIR + "roads/road_n04",   "northeast", 0);
    add_exit(CALATHIN_DIR + "roads/road_n02",   "southwest", 0);
    add_exit(CALATHIN_DIR + "paths/path_w02", "northwest", 0);
}
