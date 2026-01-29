/* square3_3.c
 * metaprat - 920703
 * Town square, north side
 * Updated by Shinto 10-19-98
 *
 * Jan 2021, Lucius - Modernized
 *
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public void
create_terel_room()
{
    set_short("Calathin town square, central");
    set_long(
      "You are on the central portion of a bustling town square. A " +
      "huge tree towers above to the northwest, and you can barely " +
      "see that there is a door in its trunk. To your west, stands " +
      "a monument of some sort. To your east are some buildings " +
      "that might interest you, and further south is an inn and " +
      "pub.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
      "The tree looks like an ancient pine, about 100 meters tall or more. " +
      "It is towering above to the northwest. You can see some kind of " +
      "entrance on the south side of the trunk, and a sign, which is too far "+
      "away to read.\n");

    add_item( ({ "buildings" }),
      "To your south, across the square, you can see an inn, while to the " +
      "east you see a town hall and another unidentified building. To the " +
      "northwest, you can see an entrance leading into the huge pine tree, " +
      "which appears to be fairly busy.\n" );

    add_item( ({ "town square", "square" }),
      "The square is bustling with people... maybe it's market day here?\n");

    add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "in the air.\n");

    add_item( ({ "snow" }),
      "There is no snow here at all, its all been trodden into oblivion. " +
      "There is a lot of snow on the trees in the forest, and also in the " +
      "landscape visible from here.\n");

    add_item( ({ "ground", "footprint", "footprints" }),
      "Deeply frozen all year round, the ground never holds footprints.\n");

    add_item( ({ "monument", "statue" }),
      "It appears to be someone on a horse, modelled out of granite, and " +
      "facing towards the east. No other details are visible from this " +
      "distance.\n");

    add_exit(CALATHIN_DIR + "square3_2", "north", 0);
    add_exit(CALATHIN_DIR + "square3_4", "south", 0);
    add_exit(CALATHIN_DIR + "square2_3", "west", 0);
    add_exit(CALATHIN_DIR + "square4_3", "east", 0);
}
