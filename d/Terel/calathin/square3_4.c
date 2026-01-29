/*
 * square3_4
 * metaprat 920703 remade 9207 31 Redhawk
 * Updated by Shinto 10-19-98
 *
 * Jan 2021, Lucius - Modernized
 *
 * Town square, north side
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public void
create_terel_room()
{
    set_short("Calathin town square, southern edge");
    set_long(
      "You are on the southern portion of a bustling town square. To " +
      "the northwest is a monument, behind of which lies a huge " +
      "pine tree. There is a door cut into the trunk, and a sign, but " +
      "you cannot read the sign from here. To the northeast, there are " +
      "a couple of buildings. West is an inn, and south is the " +
      "entrance to the pub.\n");

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

    add_exit(CALATHIN_DIR + "square3_3", "north", 0);
    add_exit(CALATHIN_DIR + "square2_4", "west", 0);
    add_exit(CALATHIN_DIR + "square4_4", "east", 0);

    room_add_object(CALATHIN_DIR + "obj/big_door2");
    add_npc(CALATHIN_DIR+ "npc/std_move_guard");
}
