/* path_w03.c   -    Vader (adapted from Metaprats forest files)  */

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
       "east and west.  West heads deeper into the forest, and east " +
       "leads back to the road.  There is also a house to the northwest." +
       "\n");

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
       "west and east.\n");
    add_item(({"house"}),"This house is made from the " +
        "fine pine logs cut from this very forest, years ago.  These " +
        "log houses look like the image of perfection.\n");


    add_exit(CALATHIN_DIR + "paths/path_w02", "east", 0);
    add_exit(CALATHIN_DIR + "paths/path_w04", "west", 0);
    add_exit(CALATHIN_DIR + "houses/house4", "northwest", 0);
}
