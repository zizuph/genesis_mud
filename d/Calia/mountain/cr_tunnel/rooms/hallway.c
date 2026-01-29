/*	entryway between Calian palace and tunnel

	coder(s):	Amelia & Digit
	history:
                 5/2/95       created Amelia
                 23/2/95      added ice chute - Digit
                 5/3/95	      updated descriptions by Amelia
                 12/5/95      Typos removed
                 23 MAY 95  added rope to description   Digit
                 23/5/95    Correction to move_living   Maniac
                 25/7/95    Bug corrected               Maniac
                 18/9/95    Typo corrected              Maniac

	purpose:	connects palace to tunnel
	exits:		down to tunnel1, up to training room.
                   into the ice chute
	objects:	none
	npcs:		none
	quests:		none
	special:	
	to do:
	bugs:		none known
*/

#pragma save_binary

inherit "/std/room";
inherit "/cmd/std/command_driver";
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "tunnels.h"

void
create_room()
{
	set_short("A hallway");
	set_long("You are standing in a short hallway that is "+
		"completely empty.  The walls and ceiling are "+
		"coated with a transparent, sparkling substance.  "+
		"At the north end a beam of light reaches up "+
		"through a hole in the ceiling and illuminates the "+
		"room.  At the south end, you see a stairway that "+
		"descends into a soft blue glow.  In the east wall, "+
		"there is a dark shaft, which seems to lead down into "+
		"darkness below.  In the west wall, you see a chute of "+
           "some kind made out of what appears to be ice.\n");
	
    add_item("rope","A single rope is dangling down into the dark shaft.\n");
	add_item((({"staircase", "stairs"})),
		("There is a crystal stairway that leads down.\n"));
	add_item((({"substance", "sparkling substance"})),
		("It sparkles like a crystalline resin and coats the "+
		"walls and ceiling.\n"));
	add_item("hallway", "The hallway is completely empty "+
		"and feels totally insulated from the world above.\n");
	add_item((({"beam", "beam of light", "light"})),
		("The beam of light is like a white sheet, "+
		"which extends up through the ceiling.  You can "+
		"return to the palace by going up.\n"));
	add_item((({"walls", "wall", "ceiling"})),
		("The walls and ceiling form a curved arch "+
		"that gives this room the feeling of a cave.\n"));
   add_item((({"shaft","dark shaft"})),
           ("The shaft leads down into complete darkness.  All "+
           "you can see in it is a single rope leading down the "+
           "shaft.  You hear the occasional sound from below.\n"));
   add_item((({"chute","ice chute"})),
           ("The chute seems to lead in a downwards direction, and "+
           "is lit by some sort of sparkling substance.\n"));


	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_IS, 1);
	add_prop(ROOM_I_INSIDE, 1);
		
	add_exit(TUNNELS_ROOMS+"tunnel1", "down", 0,0);
	
	setuid();
	seteuid(getuid());
}

int
up_beam(string str)
{
	write("You step into the white light, gently ascend, "+
		"and then step out.\n");
	say(QCTNAME(TP)+" steps into the light.\n");
	tell_room(TRAINROOM, QCTNAME(TP)+" steps out from the light.\n", TP);
	TP->move_living("M",TRAINROOM);
	return 1;
}

void
init()
{
    ::init();
    add_action("ent_chute","enter");
    add_action("pushed","push");
    add_action("up_beam", "up");
}

public int
chute_is_occupied()
{
    setuid();
    seteuid(getuid());
    
    if (LOAD_ERR(TUNNELS_ROOMS + "chute"))
    {
        return 1;
    }
    
    return sizeof(FILTER_LIVE(all_inventory(find_object(TUNNELS_ROOMS + "chute"))));
}

int
ent_chute(string str)
{
    if (str != "chute")
    {
    if (str != "shaft")
    {
    NF("Enter what?\n");
    return 0;
    }
    }
    if (str=="shaft")
    {
       write("You look down and decide that it is far too deep "+
          "for you to try to enter the shaft and decide against it.\n");
       return 1;
    }
    
    if (chute_is_occupied())
    {
       write("Someone is already in the ice chute.  You'll have to "+
          "wait until they are out before you can enter.  Please try "+
          "again in a few moments.\n");
       return 1;
    }
    
    write("You enter the ice chute and hope for the best.  You fall "+
       "onto your butt and begin to slide down the chute, your speed "+
       "increasing as you travel downwards.\n");
    say(QCTNAME(TP)+ " enters the ice chute and disappears out of sight!\n");
    TP->move_living("M", TUNNELS_ROOMS + "chute", 1);
    return 1;
}


int
pushed(string str)
{
    object target;
    object *oblist;

    if(!str)
    {
        notify_fail("Push who down the chute?\n");
        return 0;
    }

    oblist = parse_this(str, "%l [into] / [down] [the] [chute]");
    if (!sizeof(oblist)) {
        notify_fail("Push who down the chute?\n");
        return 0;
    }

    if (!living(oblist[0]))
    {
        notify_fail(oblist[0]->query_name()+"doesn't seem to be alive.\n");
        return 0;
    }
    if (sizeof(oblist) > 1)
    {
        notify_fail("You can't push everyone down the chute!  Pick one!\n");
        return 0;
    }

    if (chute_is_occupied()) { 
       notify_fail("Someone is already in the chute!\n"); 
       return 0;
    }

    target = oblist[0];
    TP->catch_msg("You send "+QTNAME(target)+ 
                  " flying down the chute as you "+
                  "push " + target->query_objective() + " into it.\n");
    target->catch_msg("You are suddenly pushed into the chute by "+
        QTNAME(TP)+"!\n");
    say(QCTNAME(TP)+" pushes "+QTNAME(target)+" into the chute!\n", 
        ({TP, target}));
    target->move_living("M",TUNNELS_ROOMS + "chute", 1);
    return 1;
}
