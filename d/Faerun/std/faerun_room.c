/*
 *  faerun/std/faerun_room.c
 *
 *  Standard room for the entire Faerun region.
 *
 *  Created by Wully, 12-2-2004
 *******************************************************************************
 * THIS FILE IS OUT DATED. USE room.c INSTEAD. 
 * THIS FILE IS KEPT HERE FOR BACKWARDS COMPATIBILITY.
 *******************************************************************************
 */
#pragma no_clone
#pragma ave_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit "/std/room";

inherit FAERUN_ROOM_TELL_BASE;
inherit FAERUN_ITEM_BASE;

// This should not be included but inherited!
#include "weather_file.c"


//  1 = castleward, 2 = woodlands, 3 = desert. >>Testing testing<< 
static private int wType;

/*
 * Function name: create_faerun_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_faerun_room(void)
{
    // Redefine this
}

/* 
 * Function name: create_room
 * Description  : Constructor, redefined so we can set some default properties
 */
public nomask void
create_room(void)
{
    // Call the faerun_room constructor so that people can configure the room
    // since this function cannot be masked.
    
    add_prop(ROOM_I_INSIDE, 0);
    set_long("\nBUG: THIS ROOM NEEDS A DESCRIPTION!\n");
    create_faerun_room();
}

/*
 * Masked to allow us to manage room tells.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (query_interactive(ob))
		start_room_tells();
}


/*
 * Tilorop's experimenting area, Weather system.
 */
public int
set_castleward(void)
{
    wType = 1;
}

public int
set_woodland(void)
{
    wType = 2;
}

public int
set_desert(void)
{
    wType = 3;
}


public string
query_weather(void)
{
    /*	if (this_object()->query_prop(ROOM_I_INSIDE))
		return "";

    switch(wType)
    {
    case 1:
    case 2:
    case 3:
		return ""+q_wind()+" and "+q_cloud()+" "+q_prec()+" "+q_temp()+"\n";
    default:
		return "";
    }*/
    
    return "";       // Disabled temporary until solved. Tilorop 15/7/05
}

public string
query_weather_type(void)
{
    switch(wType)
    {
    case 1:
     	return "Warm Desert.\n";
    case 2:
     	return "Woodlands.\n";
    case 3:
     	return "Castleward.\n";
    default:
	return "Buggy weatherterrain.\n";
    }
}

/*
 * Fix to get rid of the obnoxius 'What ?' when we try to walk in a nonexistant
 * direction. These are the default direction commands in the prefferred order.
 */
#define DEF_DIRS ({ "north", "east", "south", "west", \
    "northeast", "northwest", "southeast", "southwest", "up", "down" })

/*
 * The following two sort functions are used to sort the exits in
 * a specific, unified format.  Check the DEF_DIRS define for the
 * sorted order of the standard exits.  All other exits will be
 * added in AFTER those 10 in alphabetical order.
 * And yes, I know it looks like an ugly hack, but it DOES work. ;)
 */
static nomask int
sort_alpha(string one, string two)
{
    if (one > two)
		return 1;
    if (one < two)
		return -1;
    return 0;
}

static nomask int
resort_exits(string one, string two)
{
    int a, b;

    a = member_array(one, DEF_DIRS);
    b = member_array(two, DEF_DIRS);

    if (a >= 0 && b == -1)
		return -1;
    if (a == -1 && b >= 0 )
		return 1;
    if (a == b)
		return sort_alpha(one, two);
    if (a > b)
		return 1;
    if (a < b)
		return -1;
    return 0;
}

/* This is masked to sort the exits. */
public string *
query_obvious_exits(void)
{
    string *obv_exits = ::query_obvious_exits();

    if (obv_exits)
		obv_exits = sort_array(obv_exits, resort_exits);

    return obv_exits;
}

/* If weather is present, it will be tacked onto the end
 * of the long description of a room.  */
public varargs mixed
long(string str)
{
	string weather, result = ::long(str);

	if (strlen(str))
		return result;
	else
		weather = query_weather();

    return result + (strlen(weather) ? " " + weather : "");
}

/*
 * This is maskable by areas that may wish to do so.
 * The argument is not currently used.
 */
public int
faerun_time(string str)
{
    string *arr;

	/* This assumes we are overriding the default terrain type. */
	/*if (this_object()->terrain_includes_any(TERRAIN_UNDERGROUND) ||
		this_object()->terrain_includes_any(TERRAIN_UNDERWATER) ||
		!this_object()->terrain_includes_any(TERRAIN_OUTSIDE) ||
		!this_object()->query_prop(ROOM_I_INSIDE))*/
		
	if (this_object()->query_prop(ROOM_I_INSIDE))
	{
		write("It's too difficult to determine the time while indoors.\n");
		return 1;
	}

	/* The output will wrap, so we split it and indent the second line. */
    arr = explode(TIME_DESC_LONG, ", ");
    write(implode(arr[0..1], ",\n\t") + ", " + arr[2] + "\n");
    return 1;
}

public void
init(void)
{
    ::init();

	/* Add the domain-wide general-purpose 'time' command. */
    add_action(faerun_time, "time");
}
