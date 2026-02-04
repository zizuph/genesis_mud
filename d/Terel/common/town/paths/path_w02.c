
/* path_w02.c   -    Vader (adapted from Metaprats forest files)  */

/* Lightly inhabited forest, north of the town square. */
/* This is the western, well-kept part.                */

inherit "/std/room.c";

#include "/d/Terel/common/terel_defs.h"

create_room() {
   set_short("Track in Silver Forest");
   set_long(break_string(
      "You are on a trail, in a large pine forest.  It leads to the " +
      "southeast and west.  To the west, you can head deeper into " +
      "the forest, and southeast leads back to the road.\n", 70));

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
      "west and southeast.\n", 70));

   add_exit(TOWNDIR + "silv_n_r6", "southeast", 0);
   add_exit(TOWNDIR + "paths/path_w03", "west", 0);
}

