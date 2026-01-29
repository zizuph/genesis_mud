/*
 * Standard room for Europe
 */

#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "/d/Europe/defs.h"

inherit "/std/room";

public void
create_europe_room()
{
}

public void
reset_europe_room()
{
}

public int
query_latitude()
{
    return 60;
}

public void
create_room()
{
    create_europe_room();
    reset_room();
}

/*
 * Function name: reset_room
 * Description:   This resets a room. reset_room calls reset_europe_room
 *                which should be defined in your area if you need it.
 * NOTE: When everything works, remove this line and make the function nomask 
 */
public void
reset_room()
{
    this_object()->reset_europe_room();
}

public int
query_sun_position()
{
    return CLOCK->query_sun_position(TO->query_latitude());
}

int
check_time(string s)
{
    if (strlen(s)) return 0;
    write("It is "+CLOCK->describe_sun_position(query_sun_position())+" on "+CLOCK->name_today()+".\n");
    return 1;
}

/*
 * Function name: init
 * Description:   Give the room commands to a player. This Europe room
 *                init adds the cmd_parse_action commands for the room.
 *                (see 'kman add_cmd_parse').
 */
void
init()
{
    ::init();
    add_action("check_time", "time");
}


/*
 * Function name: clean_up
 * Description:   This function destructs the room if there is nothing in it.
 *                If you have special variables stored in a room you should
 *		  define your own clean_up(). Also if you on startup of the
 *		  room clone some objects and put inside it, please define
 *		  your own clean_up() to destruct the room. This saves a
 *		  lot of memory in the game.
 * Returns      : int 1/0 - call me again/ don't bother me again.
 */
public int
clean_up()
{
    if(!query_prop(ROOM_I_NO_CLEANUP) &&
	!sizeof(all_inventory(this_object()) + accept_here))
      {
	return 1;
      }

    return ::clean_up();
}

/* 
 * Function name: add_invis_exit
 * Description:   Add one exit to the room which will never be shown,
 *                independantly of the no_show_obvious state.
 * Arguments:	  place: The filename of the room to move to
 *                cmd:   The command given to move
 *                efunc: The delay value often given by 'value by function
 *			 call'. The delay values are:
 *			 0: Direct move to destination
 *			 =1: Can not move in this dir, do not try others
 *			 >1: Can not move to destination, but try the rest
 *			 <0: Move is done with delay (see link_room)
 *		  tired: How much more tired the player should become from
 *			 walking in that direction. Default is 1.
 * NOTE:          We keep this function just for backwards compatability.
 *                Use the extended add_exit functionality for new code!
 */
public varargs int
add_invis_exit(string place, string cmd, mixed efunc, mixed tired)
{
    return add_exit(place, cmd, efunc, tired, 1);
}

/*
 * query_prop masks
 */

public mixed
query_prop(string prop)
{
    if (prop == ROOM_I_LIGHT && !query_prop(ROOM_I_INSIDE))
	return CLOCK->query_light_level(TO->query_latitude());
    if (prop == "_room_i_sunlight" && !query_prop(ROOM_I_INSIDE))
	return CLOCK->query_sunlight_level(TO->query_latitude());
    return ::query_prop(prop);
}


/* 
 * Climate description, according to sun, clock and placement.
 */

public string query_area_name()
{
    return "Europe";
}

public string describe_climate()
{
    return 
        "It is " +
        CLOCK->describe_sun_position(TO->query_sun_position()) +
        " in " + query_area_name() + ", and the temperature is " +
        CLOCK->query_temperature(TO->query_latitude()) + ". " +
        CLOCK->query_weather(TO->query_latitude());
}
