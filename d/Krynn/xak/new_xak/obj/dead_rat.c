/*
 * Bupu's dead rat.
 * By Rastlin
 */
inherit "/std/object";

#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

public void
create_object()
{
    set_name("rat");
    set_adj("dead");

    set_long("It is a dead rat. Nothing more and nothing less.\n");

    add_prop(OBJ_I_WEIGHT, 650);
    add_prop(OBJ_I_VOLUME, 460);

    add_prop(OBJ_M_NO_SELL, "You can't sell a dead rat.\n");
}

public int
do_press(string str)
{
    string what2;
    object what1;

    NF("Press what against what?\n");
    if (!str || !strlen(str))
        return 0;

    if (parse_command(str, environment(), "%o 'to' / 'against' [east] %s", 
		      what1, what2))
    {
        if (what1 != TO)
	    return NF("You can't press that against anything.\n");

        if (what2 != "wall")
	    return NF("There is no need to press the dead rat against " + 
		      "that.\n");

	if (!E(TP)->query_prop(ROOM_I_INSIDE))
	    return NF("You can't find any walls here.\n");

	if (E(TP)->query_rat_room())
	{
            write("Just when you are about to press the dead rat " +
		  "against the wall,");
	    tell_room(E(TP), QCTNAME(TP) + " approches the east wall " +
		      "with a dead rat in " + POSSESSIVE(TP) + " hand. " +
		      "Just as " + PRONOUN(TP) + " is about to press " + 
		      "the dead rat against the wall,", TP);
	    tell_room(E(TP), " the wall starts to shiver, " +
		  "and within seconds, a doorway appears, " +
		  "leading into darkness.\n");

	    E(TP)->open_secret_door();
	    return 1;
	}

	tell_room(E(TP), QCTNAME(TP) + " starts pressing a dead rat " +
		  "against a wall. You start to wonder if everything " +
		  "is as it should be.\n", TP);
	write("You start to press the dead rat against the wall.\n");
	write("Feeling silly??\n");
	return 1;
    }
    return 0;
}

public void
init()
{
    ::init();
    add_action(do_press, "press");
}
