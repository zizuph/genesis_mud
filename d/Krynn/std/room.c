/*
 * Standard room for 'all' rooms in Krynn.
 *
 * Revision history:
 * /Rastlin, 950202, first version.
 * /Rastlin, 950207, added the function add_cmd_parse
 * /Rastlin, 950213, general speedup (Thanks Mercade!)
 * /Rastlin, 950214, made create_room() call create_krynn_room()
 *		     and added a prototype of calc_room_hide()
 * /Rastlin, 950216, added add_search written by Aridor
 *		     (slightly modifed by Rastlin)
 * ~Aridor,  960910, added automatic_reset.
 * Cotillion,201026, Disable reset using disable_reset() instead 
 */

#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/room";

#include "/d/Krynn/std/room/search.c"
#include "/d/Krynn/std/room/hide.c"
#include "/d/Krynn/std/room/cmd_parse.c"
#include "/d/Krynn/std/room/tell.c"
#include "/d/Krynn/std/room/time.c"
#include "/d/Krynn/std/room/autoreset.c"

static string area_handler;

/*
 * Prototypes
 */

string query_area_handler();

/*
 * Function name: create_krynn_room
 * Description:   Called to construct a room in Krynn. Read 'kman room.doc'
 *                to see how this is used in your area.
 */
public void
create_krynn_room()
{
}

/* 
 * Function name: reset_krynn_room
 * Description:   This is called periodically in the room to
 *                reset it.
 */
public void
reset_krynn_room()
{
}

/*
 * Function name: create_room
 * Description:   This is the general create_room() for Krynn.
 *                It will call create_krynn_room() which should be defined
 *                in a room_base file in your area.
 *
 * NOTE: When everything works, remove this line and make the function nomask!!
 */
public void
create_room()
{
    mixed calls;
    int i;

    INSIDE;
    this_object()->setup_o_krynn_room();
    create_krynn_room();
    calc_room_hide();

    if (!query_auto_reset_number() && !query_auto_reset_table() &&
        !area_handler &&
	((function_exists("reset_krynn_room", this_object()) ==
            "/d/Krynn/std/room") || (function_exists("query_reset",
                this_object()) && !this_object()->query_reset())))
    {
        disable_reset();
    }
    
    if (!query_prop(ROOM_I_INSIDE))
    {
	add_prop("_room_i_sunlight", CLOCK->query_sunlight_level);
    }

    query_area_handler()->room_created(this_object());
}

/*
 * Function name: reset_room
 * Description:   This resets a room. reset_room calls reset_krynn_room
 *                which should be defined in your area if you need it.
 * NOTE: When everything works, remove this line and make the function nomask 
 */
public void
reset_room()
{
    this_object()->set_searched(0);
    automatic_reset();
    this_object()->reset_krynn_room();
    
    query_area_handler()->room_reset(this_object());
}

/*
 * Function name: init
 * Description:   Give the room commands to a player. This Krynn room init
 *                adds the cmd_parse_action commands for the room.
 *                (see 'kman add_cmd_parse').
 */
void
init()
{
    ::init();
    
    add_action(check_time, "time");
    
    init_cmdparse();
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
    /* There are problems with doors in Krynn. Until another fix is found,
     * we disable cleanup for all rooms with doors.
     */
  /*
    mixed res = filter(all_inventory(this_object()),
		       operator(!)@operator(!)@&function_exists("create_door",));
    if (res && sizeof(res) > 0)
      return 0;
      */

    /* Doors aren't the only problem. This should help out */
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
 * Function Name: set_area_handler
 * Description  : Sets the object that should be notified of resets
 *                etc. for this area.
 *
 */
void
set_area_handler(string file)
{
    area_handler = file;
}

/*
 * Function name: query_area_handler
 * Description  : Returns the object handlign this area.
 */
string
query_area_handler()
{
    return area_handler;
}
