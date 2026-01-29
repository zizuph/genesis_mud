/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * ugnd3.c
 *
 * This room is underground. Mortricia 921023
 * Modified by Sorgum 941226
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include "enchanted.h"

object g1, g2, walker;

/*
 * Function name: reset_room
 * Description:   clone monsters at each reset.
 */
public void
reset_room()
{

    if (!g1) {
        g1 = clone_object(ENCHANT_DIR + "monster/griffin");
        g1 -> move(TO);
    }
    if (!g2) {
        g2 = clone_object(ENCHANT_DIR + "monster/griffin");
        g2 -> move(TO);
    }
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    set_short("Underground room");
    set_long("You are standing in an underground room. The air is " +
	     "not exactly refreshing. Some lanterns on the walls " +
	     "provide enough of guidelight.\n");
    
    add_item(({"lanterns"}) ,"They look as if they were maintained " +
			     "regularily.\n");

    add_prop(ROOM_I_HIDE,   80);
    INSIDE;

    add_exit(ENCHANT_DIR + "ugnd2", "north", 0);
    add_exit(ENCHANT_DIR + "ugnd4", "east", "@@go_east");

    reset_room();
}

go_east()
{
    string name;

    if (!g1 && !g2) return 0;
    name = lower_case(TP -> query_name());
    write("A griffin stops you from doing that.\n");
    if (TP == walker) {
	if (g1) g1 -> attack_object(TP);
	if (g2) g2 -> attack_object(TP);
    } else {
        if (g1) g1 -> command("stare " + name);
        if (g2) g2 -> command("stare " + name);
	write("It could be dangerous to try that once more.\n");
	walker = TP;
    }
    say(QCTNAME(TP) + " tried to go east, but failed.\n");
    return 1;
}
