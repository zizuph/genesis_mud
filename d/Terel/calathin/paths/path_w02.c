/* path_w02.c   -    Vader (adapted from Metaprats forest files)  */

/* Lightly inhabited forest, north of the town square. */
/* This is the western, well-kept part.                */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public void
create_room() 
{
    set_short("Track in Silver Forest");
    set_long(
      "You are on a trail, in a large pine forest.  It leads to the " +
      "southeast and west.  To the west, you can head deeper into " +
      "the forest, and southeast leads back to the road.\n");

    add_item(({"trees", "tree"}),
      "They are tall and green.  Pine trees often do well in the cold.  " +
      "They are covered with snow in such a way that the light reflected " +
      "off of them gives it a silver color.\n");

    add_item( ({ "huge tree" }),
        "The tree looks like an ancient pine, about 100 meters " +
        "tall or more.  It towers over the surrounding forest, like a " +
        "storm giant over dwarves.  It is to your south.\n");


    add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "in the air.\n");
 
    add_item( ({ "snow" }),
      "There is a considerable amount of snow here, particularly in the " +
      "branches of the trees.\n");

    add_item( ({ "ground", "footprint", "footprints", "trail", "road", "path"}),
      "Glancing down at the trail, you see footsteps in the snow, leading "+
      "west and southeast.\n");

    add_exit(CALATHIN_DIR + "roads/road_n03", "southeast", 0);
    add_exit(CALATHIN_DIR + "paths/path_w03", "west", 0);
    add_exit(CALATHIN_DIR + "paths/path_w01", "east",0);
}

