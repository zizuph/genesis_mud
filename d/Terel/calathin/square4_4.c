/* square4_4.c
 * metaprat - 920704
 * Updated by Shinto 10-19-98
 *
 * Jan 2021, Lucius - Modernized
 *
 * Town square, southeastern corner
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <ss_types.h>

public void
create_terel_room()
{
    set_short("Calathin Town Square, Southeast corner");
    set_long(
      "You are on the southeast corner of a bustling town square. A huge " +
      "pine tree is towering above you to the northwest. Between you and " +
      "the tree is a large stone monument. To your west and southwest " +
      "are two taverns that seem to be very popular with the locals. " +
      "Beyond the taverns are roads leading away from the square. " +
      "Looking to your east, you see the Calathin post office and a " +
      "playhouse just to the north of it. South of you lies the famous " +
      "Silver Tree Inn, where weary travellers can rest for the " +
      "night.\n");

    add_item( ({ "huge tree", "pine", "huge pine" }),
      "The tree looks like an ancient pine, about 100 meters tall or more. " +
      "It is towering above to the northwest.\n");

    add_item( ({ "buildings" }),
      "To the west, you see an inn and the pub. To your northeast, a "+
      "playhouse, further north of which is another building.\n");

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
      "facing east. No other details are visible from this " +
      "distance.\n");
/*
    add_cmd_item("onto post office roof","climb", "@@climb");
    add_cmd_item("onto the inn roof","climb", "@@climb_inn");
*/

    add_exit(CALATHIN_DIR + "square4_3", "north", 0);
    add_exit(CALATHIN_DIR + "square3_4", "west", 0);

    room_add_object(CALATHIN_DIR + "obj/silver_door2");
    room_add_object(CALATHIN_DIR + "obj/post_door2");
}

public int
climb()
{
    if (QRACE(TP) == "goblin" || QRACE(TP) == "gnome" ||
        QRACE(TP) == "dwarf" || QRACE(TP) == "hobbit" ||
        QRACE(TP) == "kender" || QRACE(TP) == "halfling")
    {
	if (TP->query_skill(SS_CLIMB) > 60)
	{
	    write("Your climbing skill, allows you to haul yourself onto the roof "+
	      "of the post office.\n");
	    TP->move_living("up",CALATHIN_DIR + "roofs/po_r");
	    return 1;
	}
	write("Your just too small to climb up onto the roof.\n");
	return 1;
    }
    if (TP->query_skill(SS_CLIMB) > 15)
    {
	write("You scramble up onto the roof of the Post Office.\n");
	TP->move_living("up",CALATHIN_DIR + "roofs/po_r");
	return 1;
    }
    write("You aren't skilled enough to climb up there.\n");
    return 1;
}

public int
climb_inn()
{
    if (QRACE(TP) == "goblin" || QRACE(TP) == "gnome" ||
        QRACE(TP) == "dwarf" || QRACE(TP) == "hobbit" ||
        QRACE(TP) == "kender" || QRACE(TP) == "halfling")
    {
	if (TP->query_skill(SS_CLIMB) > 60)
	{
	    write("Your climbing skill, allows you to haul yourself onto the roof "+
	      "of the inn.\n");
	    TP->move_living("up",CALATHIN_DIR + "roofs/inn_r");
	    return 1;
	}
	write("Your just too small to climb up onto the roof.\n");
	return 1;
    }
    if (TP->query_skill(SS_CLIMB) >15)
    {
	write("You scramble up onto the roof of the Silver Tree Inn.\n");
	TP->move_living("up",CALATHIN_DIR + "roofs/inn_r");
	return 1;
    }
    write("You aren't skilled enough to climb up there.\n");
    return 1;
}
