/* square2_3.c
 * metaprat - 920629
 * Updated by Shinto 10=19-98
 *
 * Jan 2021, Lucius - Modernized
 *
 * Town square.
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public void
create_terel_room()
{
    set_short("Calathin Town Square, central");
    set_long(
      "You are in the central portion of the bustling town square. " +
      "A pine tree towers above you to the north, while a road goes " +
      "northwest past it. You can make out a doorway in the trunk of " +
      "the tree. There is a monument here that you can look at, " +
      "and further south is an inn, next to a couple of roads " +
      "leading from the southwest corner of the square. To your " +
      "northeast are a couple of buildings.\n");

    add_item( ({ "huge tree", "pine", "tree", "huge pine" }),
      "The tree looks like an ancient pine, about 100 meters tall or more. " +
      "It is towering above to the north. You can see some kind of " +
      "entrance on the south side of the trunk, and a sign, swinging above "+
      "the door.\n");

    add_item( ({ "buildings" }),
      "To your south, across the square, you can see an inn, while to the " +
      "east you see a town hall and another unidentified building. To the " +
      "north, you can see an entrance leading into the huge pine tree, " +
      "which appears to be fairly busy.\n");

    add_item( ({ "shop" }),
      "The shop is open, and is to the north, within the tree.\n");

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
      "It is a fine statue, made from granite, of a man on a horse. " +
      "He wears many fine furs and hides, and is wielding a longbow, " +
      "with an arrow ready to fire. His hair is blowing in the wind.\n");

    add_item( ({ "sign" }),
      "It is too far to read from here. It hangs from a bracket, above "+
      "the shop door.\n");

    add_item( ({ "bracket" }),
      "This is a pretty sturdy piece of iron, about 2 meters off the ground. "+
      "It's probably too high for the local kids to climb up, but someone " +
      "who's an adult could probably climb onto it.\n");

    add_exit(CALATHIN_DIR + "square2_2", "north", 0);
    add_exit(CALATHIN_DIR + "square2_4", "south", 0);
    add_exit(CALATHIN_DIR + "square1_3", "west", 0);
    add_exit(CALATHIN_DIR + "square3_3", "east", 0);

    add_npc(CALATHIN_DIR +"npc/std_citizen");
}
