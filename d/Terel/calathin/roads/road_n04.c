/* silv_n_r5.c */
 
/* metaprat - 920622 */

/* Road from northern edge to centre. Connects with forest. */

/* Northern edge of Silvoria, where it intersects with the south of */
/* the forest.  Lightly inhabited here, some trees.  Descs taken    */
/* from Vader's forest, for consistency.                            */
/* Updated and changed to road_n4.c by Shinto 10-25-98 */
/* added exit to the stable, Trofast 4-4-1999 */ 

/* road_n4.c */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public void
create_room() 
{
    set_short("Road through Silver Forest");
    set_long(
      "You are on a road through a large pine forest.  To the south, you " +
      "see a huge pine towering above you into the sky, forcing the road " +
      "to curve southwest.  Beyond the tree, you catch glimpses of a town " +
      "centre.  Southeast from here a stable stands amidst a large yard.  "+
      "The road continues north, through a lightly populated area of the "+
      "forest.\n");

    add_item(({"trees", "tree"}), "They are tall and green.  Pine trees "
       + "often do well in the cold.\nThey are covered with snow in such a "
       + "way that the light reflected off\nof them gives it a silver color.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
     "The tree looks like an ancient pine, about 100 meters tall or more. " +
     "It is blocking your path to the south, and in fact forces the road " +
     "itself to bend towards the southwest. Strangely, smoke seems to be " +
     "drifting out from an old dead branch, 10 meters above your head!\n");

    add_item( ({ "smoke", "wisp", "wisp of smoke" }),
     "A faint wisp of dark brown smoke, billowing from a hollow branch, " +
     "many meters from your head.\n");
 
    add_item( ({ "branch", "old branch", "dead branch", "old dead branch" }),
     "Its far above you, but it seems to be smoking.. maybe the tree is on " +
     "fire!\n" );

    add_item( ({ "houses", "house" }),
      "There are houses to your northeast and northwest.  It is noticable " +
      "that the eastern houses are in bad shape, while the western houses " +
      "are well maintained by their owners.  All the houses appear to be " +
      "made out of pine logs, probably from the nearby forest.\n");

    add_item( ({ "buildings" }), "Most of the buildings are hidden behind " +
      "the huge tree, but they seem\nto be part of a town square.\n");

    add_item( ({ "stable" }),
      "The well-worn path to the stable seems to indicate that "+
      "it is open for business!\n");

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
      "years, clearly shows a road leading between the north and southwest.\n");

    add_exit(CALATHIN_DIR + "roads/road_n05", "north", 0);
    add_exit(CALATHIN_DIR + "paths/path_e01", "east", 0);
    add_exit(CALATHIN_DIR + "stable_yard",  "southeast", 0);
    add_exit(CALATHIN_DIR + "roads/road_n03", "southwest", 0);
}
