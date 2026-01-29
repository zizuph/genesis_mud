/*
 * The actors club inner room
 */
#pragma strict_types

inherit "/std/room";

#include <std.h>
#include <macros.h>
#include <language.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>

#include "actor.h"

static nomask int do_initiate(string arg);

public nomask void
create_room()
{
    setuid();
    seteuid(getuid());
    
    set_short("A plush room");
    set_long("  You find yourself in a room decorated with various " +
        "pieces of stage material, sets and other acroutements of the " +
        "acting trade. In fact, it's almost hard to find a place to " +
        "stand among all the bric-a-brac.\n  " +
        "The east wall holds a placard with the title \"Actors Club " +
        "Manifesto\" and there's a sign hanging on the north wall.\n\n");

    add_item("sign", "@@read_sign");
    add_item(({"placard", "manifesto"}), "@@read_manifesto");

    add_cmd_item("sign", "read", "@@read_sign");
    add_cmd_item(({"placard", "manifesto"}), "read", "@@read_manifesto");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "south_of_sparkle.txt");

    add_exit(AC_INNER, "north", "@@enter_test", 1, "@@can_see_exit");
    add_exit(AC_ROOMS+"stage", "south");

    clone_object(AC_EBOARD)->move(this_object());
}

public nomask void
init()
{
    if (IS_WIZ(TP) || CHECK_MEMBER(TP))
    {
        add_action(do_initiate, "initiate");
    }

    ::init();
}

static nomask int
do_initiate(string arg)
{
    string name;
    object *oblist;

    if (!strlen(arg))
    {
	return 0;
    }

    name = lower_case(arg);

    if (!sizeof(oblist = PARSE_THIS(name, "[the] %l")))
    {
	notify_fail("Initiate whom?\n");
	return 0;
    }

    oblist->add_prop(IN_SANCT_PROP, 1);
    oblist->catch_msg("You have been initiated by " + QCTNAME(TP) + ". Just walk north from here to enter the inner sanctum of the club.\n");
    write("You have initiated " + COMPOSITE_WORDS(map(oblist, &->query_the_name(this_player()))) + ".\n");
    return 1;
}

public nomask string
read_sign()
{
    string mess;
    int wiz = IS_WIZ(TP);

    mess = "  If you want to get in touch with the members of the club, or if you have opinions you would like to make known to them, please feel free to use the board.\n  However, please be informed that you will not be invited to the club by asking for it here, you will have to prove your value as a roleplayer on your own first. If you're good people will see that. Soon enough you will then be approached by a member of the club and asked to join.\n";

    if (wiz || CHECK_MEMBER(TP))
	return "  You can invite non-members to the inner sanctum by typing 'initiate <player>'. The bulletin board in this room is intended for the use of non-members to communicate with you at need.\n\n  Non-members are given the following instruction:\n\n" + mess;
    else
	return mess;
}

public nomask string
read_manifesto()
{
    TP->more(AC_HELP + "general", 1);
    return "";
}

public nomask int
enter_test()
{
    int wiz = IS_WIZ(TP);
    
    if (!wiz && !CHECK_MEMBER(TP))
    {
	if (TP->query_prop(IN_SANCT_PROP) 
           || AC_CENTRAL->query_suggest(TP->query_real_name()))
	{
	    tell_room(this_object(), QCTNAME(TP) + " hesitantly " +
              "feels at the north wall, but " + TP->query_possessive() + 
              " hand just passes through without resistance, and " + 
               TP->query_pronoun() + " stumbles through head over heels.\n", TP);
	    return 0;
	}
	write("There is no obvious exit north.\n");
	return 1;
    }

    tell_room(this_object(), QCTNAME(TP) + " makes a gesture at " +
      "the north wall, which then becomes transparent for a " +
      "second or so, allowing " + TP->query_objective() + 
      " to pass through.\n", TP);

    return 0;
}

public nomask void
leave_inv(object to, object from)
{
    TP->remove_prop(IN_SANCT_PROP);
    ::leave_inv(to, from);
}

public nomask int
can_see_exit()
{
    int rval = 0;

    int wiz = IS_WIZ(TP);

    if (!wiz && CHECK_MEMBER(TP) != 1)
    {
	if (TP->query_prop(IN_SANCT_PROP))
	    rval = 0;
	else
	    rval = 1;
    }

    return rval;
}
