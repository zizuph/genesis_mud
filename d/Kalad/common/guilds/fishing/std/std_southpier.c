 /*****************************************************************************
* /d/Kalad/common/guilds/fishing/std
*
* STD File for South Pier Rooms
*
* Map of Pier
*
*      0
*      |         G - Fishing Guild
*      0
*      |
*  0-0-0-0-0
*      |
*      G
*		 
*		 
* Created June 2018, Greneth
 *****************************************************************************/

 /*****************************************************************************
* Pragma
 *****************************************************************************/
#pragma strict_types

 /*****************************************************************************
* Includes
 *****************************************************************************/
#include "/d/Kalad/common/guilds/fishing/defs.h"

 /*****************************************************************************
* Inherits
 *****************************************************************************/
inherit "/d/Kalad/room_std";

 /*****************************************************************************
* Prototypes
 *****************************************************************************/
public nomask void  create_room();
public void         create_std_southpier();
public void         add_southpier_items();

 /*****************************************************************************
* Actions
 *****************************************************************************/
void reset_room();
void do_search();
int recently_searched;

 /*****************************************************************************
* Function name: create_room
*
* Description  : Creates the room
 *****************************************************************************/
public nomask void
create_room()
{
	 add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(LIVE_I_CAN_FISH, 1);
    create_std_southpier();
    add_southpier_items();
}

 /*****************************************************************************
* Function name: create_std_southpier
*
* Description  : Dummy function for inheriting rooms to mask
 *****************************************************************************/
public void
create_std_southpier()
{
	set_short("Add");
	set_long("Add");
}

 /*****************************************************************************
* Function name: add_southpier_items
*
* Description  : Adds the standard  exa items for the beach
 *****************************************************************************/
public void
add_southpier_items()
{
	add_item( ({ "pier" }),
	  "Stretching out quite a ways this pier has been built "
	+ "specifically for fishing. Small woooden benches to sit on "
	+ "have been placed along the railings which are a few feet "
	+ "high to prevent someone from falling into the waters "
	+ "below. At the end of the pier it T's off around a small "
	+ "shack.\n");
	add_item ( ({ "wooden benches", "wooden bench", "bench", 
		"benches" }),
	  "Very simple in design these benches are not only very "
	+ "sturdy looking but practical as well. Other than a bit "
	+ "of trash beneath it there is nothing noteworthy about "
	+ "it.\n");
	add_item ( ({ "railing", "railings" }),
	  "Set in a three-ply with a cross formation the railings "
	+ "look like they could withstand quite a bit of force "
	+ "put against them. A few notches can be seen on the "
	+ "outside of the top board and are most likely from "
	+ "the ropes of crab traps.\n");
	add_item ( ({ "notches" }),
	  "Small indents in the wood which probably comes from "
	+ "the crab trap ropes when they are pulled up.\n");
	add_item ( ({ "water", "waters" }),
	  "Sparkling blue water completely surrounds you as "
	+ "small waves roll on by.\n");
	add_item ( ({ "trash" }),
	  "Random leftover garbage from previous fishmen.\n");

	clone_object(F_OBJ + "bench")->move(this_object());
}

 /*****************************************************************************
* Function name: get_all_no_exits
*
* Description: Returns an array of strings with exits for use with 
* set_no_exit_msg()
*
* Argument: Array of exits to exclude, for simplicity you can use nw instead 
* of northwest, etc.
 *****************************************************************************/
string *
get_all_no_exits(string *exits)
{
    string *r_exits = m_values(NORMAL_EXITS);
    foreach (string exit: exits) {
        foreach (string ind, string val: NORMAL_EXITS) {
            if (exit == ind || exit == val) {
                r_exits -= ({ val });            
            }
        }
    }
    return r_exits;
}

 /*****************************************************************************
* Function name: reset_room
*
* Description: Resets room
 *****************************************************************************/
void
reset_room()
{
    recently_searched = 0;
}

 /*****************************************************************************
* Function name: init
*
* Description: Adds the search action
 *****************************************************************************/
void
init()
{
    ::init();
    add_action("search_trash","search");
}

 /*****************************************************************************
* Function name: search_trash
*
* Description: Specifically searching the trash
 *****************************************************************************/
int
search_trash(string s)
{
    if(!s || s != "trash")
        return 0;
    if(recently_searched)
    {
        write("You find nothing worthwhile.\n");
        return 1;
    }

    write("You start to search through the trash.\n");
    say(QCTNAME(TP) + " starts to search through the trash.\n");
    set_alarm(4.0,0.0,"do_search");
    return 1;
}

 /*****************************************************************************
* Function name: do_search
*
* Description: Adds items to be found
 *****************************************************************************/
void
do_search()
{
    recently_searched = 1;
    write("You find some leftover bait amongst the trash!\n");
    say(QCTNAME(TP) + " takes something from the trash.\n");
    clone_object(F_BAIT + "earthworm.c")->move(TP);
    return;
}