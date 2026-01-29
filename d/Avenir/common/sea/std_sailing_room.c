/*
*
* Based off sailing room code /d/Krynn/std/sail_room_base.c
* 
* To be used for Sparkle sailing rooms outside of that region.
*
* by Arman April 2021
*/

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>

// Includes mariner standardised sailing code
#include "/d/Krynn/std/boats/std_boat_defs.h"

#pragma save_binary

inherit "/std/room";

/* Global Variables */
string sink_path;
string *row_exits_arg = ({ });
string *row_exits_path = ({ });
int *row_exits_tired = ({ });
mixed *row_exits_check = ({ });

object *boats = ({ }); 

string boat_vista; 

int sailing_difficulty = 0;
mixed sailing_difficulty_message = 0;
mixed sailing_fail_message = 0;

#define CREATE "create_sea_room"
#define RESET "reset_sea_room"

public string
sea_short()
{
    string str = "on the high seas";
    
    return str;
}


public string
sea_desc()
{
    string str = "It is a warm spring day on the high seas. " +
        "Surprisingly, it is rather calm at the moment as " +
        "this savage ocean is renown for its severe weather. ";
    
    return str;
}

/* Redefine if you use the std_sailing_room for a lake or freshwater
   river to "freshwater". See /d/Krynn/common/fishing/
*/

public string
query_fishing_area()
{
    return "saltwater";
}

/* This next function is essential when it comes to removing the drown 
   object. Imagine if one leaves a standard water room into an area with
   non-standard underwater rooms.. the drown object will stay, but it will
   not get removed if they then go to an ordinary room. */
int
query_standard_water_room()
{
    return 1; 
}

void
boat_enter(object b)
{
    boats = filter(boats, objectp); 
    boats += ({ b }); 
}


void
boat_exit(object b)
{
    boats = filter(boats, objectp); 
    boats -= ({ b }); 
}


object 
*query_boats()
{
    boats = filter(boats, objectp); 
    return boats; 
}


void
set_boat_vista(string s)
{
    boat_vista = s; 
}


string
query_boat_vista()
{
    return boat_vista;
}


/* Returns the appropriate desc to be added for the row exits */
string
row_exit_desc()
{
    string desc;

    desc = "";
    if (sizeof(row_exits_arg))
        desc += ("You may sail: " + COMPOSITE_WORDS(row_exits_arg)+".\n");

    return desc;
}

/* Set the path to the room where things will sink to, if any. 
   Non living objects will automatically sink to that exit. 
   You don't have to set this if you want things to sink "down", as
   this is done by default if you add a swim exit for that direction. */
void
set_sink_path(string sp)
{
    sink_path = sp;
}


string
query_sink_path()
{
    return sink_path;
}

/* Code to check the sailing skill requirement of the sailor for
 * this particular room.
 */

public void
set_sailing_difficulty(int skill)
{
    sailing_difficulty = skill;
}

public int
query_sailing_difficulty()
{
    return sailing_difficulty;
}

public void
set_sailing_difficulty_message(string msg)
{
    sailing_difficulty_message = msg;
}

public mixed
query_sailing_difficulty_message()
{
    return sailing_difficulty_message;
}

public void
set_sailing_fail_message(string msg)
{
    sailing_fail_message = msg;
}

public mixed
query_sailing_fail_message()
{
    return sailing_fail_message;
}

public string
query_sailing_difficulty_desc()
{
    int difficulty = query_sailing_difficulty();

    switch(difficulty)
    {
        case 0..29:
            return "";
        case 30..50:
            return "The waters here are tricky to navigate. ";
        case 51..75:
            return "The waters here are challenging to navigate. ";
        case 76..90:
            return "The waters are extremely challenging to navigate. ";
        case 91..100:
            return "The waters here are near impossible to navigate. ";
        default:
            return "";
    }

}



/*
* IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
*/

nomask public int
query_reset()
{
   if (function_exists(RESET, TO))
      return 1;
   return 0;
}

public void
create_room()
{
    call_other(TO, CREATE);

    set_sink_path(ROOM + "sink_room");  
}

string
dir_alias(string str)
{
    switch (str) { 
        case "n" : return "north"; 
                   break;
        case "s" : return "south"; 
                   break;
        case "e" : return "east"; 
                   break;
        case "w" : return "west"; 
                   break;
        case "nw" : return "northwest"; 
                   break;
        case "ne" : return "northeast"; 
                   break;
        case "se" : return "southeast"; 
                   break;
        case "sw" : return "southwest"; 
                   break;
        case "u" : return "up"; 
                   break;
        case "d" : return "down"; 
                   break;
     }
     return str;
}


/*
 * This is the function which checks the rowing action and makes 
 * the call to carry out the row if it's possible. 
 * It is called from the inside of the rowing boat itself when a 
 * player does an action there. 
 */

int
try_row(string str)
{
    int i, tired, tmp;
    object tp = this_player();
    object row_to;
    object charter_captain = environment(tp)->query_owner();

    if(tp != charter_captain)
    {
        if(charter_captain->id("_ansalon_charter_captain"))
            tp = charter_captain; 
    }

    if (!str)
    {
	notify_fail("Sail where?\n");
	return 0;
    }

    str = dir_alias(str);

    i = member_array(str, row_exits_arg);

    if (i == -1)
    {
	notify_fail("You can't sail in that direction.\n");
	return 0;
    }

    if (this_object()->check_call(row_exits_check[i])) 
        return 1;

    tired = row_exits_tired[i]; 

    if (tp->query_fatigue() < tired) 
    {
        notify_fail("You are too tired to sail anywhere at the moment. " +
            "You decide to drift where you are.\n"); 
        return 0;
    }

    if (sizeof(row_exits_path[i]->query_boats()) >= MAX_BOATS) 
    {   
        notify_fail("Oh dear! It seems there are too many ships " +
                    "over there and your ship won't fit!\n"); 
        return 0;
    } 

    if (tp->query_skill(SAILING_SKILL) < 
        row_exits_path[i]->query_sailing_difficulty())
    {
        mixed sail_fail = row_exits_path[i]->query_sailing_fail_message();

        if (!stringp(sail_fail))
        {
            if(tp->id("_ansalon_charter_captain"))
                tp->not_enough_skill_response();

            notify_fail("The conditions in that direction are beyond " +
                "your sailing skill to navigate through!\n"); 
            return 0;
        }

        if(tp->id("_ansalon_charter_captain"))
            tp->not_enough_skill_response();

        notify_fail(sail_fail); 
        return 0;
    }

    int ship_size = environment(tp)->query_ship_size();
    int sailing_conditions = row_exits_path[i]->query_sailing_difficulty();

    switch(ship_size)
    {
        case 0..SLOOP:
            if(sailing_conditions > CONDITIONS_NORMAL)
            {
                if(tp->id("_ansalon_charter_captain"))
                    tp->ship_too_small_response();

                notify_fail("The sailing conditions in that direction " +
                    "are too tricky for this small ship to " +
                    "handle! You will need a bigger ship!\n");
                return 0; 
            }
        case CUTTER:
            if(sailing_conditions > CONDITIONS_TRICKY)
            {
                if(tp->id("_ansalon_charter_captain"))
                    tp->ship_too_small_response();

                notify_fail("The sailing conditions in that direction " +
                    "are too challenging for this ship to " +
                    "handle! You will need a bigger ship!\n");
                return 0; 
            }
        case SCHOONER:
            if(sailing_conditions > CONDITIONS_CHALLENGING)
            {
                if(tp->id("_ansalon_charter_captain"))
                    tp->ship_too_small_response();

                notify_fail("The sailing conditions in that direction " +
                    "are way too challenging for this ship to " +
                    "handle! You will need a bigger ship!\n");
                return 0; 
            }
        case CORVETTE:
            if(sailing_conditions > CONDITIONS_EXT_CHALLENGING)
            {
                notify_fail("The sailing conditions in that direction " +
                    "are way too extreme for this ship to " +
                    "handle! You will need a bigger ship!\n");
                return 0; 
            }
    }

    if (row_exits_path[i]->query_sailing_difficulty_message())
        tp->catch_tell(row_exits_path[i]->query_sailing_difficulty_message());

    tp->add_fatigue(-tired);
    environment(tp)->carry_out_row(str, row_exits_path[i]); 
    return 1;
}

/*
 * Function name: add_swim_exit
 * Description:   Add one swim exit to the room. 
 */
varargs void
add_swim_exit(string place, string cmd, mixed efunc, mixed tired, 
              mixed non_obvious)
{
    if ((cmd == "down") && (!stringp(query_sink_path())))
        set_sink_path(place); 

    add_exit(place, cmd, efunc, tired, non_obvious);  
}

/*
 * Function name: add_wade_exit
 * Description:   Add one wade exit to the room. 
 */
add_wade_exit(string place, string cmd, mixed efunc, mixed tired,
              mixed non_obvious)
{
    add_exit(place, cmd, efunc, tired, non_obvious); 
}

/*
 * Function name: add_row_exit
 * Description:   Add one ROW exit (for rowing boats) to the room. 
 * Arguments:     path: The filename of the room to move to
 *                arg:  The argument given after "row" e.g.
 *                       "north", "cave"
 *                check: A check to see if can move in that direction,
 *                       often uses vbfc. Possible values are: 
 *                       0: Direct move to destination
 *                       1: Can not move in this dir, do not try others
 *                tired: How much more tired the player should become from
 *                       rowing in that direction. Default is 1.
 */

varargs void
add_row_exit(string path, string arg, mixed check, int tired)
{
    row_exits_path += ({ path });

    row_exits_arg += ({ arg });

    row_exits_check += ({ check });

    if (!tired)
        tired = 1;
    row_exits_tired += ({ tired });
}


/*
 * Function name: remove_row_exit
 * Description:   Remove one row exit from the room.
 * Arguments:     arg:   The argument given after "row" for the exit to be 
 *                       removed.
 */
public int
remove_row_exit(string arg)
{
    int i;

    if (query_prop(ROOM_I_NO_EXTRA_EXIT))
        return 0;

    i = member_array(arg, row_exits_arg);
    if (i == -1) 
        return 0;

    row_exits_arg = exclude_array(row_exits_arg, i, i);
    row_exits_path = exclude_array(row_exits_path, i, i);
    row_exits_check = exclude_array(row_exits_check, i, i);
    row_exits_tired = exclude_array(row_exits_tired, i, i);

    return 1;
}


/* An object sinks */
public void
sink(object ob)
{
    string sp, sv;

    if (!objectp(ob)) 
        return;

    if (!objectp(present(ob, this_object())))
        return;

    if (!stringp(sp = query_sink_path()))
        return;

    sv = ((ob->num_heap() > 1) ? "sink" : "sinks"); 
    tell_room(this_object(), capitalize(LANG_THESHORT(ob)) + 
                             " " + sv + " downwards.\n");
    ob->move(sp);
    tell_room(sp, capitalize(LANG_THESHORT(ob)) + " " + sv + " in.\n");
}


int
deep_water_room(object r)
{
    if ((r->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) || 
        stringp(r->query_sink_path())) 
        return 1;
    else
        return 0;
}


/*
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 *                We need to add the drown object to livings who enter.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
     object d; 

     ::enter_inv(ob, from);

     if ((!living(ob)) && !ob->query_prop(OBJ_I_FLOAT)) 
     {
         set_alarm(2.0, 0.0, &sink(ob));
         return;
     }

     /* Burn out torches dropped into water */ 
     if (ob->query_lit(0) == -1) {    
         ob->burned_out();  
         return;
     }

     if (!interactive(ob) || ob->query_prop(LIVE_I_GILLS))
         return;

     if (query_standard_water_room()) { 
         if (!objectp(d = ob->query_prop(LIVE_O_DROWN_OB))) { 
             d = clone_object(DROWN_OBJECT);
             d->move(ob); 
         }
         d->reset_trap_move(); 
         /* Burn out torches held by player when in deep water */ 
         if (deep_water_room(this_object()) && 
             !deep_water_room(from)) 
             d->extinguish_lights(); 
    }
}



/*
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 *                We need to remove the drown object from livings who exit.
 * Arguments:     ob: The object that just left this inventory
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    object dob;

    ::leave_inv(ob, to);

    if (!living(ob))
        return;

    /* quitting */
    if (!objectp(to)) 
        return;

    dob = ob->query_prop(LIVE_O_DROWN_OB);
    if (!objectp(dob)) 
        return;

    /* If they've gone linkdead, we'll not remove the drown object. */ 
    if (file_name(to) == OWN_STATUE) 
        return;

    /* Otherwise, if they're gone into a room which isn't one of 
       our standard underwater rooms, get rid of the drown object. */ 
    if (!to->query_standard_water_room()) 
        dob->remove_object();

    /* Another possibility is if you've swum to the surface, in which 
       case catch your breath but retain the drown object. */ 
    if (!(to->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER))
        dob->reset_oxygen_debt(); 
}




