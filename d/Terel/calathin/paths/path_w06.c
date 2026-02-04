/* path_w02.c   -    Vader (adapted from Metaprats forest files)  */

/* Lightly inhabited forest, north of the town square. */
/* This is the western, well-kept part.                */
/* Updated by Shinto 11-8-98 */

/*
 * Updated 2019.08.01 by Shanoga:
 *  - Added VBFC check for current/recent combat before entering
 *     non-combat temple to the south.
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public void
create_room() {
    set_short("Track in Silver Forest");
    set_long(
      "You are on a trail, in a large pine forest.  It leads to the " +
      "north and south.  South is the entrance to a temple, and north " +
      "leads back into the forest.\n");

    add_item(({"trees", "tree"}),
      "They are tall and green.  Pine trees often do well in the cold.  " +
      "They are covered with snow in such a way that the light reflected " +
      "off of them gives it a silver color.\n");

    add_item( ({ "huge tree" }),
        "The tree looks like an ancient pine, about 100 meters " +
        "tall or more.  It towers over the surrounding forest, like a " +
        "storm giant over dwarves.  It is to your south.\n");


    add_item( ({ "mist", "icy mist" }),
        "The mist is just the effect of the chill weather on the water vapor "
+
        "in the air.\n");

    add_item( ({ "snow" }),
         "There is a considerable amount of snow here, particularly in the " +
         "branches of the trees.\n");

    add_item( ({ "ground", "footprint", "footprints", "trail", "road",
"path"}),
         "Glancing down at the trail, you see footsteps in the snow, leading "+
         "north and south.\n");
    add_item(({"temple"}), "It is made from a dark " +
        "granite, and emanates a feeling of mystery.\n");


    add_exit(CALATHIN_DIR + "paths/path_w05", "north", 0);
    add_exit(CALATHIN_DIR + "temple/temple", "south", "@@enter_church");
}

public int
enter_church() {
    
    if (!TP->query_relaxed_from_combat() || TP->query_attack())
    {
        TP->catch_vbfc("You sense a divine force preventing you from entering "+
                       "that holy place because of your recent combat.\n");
        return 1;
    }
    return 0;
}