/*
 * Outer Circle of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 *
 * Updated 2/24/2016 by Leia. Added functionality to enter the temple
 * meeting room.
 */

#pragma strict_types

#include "defs.h"
#include <ss_types.h>
#include <macros.h>

inherit TEMPLE_ROOM_BASE;

// Defines

// Prototypes

// Global Variables
int door_open = 0;

public string
walldesc()
{
	if(door_open == 1)
	{
		return "The wall is made of smooth stone, and set in the middle of it is an open door, with an indentation just to the left of it.\n";
	}
	
	else
	{
		return "The wall is made of smooth stone. Near the middle there is an indentation.\n";
	}
}

public void
create_temple_room()
{
	set_short("Inside the Elemental Temple of Calia");
	set_long("You stand inside the Elemental Temple of Calia, an ornately "
		+ "constructed building that houses those devoted to the service "
		+ "of the Elementals. The walls are made from white marble, or grey stone "
		+ "while the foundation is made from crystalline. The vaulted ceiling is "
		+ "comprised of wood and supported by mighty columns. You notice that "
		+ "the east wall has a small indentation.\n\n");
			
	try_item (({"indentation","wall indentation", "indentation on wall"}),"On the east wall there is a small indentation "
		+ "in the shape of a hand.\n");
		
	try_item (({"east wall","eastern wall"}),"@@walldesc@@");
	
    add_exit(ELEMENTALIST_TEMPLE + "aeria", "north");
    add_exit(ELEMENTALIST_TEMPLE + "outer11", "south"); 
}

public void
init()
{
	::init();
	
	add_action("do_open","place");
}

public int
setroom(int DOOR_STATUS)
{
	door_open = DOOR_STATUS;
}

public int
remex(object THIS_PLAYER)
{
	tell_room(ELEMENTALIST_TEMPLE + "outer9","The door in the eastern wall slides "
		+ "shut and vanishes from sight.\n");
	tell_room(ELEMENTALIST_TEMPLE + "meeting","The door in the western wall slides shut "
			+ "and vanishes from sight.\n");
	remove_exit("east");
	setroom(0);
	(ELEMENTALIST_TEMPLE + "meeting")->remove_exit("west");
	(ELEMENTALIST_TEMPLE + "meeting")->setroom(0);
	return 0;
}

public int
adex(object THIS_PLAYER)
{
	add_exit(ELEMENTALIST_TEMPLE + "meeting","east");
	setroom(1);
	(ELEMENTALIST_TEMPLE + "meeting")->add_exit(ELEMENTALIST_TEMPLE + "outer9","west","@@check_sitting",1);
	(ELEMENTALIST_TEMPLE + "meeting")->setroom(1);
	tell_room(ELEMENTALIST_TEMPLE + "meeting","A door materializes in the western wall "
			+ "and slides open.\n");
	set_alarm(6.0,0.0,"remex",THIS_PLAYER);
	return 1;
}

public int
do_open(string arg)
{
	if(door_open)
	{
		write("You put your hand in the indentation on the wall, "
			+ "however the door is already open.\n");
		say(QCTNAME(this_player()) + " places " + TP->query_possessive()
			+ " hand in an indentation on the wall, however the "
			+ "door is already open.\n");
		return 1;
	}

	
	if (!strlen(arg))
	{
		notify_fail("Place what in where?\n");
		return 0;
	}
	
	arg = lower_case(arg);
	
	if (arg != "hand in indentation")
	{
		write("Place what in where?\n");
		return 0;
	}
	else
	{
		if(GUILD_MANAGER->query_is_ew_council(this_player(), 1))
		{
			write("You place your hand in the indentation on the wall. There is "
				+ "a surge of energy and a rumble from the wall. A hidden door "
				+ "materializes in the east wall and slides open, allowing "
				+ "passage eastwards.\n");
			say(QCTNAME(this_player()) + " places " + TP->query_possessive()
				+ " hand in the indentation on the wall. There is a surge of "
				+ "energy and a rumble from the wall. A hidden door materializes "
				+ "in the east wall and slides open, allowing passage eastwards.\n");
			adex(this_player());
			return 1;
		}
		
		if(GUILD_MANAGER->query_is_ec_council(this_player(), 1))
		{
			write("You place your hand in the indentation on the wall. There is "
				+ "a surge of energy and a rumble from the wall. A hidden door "
				+ "materializes in the east wall and slides open, allowing "
				+ "passage eastwards.\n");
			say(QCTNAME(this_player()) + " places " + TP->query_possessive()
				+ " hand in the indentation on the wall. There is a surge of "
				+ "energy and a rumble from the wall. A hidden door materializes "
				+ "in the east wall and slides open, allowing passage eastwards.\n");
			adex(this_player());
			return 1;
		}
		
		if(GUILD_MANAGER->query_is_elder_cleric(this_player()))
		{
			write("You place your hand in the indentation on the wall. There is "
				+ "a surge of energy and a rumble from the wall. A hidden door "
				+ "materializes in the east wall and slides open, allowing "
				+ "passage eastwards.\n");
			say(QCTNAME(this_player()) + " places " + TP->query_possessive()
				+ " hand in the indentation on the wall. There is a surge of "
				+ "energy and a rumble from the wall. A hidden door materializes "
				+ "in the east wall and slides open, allowing passage eastwards.\n");
			adex(this_player());
			return 1;
		}

		else if(IS_MEMBER(this_player()))
		{
			write("You place your hand in the indentation on the wall. You feel "
				+ "a surge of energy as you connect with the indentation, "
				+ "but nothing happens.\n");
			say(QCTNAME(this_player()) + " places " + TP->query_possessive()
				+ " hand in the indentation on the wall. There is a surge of "
				+ "energy, but nothing happens.\n");
			return 1;
		}
		else
		{
			write("You place your hand in the indentation. Nothing happens.\n");
			say(QCTNAME(this_player()) + " places " + TP->query_possessive()
				+ " hand in an indentation on the wall. Nothing happens.\n");
			return 0;
		}
	}
}
