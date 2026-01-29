/*
 * Water base of Calia, inherited by water rooms. 
 * Coded by Maniac. 
 * This baseroom allows the addition of swim, wade and row exits,
 * brings in / removes the drown object when necessary, and handles sinking 
 * of non-living and non-floating objects. 
 * Copyright Miguel Leith 1996. 
 */

#include "/d/Faerun/defs.h"
#include "/d/Faerun/sys/water.h"
#include <composite.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#pragma save_binary

inherit FAERUN_ROOM_BASE;

void create_faerun_water_room() 
{
}    /* re-define this in your room */


/*
 * Global Variables
 */

string sink_path;

string boat_vista; 


/* This next function is essential when it comes to removing the drown 
   object. Imagine if one leaves a standard water room into an area with
   non-standard underwater rooms.. the drown object will stay, but it will
   not get removed if they then go to an ordinary room. */
int
query_standard_water_room()
{
    return 1; 
}


nomask void
create_faerun_room()
{
    int i;

    /* default is under water */
    add_prop(ROOM_I_TYPE, ROOM_UNDER_WATER);

    create_faerun_water_room();  /* This function sets up the long, short, and
                           * swim/wade exits. May also make it ROOM_IN_WATER
                           * instead of ROOM_UNDER_WATER.
                           */
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


/* An object sinks */
void
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

     if ((!living(ob)) && (stringp(query_sink_path())) && 
         !ob->query_prop(OBJ_I_FLOAT)) {
         set_alarm(1.0, 0.0, &sink(ob));
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
