/* -*- Mode: C -*-
 *
 * m_chip.c
 *
 * Skippern 20(c)01
 *
 * a marble stone, chipped from a marble block.
 *
 */
#pragma strict_types

inherit "/std/object";

#include "../defs.h"
#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
public int     throw(string arg);


/*
 * Function name:    create_object
 * Description  :    Creates the object
 */
void
create_object()
{
    set_name("marble");
    set_short("marble pebble");
    add_name("stone");
    add_name("pebble");
    add_name("rock");

    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_WEIGHT, (85 * query_prop(OBJ_I_VOLUME) / 10));
    add_prop(OBJ_I_VALUE, (24 * query_prop(OBJ_I_WEIGHT) / 10));

    add_adj("marble");
    add_adj("of");
    add_adj("stone");
    add_adj("rock");

    set_long("It is a marble pebble. It looks like it have been knocked " +
	     "from a larger rock with a hammer.\n");
}

void
init()
{
    ::init();
    add_action("throw", "throw");
}

public int
throw(string arg)
{
    string terrain;
    object room_ob = environment(environment(this_object())), 
	tp = environment(this_object());

    notify_fail("Throw away what?\n");
    if (arg == "pebble")
    {
    tell_room(room_ob, QCTNAME(tp)+" throws a marble pebble.\n", tp);

    if (room_ob->query_prop(ROOM_I_INSIDE) != 0)
    {
	tell_room(room_ob, "The pebble hits the wall, and makes a small " +
		  "mark in it.\n", 0);
	this_object()->remove_object();
	return 1;
    }

    switch(terrain)
    {
    case "town":
	tell_room(room_ob, "The pebble disapairs in the crowd.\n", 0);
	break;
    default:
	tell_room(room_ob, "The pebble disapairs out of your sight.\n", 0);
	break;
    }
    this_object()->remove_object();
    return 1;
    }
    return 0;
}



