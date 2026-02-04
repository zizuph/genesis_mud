
/* forest8_4.c     -    metaprat  -    920710    */

/* Lightly inhabited forest, north of the town square. */
/* This is the western, well-kept part.                */

inherit "/std/room.c";

#include "/d/Terel/common/terel_defs.h"

create_room() {
   set_short("Track in Silver Forest");
   set_long(break_string(
      "You are on a trail, in a large pine forest.  It leads north, " +
      "northwest, and south.  To the south, you see a road, leading " +
      "southwest past an enormous tree.  The northwest branch of the trail " +
      "leads deeper into the forest, while the northern branch looks more "+
      "used.\n", 70) );

   add_item(({"trees", "tree"}), break_string(
      "They are tall and green.  Pine trees often do well in the cold.  " +
      "They are covered with snow in such a way that the light reflected " +
      "off of them gives it a silver color.\n", 70) );

   add_item( ({ "huge tree" }),
     break_string("The tree looks like an ancient pine, about 100 meters " +
        "tall or more.  It towers over the surrounding forest, like a " +
        "storm giant over dwarves.  It is to your south.\n", 70) );

   add_item( ({ "houses", "house" }), break_string(
      "There are houses to your east and south.  It is noticable that the " +
      "eastern houses are in bad shape, while the western houses are well " +
      "maintained by their owners.  All the houses appear to be made out " +
      "of pine logs, probably from the nearby forest.  The house here, " +
      "is a small pine cabin, and looks inhabited.  Snow covers its "+
      "roof, making it merge into the surrounding snow drifts.\n", 70) );

   add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "in the air.\n");

   add_item( ({ "snow" }),
      break_string(
      "There is a considerable amount of snow here, particularly in the " +
      "branches of the trees, and on the roofs of houses.\n", 70) );

   add_item( ({ "ground", "footprint", "footprints", "trail", "road", "path"}),
      break_string(
      "Glancing down at the trail, you see footsteps in the snow, leading "+
      "north, northwest, and south.\n", 70) );

   add_exit(TOWNDIR + "forest8_3", "north", 0);
   add_exit(TOWNDIR + "silv_n_r6", "south", 0);
   add_exit(TOWNDIR + "forest7_3", "northwest", 0);
}

