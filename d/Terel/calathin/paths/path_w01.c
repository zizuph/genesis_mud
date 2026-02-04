/* forest8_4.c     -    metaprat  -    920710    */

/* Lightly inhabited forest, north of the town square. */
/* This is the western, well-kept part.                */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public void
create_room() 
{
    set_short("Track in Silver Forest");
    set_long(
      "You are on a trail, in a large pine forest.  It leads west, " +
      "northeast, and south.  To the south, you see a road, leading " +
      "southwest past an enormous tree.  The west branch of the trail " +
      "leads deeper into the forest, while the northeastern branch looks more "+
      "used.\n");

    add_item(({"trees", "tree"}), 
      "They are tall and green.  Pine trees often do well in the cold.  " +
      "They are covered with snow in such a way that the light reflected " +
      "off of them gives it a silver color.\n");

    add_item( ({ "huge tree" }),
        "The tree looks like an ancient pine, about 100 meters " +
        "tall or more.  It towers over the surrounding forest, like a " +
        "storm giant over dwarves.  It is to your south.\n");

    add_item( ({ "houses", "house" }),
      "There are houses to your east and west.  It is noticable that the " +
      "eastern houses are in bad shape, while the western houses are well " +
      "maintained by their owners.  All the houses appear to be made out " +
      "of pine logs, probably from the nearby forest.  The house here, " +
      "is a small pine cabin, and looks inhabited.  Snow covers its "+
      "roof, making it merge into the surrounding snow drifts.\n");

    add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "in the air.\n");

    add_item( ({ "snow" }),
      "There is a considerable amount of snow here, particularly in the " +
      "branches of the trees, and on the roofs of houses.\n");

    add_item( ({ "ground", "footprint", "footprints", "trail", "road", "path"}),
      "Glancing down at the trail, you see footsteps in the snow, leading "+
      "west, northeast, and south.\n");

    add_exit(CALATHIN_DIR + "roads/road_n03", "south", 0);
    add_exit(CALATHIN_DIR + "paths/path_w02", "west",0);
    add_exit(CALATHIN_DIR + "roads/road_n05", "northeast", 0);
}

