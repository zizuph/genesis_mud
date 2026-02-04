
/* path_w02.c   -    Vader (adapted from Metaprats forest files)  */

/* Lightly inhabited forest, north of the town square. */
/* This is the western, well-kept part.                */

inherit "/std/room.c";

#include "/d/Terel/common/terel_defs.h"

create_room() {
   set_short("Track in Silver Forest");
   set_long(break_string(
      "You are on a trail, in a large pine forest.  It leads to the " +
   "east and west.  West heads deeper into the forest, and east " +
   "leads back to the road.  There is also a house to the northwest." +
   "\n", 70));

   add_item(({"trees", "tree"}), break_string(
      "They are tall and green.  Pine trees often do well in the cold.  " +
      "They are covered with snow in such a way that the light reflected " +
      "off of them gives it a silver color.\n", 70) );

   add_item( ({ "huge tree" }),
     break_string("The tree looks like an ancient pine, about 100 meters " +
        "tall or more.  It towers over the surrounding forest, like a " +
        "storm giant over dwarves.  It is to your south.\n", 70) );


   add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "in the air.\n");

   add_item( ({ "snow" }),
      break_string(
      "There is a considerable amount of snow here, particularly in the " +
      "branches of the trees.\n", 70));

   add_item( ({ "ground", "footprint", "footprints", "trail", "road", "path"}),
      break_string(
      "Glancing down at the trail, you see footsteps in the snow, leading "+
      "west and east.\n", 70));
   add_item(({"house"}), break_string("This house is made from the " +
    "fine pine logs cut from this very forest, years ago.  These " +
    "log houses look like the image of perfection.\n", 70));


   add_exit(TOWNDIR + "paths/path_w02", "east", 0);
   add_exit(TOWNDIR + "paths/path_w04", "west", 0);
   add_exit(TOWNDIR + "houses/m_house2", "northwest", 0);
}

