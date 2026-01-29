#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"
#include <language.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include "/d/Krynn/std/boats/std_boat_defs.h"

inherit         BALIFOR_OUT;
object          drac1;
object          drac2;

#define PB_MAX_BOATS_IN_ROOM 50
#define BALIFOR_BAY  "/d/Krynn/south_courrain/room/s_courrain-3-17-h"

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

/* This next function is essential when it comes to removing the drown 
   object. Imagine if one leaves a standard water room into an area with
   non-standard underwater rooms.. the drown object will stay, but it will
   not get removed if they then go to an ordinary room. */
int
query_standard_water_room()
{
    return 0; 
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
    if (sizeof(row_exits_path[i]->query_boats()) >= PB_MAX_BOATS_IN_ROOM) 
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
    // SAIL_DEBUG("Ship size: " +ship_size);
    // SAIL_DEBUG("Conditions: " +sailing_conditions);
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
    if (TO->query_prop(ROOM_I_NO_EXTRA_EXIT))
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

void
reset_balifor_room()
{
    if (!objectp(drac1)) {
	drac1 = clone_object(KNPC + "baaz");
	drac1->move(TO);
    }
    if (!objectp(drac2)) {
	drac2 = clone_object(KNPC + "baaz");
	drac2->move(TO);
    }
}

create_balifor_room()
{
    set_short("Pier in the Bay");
    set_long("@@long_descr");

    add_item("sign", "@@read");
    add_item(({"Breakwater", "breakwater"}), "@@break_water");
    add_item(({"steppes", "Steppes"}), "@@steppes");
    add_item(({"Bay of Balifor","bay of balifor","bay"}),
      "To your west is the Bay of Balifor.\n");
    add_item("pier","You are at present standing on a pier " +
      "on the edge of the Bay of Balifor.\n");
    add_item(({"dark ships","ships"}),
      "Dark ships of the dragonarmies often sail into and " +
      "out of this port city.\n");

    add_cmd_item("sign", "read", "@@read");

    add_exit(BROOM + "city01", "east", "@@pier", 0);
    add_exit(BROOM + "pier04","north",0);

    add_row_exit(BALIFOR_BAY, "southwest", 0, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    set_tell_time(80);
    add_tell("@@wharf");
    start_room_tells();
    reset_balifor_room();
}

int
pier()
{
    write("You walk off the wharf, back to the street.\n");
    return 0;
}

string
long_descr()
{
    return tod_descr1() + " You are looking over the Bay of Balifor, " +
    "standing out on a pier. The dragonarmies have taken over the " +
    "port city, and confiscated all boats for their use. The dark " +
    "ships sail in and out of Balifor frequently. " + season_descr() +
    "\nThere is a sign standing here." +
    "\n";
}

string
read()
{
    return "The sign reads: The ship to Sybarus used to land here. " +
    "It is cancelled until further notice.\n";
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