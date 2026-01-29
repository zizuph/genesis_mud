/*
 * pier.c
 *
 * One of the small beaches you can find near Kurinost.
 *
 * Copyright (C): Kellon, oktober 2012
 *                Poul Erik Jensen
 *
 */
#pragma save_binary

// I N C L U D E D   F I L E S
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"
#include "/d/Calia/sys/water.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

// I N H E R I T E D   F I L E S
inherit BEACHBASE;

// D E F I N I T I O N S

// G L O B A L   V A R S
string sink_path;
string *row_exits_arg = ({ });
string *row_exits_path = ({ });
int *row_exits_tired = ({ });
mixed *row_exits_check = ({ });
object *boats = ({ }); 
string boat_vista; 

object warship, ship;
object drac1, drac2, drac3, drac4, drac5, captain;
#define DRAC "/d/Krynn/std/sivak"

// P R O T O T Y P E S
public string show_the_sand();

// P U B L I C   F U N C T I O N S

public void
reset_kurinost_room()
{
    object boat_in;

    seteuid(getuid(TO));
    if(!ship)
    {
	ship = clone_object("/d/Ansalon/silvanesti/kurinost/ship/ship");
	ship->start_ship();
    }

    if(!objectp(warship))
    {
        warship = clone_object(RSOBJS + "warship");
        warship->move(TO, 1);
    }

     if (!objectp(boat_in = warship->query_boat_in())) 
     {
         warship->config_boat_inside();
         boat_in = warship->query_boat_in();
     }

     if (!objectp(drac1)) 
     {
         drac1 = clone_object(DRAC);
         drac1->set_color("green");
         drac1->move_living("in his warship", boat_in);
     }

     if (!objectp(drac2)) 
     {
         drac2 = clone_object(DRAC);
         drac2->set_color("green");
         drac2->move_living("in his warship", boat_in);
     }

     if (!objectp(drac3)) 
     { 
         drac3 = clone_object(DRAC);
         drac3->set_color("green");
         drac3->move_living("in his warship", boat_in);
     }

     if (!objectp(drac4)) 
     {
         drac4 = clone_object(DRAC);
         drac4->set_color("green");
         drac4->move_living("in his warship", boat_in);
     }

     if (!objectp(captain)) 
     {
         captain = clone_object(RSLIVING + "da_captain");
         captain->move_living("into his warship", boat_in);
         captain->set_stats(({280, 240, 240, 170, 170, 180}));
         captain->heal_hp(10000);
         boat_in->set_owner(captain); 
     }

}


/*
 *  FUNCTION : show_the_sand
 *  Arguments: none
 *  Returns  : string - the description.
 * 
 *  Generates a description of the sand. Maybe there are items
 *  to be found in the sand.
 *
 */

public string
show_the_sand()
{
    string item_desc = show_items();

    return "To your south waves wash onto the coarse grey sand of this " +
        "short stretch of the beach.\n";
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
    if (tp->query_fatigue() < tired) {
        notify_fail("You are too tired to sail anywhere at the moment. " +
            "You decide to drift where you are.\n"); 
        return 0;
    }
    if (sizeof(row_exits_path[i]->query_boats()) >= ANSALON_MAX_BOATS) {   
        notify_fail("Oh dear! It seems there are too many ships " +
                    "over there and your ship won't fit!\n"); 
        return 0; 
    } 
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
 *  FUNCTION : create_kurinost_room
 *  Arguments: None
 *  Returns  : Void
 * 
 *  create_room function that sets up descriptions and exits.
 *
 */
public void
create_kurinost_room()
{
    // We need to add these items before the rest is generated.
    add_item(({ "beach", "small beach", "sand", "coarse sand",
        "grey sand", "coarse grey sand" }), show_the_sand);

    generate_beach("Thundering waves spray up around you as you stand on " +
        "the edge of a long wooden pier that juts out into the stormy " +
        "sea of the Bay of Balifor. The pier leads south to a beach " +
        "where a narrow path twists up the steep granite cliffs that " +
        "make up much of this coastline.");
    
    set_short("long wooden pier stretching into the Bay of Balifor");
    set_long(show_me_long_desc);

    add_tell("Giant waves crash into the wooden pier, spraying you " +
        "with salty water.\n");
  
    add_item(({ "path", "narrow path", "small path",
        "small narrow path", "steep path", "steep narrow path",
        "narrow ledge" }), "A small narrow path twists and turns its way " +
        "up the side of the cliffside like a great black snake to your " +
        "south.\n");
    add_item(({"long wooden pier", "wooden pier", "pier"}),
        "A long wooden pier has been built here for the forces of the " +
        "Green Dragonarmy, to assist in their occupation of the elven " +
        "nation of Silvanesti to your south. Ships from Port Balifor " +
        "in the north dock here.\n");

    add_exit(RSROOMS + "rs_shore", "south");

    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    setup_tells();
    KURINOSTMAP;

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");
    reset_room();
}