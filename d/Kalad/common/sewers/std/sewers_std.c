 /*****************************************************************************
*  /d/Kalad/common/sewers/std/sewers_std.c
*
*  STD File: STD file for the Sewers
*
*  Created Jan 2021, Greneth
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
*  Description  : Adds the smell action
 *****************************************************************************/
public void
init()
{
    ::init();
    add_action(smell_list, "smell");
}

 /*****************************************************************************
*  Function name: smell_air
*  Description  : Describes the smell action
 *****************************************************************************/
int
smell_list(string what)
{
    if (parse_command(what, this_player(), "[the] 'air' / 'sewers' / "
	+ "'area' / 'here'"))
	{
        if (TP->query_stat(2) > 164)
        {
            say(QCTNAME(this_player()) + " wrinkles their nose, showing a "
			+ "look of disgust on their face as they take a quick whiff of "
			+ "the surrounding area.\n");
		    write("Your nose wrinkles and your face slowly forms a look of "
			+ "disgust as you take a quick whiff of the surrounding area.\n");
			return 1;
	    }
		else
		    say(QCTNAME(this_player()) + " takes a quick whiff of their "
		    + "surroundings and immediately begins to gag.\n");
            write("You take a quick whiff of the surrounding area and "
			+ "immediately begin to gag.\n");
		    return 1;
		}
    if (parse_command(what, this_player(), "[the] 'water' / 'sewage' / "
	+ "'ground' / 'floor'"))
    {
	    if (TP->query_stat(2) > 164) 
	    {
		    say(QCTNAME(this_player()) + " wrinkles their nose, showing a "
			+ "look of disgust on their face as they take a quick whiff "
			+ "of the surrounding area.\n");
		    write("Smelling ground\n");
			return 1;
	    }
		else
	        say(QCTNAME(this_player()) + " takes a quick whiff of their "
            + "surroundings and immediately begins to gag.\n");
            write("Smelling ground epic con\n");
		    return 1;
	}
}