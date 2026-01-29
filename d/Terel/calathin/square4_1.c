/* square4_1.c
 * metaprat - 920703
 * Updated by Shinto 10-19-98
 *
 * Jan 2021, Lucius - Modernized
 *
 * Town square, northeastern side
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public void
create_terel_room()
{
    set_short("Calathin Town Square, Northeastern corner");
    set_long(
      "You are on the northeast corner of a bustling town square. A huge " +
      "pine tree is towering above you to the northwest, next to a road " +
      "going into the forest. To the southwest, you see a monument, and an "+
      "inn. In the far southwest are a couple of roads. Another road is " +
      "near the tree. To your east is a town hall, and southeast "+
      "is another building.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
      "The tree looks like an ancient pine, about 100 meters tall or more. " +
      "It is towering above to the northwest. You can see some kind of " +
      "entrance on the south side of the trunk, and a sign, which is too far "+
      "away to read.\n");

    add_item( ({ "buildings" }),
      "To your southwest, across the square, you can see an inn, and " +
      "east you see a town hall. South of the town hall is another building."+
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

    add_exit(CALATHIN_DIR + "square4_2", "south", 0);
    add_exit(CALATHIN_DIR + "square3_1", "west", 0);

    room_add_object(CALATHIN_DIR + "obj/arm_door2");
    room_add_object(CALATHIN_DIR + "obj/hall_door2");
}
