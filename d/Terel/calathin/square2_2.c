/*
 * square2_1.c
 * metaprat - 920629
 * Updated by Shinto 10-19-98
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
      "the tree. To the south, you see a monument, and beyond that " +
      "the inn, next to a couple of roads leading from the southwest " +
      "corner of the square. To your east are a couple of buildings. " +
      "\n");

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

    add_item("shop",
      "The shop is open, and is to the north, within the tree.\n");

    add_item("door",
      "The shop door has been wedged open by the proprieter.\n");

    add_cmd_item("door", "open", "But its already open!\n");
    add_cmd_item("door", "close", "The door has been wedged open.\n");

    add_item( ({ "town square", "square" }),
      "The square is bustling with people... maybe it's market day here?\n");

    add_item( ({ "mist", "icy mist" }),
      "The mist is just the effect of the chill weather on the water vapor " +
      "in the air.\n");

    add_item("snow",
      "There is no snow here at all, its all been trodden into oblivion. " +
      "There is a lot of snow on the trees in the forest, and also in the " +
      "landscape visible from here.\n");

    add_item( ({ "ground", "footprint", "footprints" }),
      "Deeply frozen all year round, the ground never holds footprints.\n");

    add_item( ({ "monument", "statue" }),
      "It appears to be someone on a horse, modelled out of granite, and " +
      "facing towards the east. No other details are visible from this " +
      "distance.\n");

    add_item("sign",
      "It is too far to read from here. It hangs from a bracket, above "+
      "the shop door.\n");

    add_item("bracket",
      "This is a pretty sturdy piece of iron, about 2 meters off the ground. "+
      "Its probably too high for the local kids to climb up, but someone " +
      "who's an adult could probably climb onto it.\n");

    add_cmd_item(
      ({ "tree", "huge tree", "pine", "huge pine", "huge pine tree", "up" }),
      "climb",
      "What are you going to climb onto? The bark is very icy...\n");

    add_exit(CALATHIN_DIR + "square2_3", "south", 0);
    add_exit(CALATHIN_DIR + "square2_1", "north", 0);
    add_exit(CALATHIN_DIR + "square1_2", "west", 0);
    add_exit(CALATHIN_DIR + "square3_2", "east", 0);

    add_npc(CALATHIN_DIR + "npc/g_monger");
}
