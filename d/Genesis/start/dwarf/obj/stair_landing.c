/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "../defs.h"

#define SHANDLER "/d/Genesis/start/dwarf/obj/stairhandler.c"

static int	escalator_on,	/* Escalator running or not */
    landing_number;	/* This landing number */

static string	this_side,	/* Which side of the stairway */
    other_side;	/* The other side of the stairway */

void
create_room()
{
    set_short("Stairway step");

    set_long(BS("\nYou are standing on a landing in a great winding stairway. The landing is merely a couple of yards of free space, but you sure can appreciate the opportunity to rest your feet a bit before taking on the next flight of steps.\n\n"));

    add_item(({"bannister"}),
	     BS("The bannister is carved in a hard, dark kind of wood. It is about a yard or so high and supported by massive pillars of carved rock at regular intervals. After inspecting it for a while, you realize that it's quite a masterly piece of woodwork. The stairwell is spiral with numerous landings, but despite this the bannister flows unbroken, without visible seams all the way from top to bottom. It is glossy and smooth from years of wear.\n"));

    add_exit("", "up", "@@move_up");
    add_exit("", "down", "@@move_down");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
}

void
init()
{
    ::init();

    add_action("jump_bannister", "jump", 0);
    add_action("look_over", "look", 0);
}

static int
look_over(string what)
{
    if (what == "over")
    {
	NF("Look over what?\n");
	return 0;
    }
    
    if (what != other_side && what != "over bannister")
	return 0;

    write("Looking over the bannister, you see:\n");

    SHANDLER->glance_landing(TP, other_side, landing_number);
    return 1;
}

static int
move_up()
{
    seteuid(getuid(TO));
    SHANDLER->move_player(TP, this_side, landing_number + 1, "up");
    return 1;
}

static int
move_down()
{
    seteuid(getuid(TO));
    SHANDLER->move_player(TP, this_side, landing_number - 1, "down");
    return 1;
}

static int
jump_bannister(string what)
{
    string foobar;

    if (what != "bannister" && what != "over bannister")
    {
	NF("Jump over what?\n");
	return 0;
    }

    write("You jump over the bannister.\n");
    SHANDLER->move_player(TP, other_side, landing_number, "jumping over the bannister");
    return 1;
}

public void
set_info(string s_side, int lnum)
{
    if (stringp(s_side))
    {
	this_side = s_side;
	other_side = this_side == "blue" ? "red" : "blue";
    
	add_my_desc(BS("A bannister separates this stairway from the one on the " + other_side + " side.\n\n"));
    }
    tell_room(TO, "The stairway rumbles.\n");
    
    landing_number = lnum;
}

public string
wizinfo()
{
    return BS("This is landing number " + landing_number + " on the " + this_side + " side of the bannister.\n");
}
