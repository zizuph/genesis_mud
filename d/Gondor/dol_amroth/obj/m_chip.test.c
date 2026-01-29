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
    int    ter_tot;
    object room_ob = environment(environment(this_object())), 
	tp = environment(this_object());

    notify_fail("Throw away what?\n");
    if (arg == "pebble")
    {
    tell_room(room_ob, QCTNAME(tp)+" throws a marble pebble.\n", tp);

    // Make some code so the pebble can be throwed on livings.

    if (room_ob->query_prop(ROOM_I_INSIDE) != 0)
    {
	tell_room(room_ob, "The pebble hits the wall, and makes a small " +
		  "mark in it.\n", 0);
	this_object()->remove_object();
	return 1;
    }

    /* I need some code here to determine what type of terrain the player are in.
     * We want different messages for different types of terrain (disapairs in the wood,
     * in the crowd, in the bushes etc) */
    ter_tot = room_ob->query_prop(ROOM_I_TERRAIN_TYPE);
    if (ter_tot)
    {
        if (ter_tot - TERRAIN_HASDEAD)
	    ter_tot -= TERRAIN_HASDEAD;
	if (ter_tot - TERRAIN_RESIDENCE)
	{
	    ter_tot -= TERRAIN_RESIDENCE;
	    terrain = "town";
	}
	if (ter_tot - TERRAIN_CROWDED)
	{
	    ter_tot -= TERRAIN_CROWEDED;
	    terrain = "town";
	}
	if (ter_tot - TERRAIN_SHADOWS)
	    ter_tot -= TERRAIN_SHADOWS;
	if (ter_tot - TERRAIN_STEEP)
	    ter_tot -= TERRAIN_STEEP;
	if (ter_tot - TERRAIN_ROUGH)
	    ter_tot -= TERRAIN_ROUGH;
	if (ter_tot - TERRAIN_SMALL_PLANT)
	    ter_tot -= TERRAIN_SMALL_PLANT;
	if (ter_tot - TERRAIN_TALL_PLANT)
	    ter_tot -= TERRAIN_TALL_PLANT;
	if (ter_tot - TERRAIN_CLUTTER)
	    ter_tot -= TERRAIN_CLUTTER;
	if (ter_tot - TERRAIN_SOIL)
	    ter_tot -= TERRAIN_SOIL;
	if (ter_tot - TERRAIN_SAND)
	    ter_tot -= TERRAIN_SAND;
	if (ter_tot - TERRAIN_ROCK)
	    ter_tot -= TERRAIN_ROCK;
	if (ter_tot - TERRAIN_WET)
	    ter_tot -= TERRAIN_WET;
	if (ter_tot - TERRAIN_IMPURE)
	    ter_tot -= TERRAIN_IMPURE;
    }
    else
        terrain = "default";

    switch(terrain)
    {
    case "town":
	tell_room(room_ob, "The pebble disapairs in the crowd.\n", 0);
	break;
    case "forest":
	tell_room(room_ob, "The pebble disapairs between the trees.\n", 0);
    case "field":
	tell_room(room_ob, "The pebble disapairs in the bushes.\n", 0);
	break;
    case "rocks":
	tell_room(room_ob, "The pebble disapairs among the other rocks.\n", 0);
	break;
    case "water":
	tell_room(room_ob, "The pebble disapairs into the water.\n", 0);
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



