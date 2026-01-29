/*
 * square1_4.c
 * metaprat - 920703 remade 920728 Redhawk:-)
 * Updated by Shinto 10-19-98
 *
 * Jan 2021, Lucius - Modernized
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public void
create_terel_room()
{
    set_short("Calathin Town Square, Southwest corner");
    set_long(
      "You are in the southwest corner of a bustling town square. A huge " +
      "pine tree is towering above you to the north, just past a small " +
      "winding road. An inn and a pub are to the east. On the opposite "+
      "side of the square, a couple of buildings are visible through the " +
      "mist. A road enters from the south, while another one enters from " +
      "the west. In the middle of the square, northeast, you can see a "+
      "large stone monument. A large weapon shop has an entrance just "+
      "west of here. It appears that Calathin is fairly civilized.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
      "The tree looks like an ancient pine, about 100 meters tall or more. " +
      "It is towering above to the north.\n");

    add_item( ({ "buildings" }),
      "To your east, you can see an inn and a pub, while to the northeast " +
      "you see an outline of a couple of buildings through the mist.\n");

    add_item( ({ "town square", "square" }),
      "The square is bustling with people.. maybe it's market day here?\n");

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
      "facing away from you, towards the east.\n");

    add_item( ({ "mountain", "mountains" }),
      "A range of mountains, barely visible through the mist.\n");

    add_exit(CALATHIN_DIR + "square1_3", "north", 0);
    add_exit(CALATHIN_DIR + "square2_4", "east", 0);
    add_exit(CALATHIN_DIR + "roads/road_w01", "west", 0);
    add_exit(TOWNDIR + "street/street0","south", 0);
//    add_exit(CALATHIN_DIR + "roads/road_e01", "southeast", 0);
//    room_add_object(CALATHIN_DIR + "obj/lamp_door2");
    add_npc(CALATHIN_DIR + "npc/std_move_guard");
}

