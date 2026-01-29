/*
 *square1_3.c
 * metaprat - 920703
 * Updated by Shinto 10-19-98
 *
 * Jan 2021, Lucius - Modernized
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public static int aid = 0;

public void
reset_terel_room()
{
    aid = 0;
}

public void
create_terel_room()
{
    set_short("Calathin Town Square, western edge");
    set_long(
      "You are in the southwestern side of a bustling town square. A huge " +
      "pine tree is towering above you to the northeast, just past a small " +
      "winding road. An inn is southeast, next to a pub, which is further "+
      "east. On the opposite side of the square, you can see a couple " +
      "of buildings looking out through the mist. To the south, a couple " +
      "of roads leave the square, going west and south. The middle " +
      "of the square is to the northeast, while a large monument " +
      "faces away from you to the east.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
      "The tree looks like an ancient pine, about 100 meters tall or more. " +
      "It is towering above to the northeast.\n");

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

    add_exit(CALATHIN_DIR + "square1_2", "north", 0);
    add_exit(CALATHIN_DIR + "square2_3", "east", 0);
    add_exit(CALATHIN_DIR + "square1_4", "south", 0);

    room_add_object(CALATHIN_DIR + "obj/meat_door2");
    add_npc(CALATHIN_DIR + "npc/std_move_citizen", 2);
}

public void
wave_clue()
{
    tell_room(TO,
      "The tall long-legged human says: Well, I blame the town guard.\n"+
      "The tall long-legged human says: " +
      "All these deaths, and they've done nothing...\n" +
      "The dark-haired blue-eyed elf says: Let's talk elsewhere, huh?\n" +
      "The dark-haired blue-eyed elf leaves east.\n" +
      "The tall long-legged human leaves east.\n");
}

public void
init()
{
    ::init();
    if (!aid && interactive(this_player()))
	aid = set_alarm(1.0, -1.0, wave_clue);
}

