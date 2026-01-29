/*
 * square1_2.c
 * metaprat - 920703
 * Additions by Om - 920721
 * Updated by Shinto, 10-19-98
 * Updated by Orion  5-17-99
 *
 * Jan 2021, Lucius - Modernized
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public void
create_terel_room()
{
    set_short("Calathin Town Square, western edge");
    set_long(
      "You are in the northwestern side of a bustling town square. " +
      "A huge pine tree towers over the city further northeast, just " +
      "past a road and a marble column. You can see a tavern off to " +
      "south, just east of another road. In the center of the square" +
      ", to the southeast, is a large stone statue facing away " +
      "from you. Through the mist, you can barely make out buildings " +
      "on the opposite side of the square. West of you lies the " +
      "entrance to the Bank of Calathin.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
      "The tree looks like an ancient pine, about 100 meters tall or more. " +
      "It is towering above to the northeast. You can see some kind of " +
      "entrance on the south side of the trunk, and a sign, which is too far "+
      "away to read.\n");

    add_item( ({ "buildings" }),
      "To your southeast, you can see an inn and a pub, while to the east " +
      "you see an outline of a couple of buildings through the mist.\n");

    add_item( ({ "town square", "square" }),
      "The square is bustling with people.. maybe it's market day here?\n");

    add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chilly weather on the water vapor " +
      "in the air.\n");

    add_item( ({ "snow" }),
      "There is no snow here at all, it's all been trodden into oblivion. " +
      "There is a lot of snow on the trees in the forest, and also in the " +
      "landscape visible from here.\n");

    add_item( ({ "ground", "footprint", "footprints" }),
      "Deeply frozen all year round, the ground never holds footprints.\n");

    add_item( ({ "monument", "statue" }),
      "It appears to be someone on a horse, modelled out of granite, and " +
      "facing away from you, towards the east.\n");

    add_exit(CALATHIN_DIR + "square1_1", "north", 0);
    add_exit(CALATHIN_DIR + "square2_2", "east", 0);
    add_exit(CALATHIN_DIR + "square1_3", "south", 0);

    room_add_object(CALATHIN_DIR + "obj/bank_door2");
    add_npc(CALATHIN_DIR + "npc/guiplayer");
}
