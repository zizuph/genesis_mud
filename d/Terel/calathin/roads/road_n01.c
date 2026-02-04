/* silv_n_r8.c */
 
/* metaprat - 920622 */

/* Road from northern edge to centre. Connects with forest. */

/* Northern edge of Silvoria, where it intersects with the south of */
/* the forest.  Lightly inhabited here, some trees.  Descs taken    */
/* from Vader's forest, for consistency.                            */
/* Updated and changes to road_n01.c by Shinto 10-21-98 */

/* road_n01.c */


#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public void
create_room() 
{
    set_short("Road from Silver Forest, near town square");
    set_long(
      "You are on a road near a huge pine tree.  To the southeast, you see " +
      "a bustling town square, while to the east, a huge pine tree towers " +
      "majestically over the town. Skirting the tree to the southwest, is "+
      "trail that leads between the forest and some buildings. "+
	  "To the north, the road continues towards "+
      "a wooded area, although you can't make out much at this distance, " +
      "through the icy mist.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
     "The tree looks like an ancient pine, about 100 meters tall or more. " +
     "It is towering above to to the east.  It is impossible to climb, " +
     "not only because all the possible handholds are iced over, but also " +
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
      "years, clearly shows a path leading between the north and southeast, "+
      "as well as southwest.\n");

    add_cmd_item( ({ "tree", "huge tree", "pine", "huge pine" }),
                 "climb",
                 "You look at the huge tree, and see no possible way you " +
                 "could climb it.\nThe lowest branch is many meters above " +
                 "your head, and the trunk\nof the tree is icy.\n");

    add_exit(CALATHIN_DIR + "roads/road_n02",  "north", 0);
    add_exit(CALATHIN_DIR + "square2_1", "southeast", 0);
    add_exit(CALATHIN_DIR + "paths/path_s01", "southwest", 0);
}

