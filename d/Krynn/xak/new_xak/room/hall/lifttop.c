/* 
 * Xak Tsaroth - Hall of the Ancestors
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;

public void
create_xak_room()
{    
    set_short("By the lift");
    set_long("You are at a dead end. There is a lift here that can take " +
	     "you down through a hole in the ground and perhaps further " +
	     "into the city. There is a torch here burning merrily high up " +
	     "on one of the walls.\n");

    LIGHT;

    add_exit(HALL + "southcrypt6", "north");

    add_item("torch", "The torch is high up on the wall well out of reach.\n");
    add_item(({"lift", "pot", "giant pot"}),
	     "The lift consists of two giant lard-rendering pots. Gully " +
	     "dwarves are standing in line here, ready to run out when " +
	     "the draconians crack their whips. They all jump into the pot " +
	     "that is attached to a huge chain wrapped around a " +
	     "spoked wheel with teeth that fit into the links of the " +
	     "chain, that is what is squeaking. The wheel turns and " +
	     "down they go, and pretty soon another pot will come up.\n");
}

public int
do_enter(string str)
{
    NF("Enter what?\n");
    if (!str || !strlen(str))
        return 0;

    if (parse_command(str, ({}), "[into] [giant] 'lift' / 'pot'"))
    {
        
    }
    return 0;
}

public void
init()
{
    ::init();
    add_action(do_enter, "enter");
}






