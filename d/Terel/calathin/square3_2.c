/* square3_12.c
 * metaprat - 920703
 * Town square, north side
 * Updated by Shinto 10-19-98

    Modified: 16 Sep 2003, by Bleys
	- Now clones the elven boy Ailin.
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
      "huge tree, towering high into the sky, can be seen to the " +
      "northwest. To the east and southeast, there are a couple of " +
      "buildings. To the southwest, you can see a monument of some " +
      "sort. To the southwest, there is an inn.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
      "The tree looks like an ancient pine, about 100 meters tall or more. " +
      "It is towering above to the northwest. You can see some kind of " +
      "entrance on the south side of the trunk, and a sign, which is too far "+
      "away to read.\n");

    add_item( ({ "buildings" }),
      "To your south, across the square, you can see an inn, while to the " +
      "east you see a town hall and another unidentified building. To the " +
      "northwest, you can see an entrance leading into the huge pine tree, " +
      "which appears to be fairly busy.\n");

    add_item( ({ "town square", "square" }),
      "The square is bustling with people... maybe it's market day here?\n");

    add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "in the air.\n");

    add_item( ({ "snow" }),
      "There is no snow here at all, it's all been trodden into oblivion. " +
      "There is a lot of snow on the trees in the forest, and also in the " +
      "landscape visible from here.\n");

    add_item( ({ "ground", "footprint", "footprints" }),
      "Deeply frozen all year round, the ground never holds footprints.\n");

    add_item( ({ "monument", "statue" }),
      "It appears to be someone on a horse, modelled out of granite, and " +
      "facing towards the east. No other details are visible from this " +
      "distance.\n");

    add_exit(CALATHIN_DIR + "square3_1", "north", 0);
    add_exit(CALATHIN_DIR + "square3_3", "south", 0);
    add_exit(CALATHIN_DIR + "square2_2", "west", 0);
    add_exit(CALATHIN_DIR + "square4_2", "east", 0);

    room_add_object(CALATHIN_DIR + "obj/bin");
    add_npc(CALATHIN_DIR + "npc/ailin");
    add_npc(CALATHIN_DIR + "npc/std_move_citizen");
}
