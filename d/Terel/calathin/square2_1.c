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

#include <tasks.h>
#include <ss_types.h>
#include <macros.h>

#define DIFFICULTY  (TASK_ROUTINE + 300)  /* 40 avg gives 50% success  */
#define DAMAGE      5                     /* damage is 5 + 10 * tree height */


public void
create_terel_room()
{
    set_short("Calathin Town Square, Northern edge");
    set_long(
      "You are on the northern edge of a bustling town square. A huge " +
      "pine tree is towering above you to the north, while a road goes " +
      "northwest past it. From this angle, you can see that there is a " +
      "door of some sort in the trunk of the tree. To the south, you see " +
      "a monument, and beyond it an inn next to a couple of roads leading " +
      "from the southwest corner of the square. To your east and southeast "+
      "are a couple of buildings.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
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

    add_item( ({ "door" }),
      "The shop door has been wedged open by the proprieter.\n");

    add_cmd_item( ({ "door" }), "open", "But its already open!\n");
    add_cmd_item( ({ "door" }), "close", "The door has been wedged open.\n");

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

    add_item( ({ "monument", "statue" }),
      "It appears to be someone on a horse, modelled out of granite, and " +
      "facing towards the east. No other details are visible from this " +
      "distance.\n");

    add_item( ({ "sign" }),
      "The sign says: 'General store'. It's hanging off a bracket, above " +
      "the shop door.\n");

    add_item( ({ "bracket" }),
      "This is a pretty sturdy piece of iron, about 2 meters off the ground. "+
      "It's probably too high for the local kids to climb up, but someone " +
      "who's an adult could probably climb onto it.\n");

    add_cmd_item( "sign", "read",
      "The sign says: 'General store'. It's hanging off a bracket, above " +
      "the shop door.\n");

    add_cmd_item(
      ({ "tree", "huge tree", "pine", "huge pine", "huge pine tree", "up" }),
      "climb",
      "What are you going to climb onto? The bark is very icy.\n");

    add_cmd_item(
      ({ "onto bracket", "bracket", "onto sign", "sign" }),
      "climb", "@@climb_tree");

    add_exit(CALATHIN_DIR + "square3_1", "east", 0);
    add_exit(CALATHIN_DIR + "square2_2", "south", 0);
    add_exit(CALATHIN_DIR + "square1_1", "west", 0);
    add_exit(CALATHIN_DIR + "roads/road_n01", "northwest", 0);

    room_add_object("/d/Genesis/obj/donation/column");
    room_add_object(CALATHIN_DIR + "obj/pack_door2.c");
    add_npc(CALATHIN_DIR +"npc/std_move_guard");
}


/* climb() taken from /doc/examples/room/sc_room */

public int
climb_tree()
{
    /* Uses Quis's Tasks system, read /doc/man/general/tasks */
    int success;

    success = this_player()->
    resolve_task(DIFFICULTY, ({ SKILL_WEIGHT, 600, SS_CLIMB,
	SKILL_WEIGHT, 150, SS_DEX }) );

    /* pathetic attempt, falls over with minor injury */
    if (success < -30)
    {
	write(
	  "You reach up to the sign's bracket, and try to climb onto it. "+
	  "However, as you pull yourself onto it, you overbalance, and " +
	  "fall back to the ground, with a heavy thump. Ouch!\n");
	say(QCTNAME(TP) + " tried to climb onto the bracket, " +
	  "but falls.\n");
	TP->reduce_hit_point(DAMAGE);
	return 1;
    }
    /* failed to get up, but didn't get injured */
    if (success < 0)
    {
	write(
	  "You reach up to the sign's bracket, and try to pull yourself " +
	  "up, but your hands slip, and you fall back to the ground. " +
	  "Fortunately, you land on your feet, injuring nothing but your " +
	  "pride.\n");
	say(QCTNAME(this_player()) + " tried to climb onto the bracket, " +
	  "but falls.\n");
	return 1;
    }
    /* gut up, but only just */
    if (success < 30)
    {
	write(
	  "You pull yourself up onto the sign's bracket, and, wobbling, " +
	  "try to stand up. Somehow you manage it, and pause for a while, "+
	  "to get your breath back.\n");
	TP->move_living("climbing onto a sign", CALATHIN_DIR + "tree1");
	return 1;
    }
    /* got up easily */
    write(
      "You climb up onto the sign's bracket with ease, and stand upright "+
      "in an easy movement.\n");
    TP->move_living("climbing onto a sign", CALATHIN_DIR + "tree1");
    return 1;
}
