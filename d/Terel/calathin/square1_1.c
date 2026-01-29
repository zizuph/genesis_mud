/*
 * square1_1.c
 * metaprat 920629 remade Redhawk 920811
 * Town square.  1,1 is at position X7,Y8 on the overall map.
 * Updated by Shinto 10-19-98
 * Updated by Orion  5-17-99
 *
 * Jan 2021, Lucius - Modernized
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public void
create_terel_room()
{
    set_short("Calathin Town Square, northwestern corner");
    set_long(
      "You are in the northwest corner of a bustling town square. " +
      "A huge pine tree towers over you to the northeast. A winding " +
      "road snakes in from the forest, coming between you and the " +
      "huge tree. The road ends just before a white, marble column. " +
      "In the northwestern corner of the square is a shop of some " +
      "sort. Southwest of you is the Bank of Calathin. Off to the " +
      "south, just west of a tavern, you see another road. You " +
      "notice a large statue in the center of the square.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
      "The tree looks like an ancient pine, about 100 meters tall or more. " +
      "It is towering above to the northeast. You can see some kind of " +
      "entrance on the south side of the trunk, and a sign, which is too far "+
      "away to read.\n");

    add_item( ({ "buildings" }),
      "To your south, across the square, you can see an inn, while to the " +
      "east you see a town hall and another unidentified building. Roughly " +
      "to the northeast, you can see an entrance leading into the huge " +
      "pine tree, which appears to be fairly busy.\n");

    add_item( ({ "town square", "square" }),
      "The square is bustling with people.. maybe it's market day here?\n");

    add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "in the air.\n");

    add_item( ({ "snow" }),
      "There is no snow here at all, it's all been trodden into oblivion. " +
      "There is a lot of snow on the trees in the forest, and also in the " +
      "landscape visible from here.\n");

    add_item( ({ "ground", "footprint", "footprints" }),
      "Deeply frozen all year round, the ground never holds footprints.\n");

    add_item( ({ "statue" }),
      "It appears to be someone on a horse, modelled out of granite, and " +
      "facing towards the east. No other details are visible from this " +
      "distance.\n");

    add_item( ({ "sign" }), "The sign is far too far away to read.\n");

    add_cmd_item( "sign", "read", "The sign is far too far away to read.\n");

    add_cmd_item(
      ({ "tree", "huge tree", "pine", "huge pine", "huge pine tree" }),
      "climb",
      "How can you climb the tree if it's no-where near you?\n");

    add_exit(CALATHIN_DIR + "square2_1", "east", 0);
    add_exit(CALATHIN_DIR + "square1_2", "south", 0);

    room_add_object(CALATHIN_DIR + "obj/skin_door2");
    add_npc(CALATHIN_DIR + "npc/std_move_guard");
}
