/* square4_3.c
 * metaprat - 920704
 * Additions by Om - 920721
 * Updated by Shinto 10-19-98
 *
 * Jan 2021, Lucius - Modernized
 *
 * Town square, eastern side
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public void
create_terel_room()
{
    set_short("Calathin Town Square, Eastern side");
    set_long(
      "You are on the eastern side of a bustling town square. A huge " +
      "pine tree is towering above you to the northwest, next to a road " +
      "going into the forest. To the west, you see a monument. South of "+
      "the monument is an inn and a pub. In the far southwest are a couple "+
      "of roads. To your north is a town hall, and east a playhouse.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
      "The tree looks like an ancient pine, about 100 meters tall or more. " +
      "It is towering above to the northwest.\n");

    add_item( ({ "buildings" }),
      "To your southwest, across the square, you can see an inn, and a pub. "+
      "To your north, a town hall, and directly east, a playhouse.\n");

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
      "facing towards you. No other details are visible from this " +
      "distance.\n");

    add_exit(CALATHIN_DIR + "square4_2", "north", 0);
    add_exit(CALATHIN_DIR + "square4_4", "south", 0);
    add_exit(CALATHIN_DIR + "square3_3", "west", 0);

    room_add_object(CALATHIN_DIR +"obj/play_door2");
    add_npc(CALATHIN_DIR + "npc/recplayer");
}
