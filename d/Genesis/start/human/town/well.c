/*
 *	/d/Genesis/start/human/town/well.c       /Styles
 *
 *	Copyright notice, please read.
 *
 *	Copyright Chalmers Datorf|rening, 1993
 *
 *	You are welcome to read this file for information & education
 *	purposes. However, you are expressly forbidden to copy this code
 *	for use in any other mud. This code is part of Genesis and we 
 *	want Genesis to remain unique. You must invent your own world
 *	on your own mud.
 *
 *  Modification log:
 *
 *		Nov 2008:
 *			Expanded a little on the design for it to better fit in
 *			with the upcoming new Sparkle and the city's water mains.
 *			When the new sparkle is ready, we can take away the grate
 *			and allow access through the door, via the excess water
 *			flow regulator, down into the sewers. -Styles.
 *
 *              June 2009:
 *                       Added ROOM_S_MAP_FILE functionality and changed
 *                       path to climb out to lead to New Sparkle (Gorboth)
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";


// Includes
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "../defs.h"


//Defenitions
#define BELLSOUND     " "
#define TELL_STY(x)   find_living("styles")->catch_tell( \
                        ctime(time()) + BELLSOUND + x + "\n")

// Prototypes
public string         in_the_pool();
public void	          create_pool();


// Global variables
public object         Pool; 




void
create_room()
{
    set_short("In the well");
    set_long("\n"+
			"You are in a fairly large well chamber.\n"+
			"In the center of the stone floor there is a pool of "+
			"fresh water. The pool is supplied from a stream "+
			"flowing from a tunnel to the west. Most of the water "+
			"from the stream does not enter the pool but is diverted "+
			"into a hole in the south wall. There is a door next to "+
			"the hole in the south wall and a sturdy metal grate "+
			"blocks passage to the west tunnel. Far up, about ten "+
			"meters, you can see a circle of light.\n");

	add_item("walls",
		"The walls of the well shaft are made out of roughly hewn "+
		"stones, sloppy work that would make any dwarf snort with "+
		"contempt. They were however built by humans and they are "+
		"sturdy enough to last for ages.\n");

	add_item("stones",
		"The stones of the walls seem to be able to provide a good "+
		"hold for climbing, if they didn't look so slippery....\n");

	add_item(({ "water", "stream" }),
		"It looks clean and fresh.\n");

	add_item(({ "well" }), &query_long());

	add_item("light",
		"That just might be daylight.\n");

	add_item("wall",
		"Which one?\n");

	add_item("tunnel",
		"It is a fresh water tunnel. Part of Sparkle's water main. "+
		"It is blocked by a sturdy metal grate.\n");

	add_item("hole",
		"The excess water from the stream drains into the hole. "+
		"It is low, just about twenty centimeters high and about "+
		"two meters wide.\n");

	add_item(({ "lock", "padlock" }),
		"You see nothing special about it. It's big though...\n");

	add_item("door",
		"It is a sturdy metal door. It is locked with a big padlock.\n");

	add_item(({ "grate", "metal grate" }),
		"The grate is made out of strong solid metal. It is set into "+
		"the stone and can not be opened.\n");

	add_item("south wall",
		"The south wall is made out of roughly hewn stones, sloppy "+
		"work that would make any dwarf snort with contempt. This "+
		"wall also features a door and a hole for the excess water.\n");

	add_item("north wall",
		"The north wall is closest to the pool. It is made out of "+
		"roughly hewn stones, sloppy work that would make any dwarf "+
		"snort with contempt. It is wet and slippery.\n");

	add_item("west wall",
		"The west wall is made out of roughly hewn stones, sloppy work "+
		"that would make any dwarf snort with contempt. A metal grate "+
		"is blocking passage into the water supply tunnel.\n");

	add_item("east wall",
		"The east wall is made out of roughly hewn stones, sloppy work "+
		"that would make any dwarf snort with contempt.\n");

	add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_INSIDE, 1);


	create_pool();
}




public string
wizinfo()
{
    return ("\nThe well can potentially kill you when you try to "+
			"climb down but fail and fall. Climbing up is not that "+
			"easy either and you need to succed with a SS_CLIMB check "+
			"at a level that is random(50). Eventually anyone will "+
			"make it. This room is a future access point to the "+
			"water mains and to the sewers in the next version of "+
			"Sparkle.\n");
}


public void
create_pool()
{
	Pool = clone_object("/d/Genesis/start/human/obj/pool.c");
	Pool->set_name("pool");
	Pool->set_short("pool of water");
	Pool->set_long(&in_the_pool());
	Pool->set_no_show_composite(1);
	Pool->add_prop(OBJ_M_NO_GET, "You can't get the "+
						Pool->short() +".\n");


	Pool->move(this_object(), 1);
}



public object
query_pool()
{
	return Pool; 
}



public string
in_the_pool()
{

	if (present("coin", Pool))
		return "It is about a meter deep and looks rather clean "+
			   "and fresh. Looking closely you see a glimmer at "+
			   "the bottom. ";


	return "It is about a meter deep and looks clean and fresh.\n";
}


public int
climb_up(string str)
{

	// It's harder going up than falling down. ;)
	int needed_skill_level = random(50);

    switch (str)
    {
		case "test":
			write(needed_skill_level + "\n");
			return 1;
			break;

		case "up":
		case "out":
			break;

		case "down":
			write("There is no way down.\n");
			break;

		default:
			NF("Exactly where do you want to climb?\n");
			//TELL_STY(TP->query_real_name() +" tried to <climb> ["+ str +"] in the well.\n");
			return 0;
			break;
    }

    /* I'm going to change this so that it doesn't create a trap for
     * players who haven't got any climbing skill. Also, I'm going to
     * change the fail message to indicate that there is hope if
     * you keep trying. (Gorboth)
    if (TP->query_skill(SS_CLIMB) > needed_skill_level)
     */
    if ((TP->query_skill(SS_CLIMB) + random(25)) > needed_skill_level)
	{
		write("You climb up and out of the well.\n");
        say( QCTNAME(TP) +" climbs up and out of the well.\n");
                TP->move_living("M",
                    "/d/Sparkle/area/city/rooms/streets/market_square");

		//TELL_STY(TP->query_real_name() +" climbed out of the well.\n");
    }
	else
		{
        write("You manage to make it partway up but slip on the slick"
          + " stony surface and tumble back to the bottom. Grrr! Well,"
          + " I suppose you might be luckier if you keep trying.\n");
			say( QCTNAME(TP) +" tries to climb out of the well.\n");
			// Inroduce random chanse to increase SS_CLIMB. It is after
			// all good practice.
		}


	return 1;
}



public int
pick_lock(string arg)
{
    switch (arg)
    {

		case "lock":
			break;

		case "padlock":
			break;

		case "grate":
			write("It has no lock to pick\n");
			return 1;
			break;

		default:
			return 0;
			break;
    }

     write("You fail.\n");
	 say( QCTNAME(TP) +" tries to pick the "+ arg +".\n");
    return 1;
}




public int
unlock_door(string arg)
{

    switch (arg)
    {
		case "door":
			break;

		case "lock":
			break;

		case "padlock":
			break;

		case "grate":
			write("It has no lock!\n");
			return 1;
			break;

		default:
			return 0;
			break;
    }

     write("You fail.\n");
	 say( QCTNAME(TP) +" tries to unlock the "+ arg +".\n");
    return 1;
}




void
init()
{
    ::init();

    add_action(climb_up, "climb");
	add_action(unlock_door, "unlock");
	add_action(pick_lock, "pick");

	if (!Pool)
		create_pool();
}
