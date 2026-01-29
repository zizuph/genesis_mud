 /*****************************************************************************
*  /d/Calia/gelan/sewers/std/sewers_std.c
*
*  Description: STD file for the Gelan Sewers
*
*  Created Aug 2021, Greneth
*
*  Changes:      
*
 *****************************************************************************/

 /*****************************************************************************
*  Pragma
 *****************************************************************************/
#pragma strict_types

 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include "../local.h"

 /*****************************************************************************
*  Inherits
 *****************************************************************************/
inherit "/std/room";

 /*****************************************************************************
*  Prototypes
 *****************************************************************************/
public nomask void  create_room();
public void         create_std_sewers();
public void         add_sewers_items();

 /*****************************************************************************
*  Strings
 *****************************************************************************/
string smell_list(string str);

 /*****************************************************************************
*  Function name: create_room
*  Description  : Creates the room
 *****************************************************************************/
public nomask void
create_room()
{
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_INSIDE, 1);
    create_std_sewers();
    add_sewers_items();
}

 /*****************************************************************************
*  Function name: create_std_sewers
*  Description  : Dummy function for inheriting rooms to mask
 *****************************************************************************/
public void
create_std_sewers()
{
    set_short("a set_short is needed here");
    set_long("A set_long is needed here");
}

 /*****************************************************************************
*  Function name: add_sewers_items
*  Description  : Adds the standard exa items for the sewers
 *****************************************************************************/
public void
add_sewers_items()
{
    add_item(({"cove", "crescent cove", "crescent shaped cove"}),
    "This crescent shaped cove is rather seculded with the rising outcrops "
    + "on both sides and narrow water access.\n");
}

 /*****************************************************************************
*  Function name: get_all_no_exits
*  Description  : Returns an array of strings with exits for use with 
*                 set_no_exit_msg()
*  Argument     : Array of exits to exclude, for simplicity you can use nw 
*                 instead of northwest, etc.
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
*  Function name: init
*  Description  : Adds actions
 *****************************************************************************/
public void
init()
{
    ::init();
    add_action(smell_list, "smell");
}

 /*****************************************************************************
*  Function name: smell_list
*  Description  : Describes the smell action
 *****************************************************************************/
int
smell_list(string what)
{
	if (!what)
    {
        return 0;
    }
	
    if (parse_command(what, this_player(), "[the] 'air' / 'sewers' / "
	+ "'area' / 'here'"))
	{
        if (TP->query_stat(SS_CON) > SMELL_CON)
        {
            say(QCTNAME(TP) + " wrinkles their nose as they "
			+ "take a quick whiff of the surrounding area.\n");
		    write("Your nose wrinkles as you take a quick whiff of the "
			+ "surrounding area.\n");
			return 1;
	    }
		else
		    say(QCTNAME(TP) + " takes a quick whiff of their "
		    + "surroundings and immediately begins to gag.\n");
            write("You take a quick whiff of the surrounding area and "
			+ "immediately begin to gag.\n");
		    return 1;
		}
    if (parse_command(what, this_player(), "[the] 'water' / 'sewage' / "
	+ "'ground' / 'floor'"))
    {
	    if (TP->query_stat(SS_CON) > SMELL_CON) 
	    {
		    say(QCTNAME(TP) + " kneels down and smells the "
            + "sewage on the ground, forcing them to cough a few times.\n");
		    write("You kneel down and smell the sewage on the ground, "
            + "the smell is ripe and causes you to cough a few times.\n");
			return 1;
	    }
		else
            say(QCTNAME(TP) + " kneels down and smells the "
            + "sewage on the ground, causing them to immediately puke.\n");
            write("You kneel down and smell the sewage on the ground, "
            + "causing you to immediately puke.\n");
        return 1;
    }
}