/*
 * MR8.c
 * Ruins of Kamesh
 * Entrance to the Crypt.
 * - Alaron January 1997
 */

#include "/d/Emerald/defs.h"
#include "default.h"

#define DOOR_OPEN 1
#define DOOR_CLOSED 0

inherit "/std/room";

void do_open_door();
void do_close_door();
string open_or_closed();
int query_door_status();

int enter_tomb(string str);
int open_door(string str);
int close_door(string str);

int door_status;

int 
query_door_status()
{
    return door_status;
}

void
create_room()
{
    door_status = DOOR_CLOSED;

    set_short("A small clearing");
    set_long("   You are standing at the end of the narrow path that "+
	     "winds its way through the decaying ruins of the "+
	     "monastery. The scene is dominated by a towering tomb which "+
	     "is made of thick, gray blocks of stone carved in relief. Huge "+
	     "patches of moss decorate the dark, water-stained stone "+
	     "walls. At the front of the tomb is an enormous, iron door that "+
	     "has taken on a very green tinge due to centuries of not "+
	     "being used or opened. An icy wind blows across the clearing, "+
	     "bending treetops and brushing the grass against your "+
	     "feet.\n\n");

    add_prop(ROOM_I_INSIDE, 0);

    add_item( ({"path", "down", "ground", "below", "dirt", "clearing"}),
	     "The path beneath you tapers to an end in front of the "+
	     "massive tomb. It is a winding patch of dirt covered with "+
	     "pebbles and overgrown weeds.\n");

    add_item( ({"tomb", "towering tomb", "dark tomb", "stone tomb",
		"crypt"}),
	     "The massive tomb towering before you is quite a sight. It "+
	     "doesn't stand much higher than you, but it seems to sprawl out "+
	     "in all directions forever, the corners of the tomb being "+
	     "swallowed by the mist so you can't gauge its true size. It "+
	     "is made of huge, thick dark gray stone bricks carved in "+
	     "relief. The top of the tomb is a black stone slab that looks "+
	     "like it is all one piece. A huge, tarnished iron door sits "+
	     "@@open_or_closed@@ and recessed in the front wall.\n");

    add_item( ({"stone bricks", "bricks"}),
	     "The stone bricks are square bricks with intricately carved "+
	     "designs on them. The designs are carved in relief, so it "+
	     "looks like the pictures are trying to reach out of the "+
	     "bricks and escape.\n");

    add_item( ({"slab", "stone slab", "black stone slab", "roof"}),
	     "The black stone slab for the roof seems to be all "+
	     "one piece, though you can't quite figure out how the "+
	     "construction of this was accomplished, considering how "+
	     "wide and long the tomb is.\n");

    add_item( ({"door", "iron door", "tarnished door", "tarnished iron door"}),
	     "The huge iron door looks like a relic from an ancient time. "+
	     "The door must be a half-meter thick, and the iron riveting is "+
	     "clearly visible on the outside. The iron should have been "+
	     "pitch black, but the years of being in this kind of moisture "+
	     "have begun to give the door a greenish tinge.\n"+
	     "The door is @@open_or_closed@@\n");

    add_exit(MONKRUIN_DIR + "mr6", "northeast");

    if (LOAD_ERR(MONKRUIN_DIR + "cry1"))
    {
	// we're in trouble!!
    }
}

init()
{
    ::init();
    add_action(enter_tomb, "enter");
    add_action(open_door, "open");
    add_action(close_door, "close");
}

string 
open_or_closed()
{
    if (door_status==DOOR_OPEN)
	return "open";
    else
	return "closed";
}

int
enter_tomb(string str)
{
    if ( (member_array(str, ({"tomb", "crypt", "entrance", "door"})))==-1)
    {
	notify_fail("Enter what?\n");
	return 0;
    }

    if (door_status == DOOR_CLOSED)
    {
	notify_fail("The iron door is closed. You can't enter.\n");
	return 0;
    }

    write("You step through the entrance to the tomb, suddenly feeling "+
	  "a blast of unnaturally cold air ... \n\n");
    say(QCTNAME(TP)+" steps through the entrance to the tomb.\n");
    TP->move_living("into the tomb", MONKRUIN_DIR + "cry1", 0, 0);
    tell_room(MONKRUIN_DIR + "cry1",
	      QCTNAME(TP)+" steps through the entrance to the tomb.\n",
	      TP);
    return 1;
}

int
open_door(string str)
{
    if (!str) return 0;

    if ( (str!="door") && (str!="iron door") )
    {
	notify_fail("Open what?\n");
	return 0;
    }

    if (door_status == DOOR_OPEN) 
    {
	notify_fail("The door is already open.\n");
	return 0;
    }

    write("You heave on the massive iron door and manage to pull it open.\n");
    say(QCTNAME(TP)+" heaves on the massive iron door and manages to "+
	"pull it open.\n");
    
    do_open_door();
    return 1;
}

int
close_door(string str)
{
    if (!str) return 0;

    if ( (str!="door") && (str!="iron door") )
    {
	notify_fail("Close what?\n");
	return 0;
    }

    if (door_status == DOOR_CLOSED)
    {
	notify_fail("The door is already closed.\n");
	return 0;
    }

    write("You push and slam into the door and finally manage to close "+
	  "it.\n");
    say(QCTNAME(TP)+" pushes and slams into the door and finally manages "+
	"to close it.\n");
    
    do_close_door();
    return 1;
}

void
do_open_door()
{
    string msg;

    msg = "The huge iron door creaks and squeals as it pulls open on its "+
	"ancient, rusted hinges.\n";

    tell_room(MONKRUIN_DIR + "cry1", msg);
    tell_room(this_object(), msg);

    door_status = DOOR_OPEN;
}

void
do_close_door()
{
    string msg;

    msg = "The huge iron door creaks and squeals as it slams shut.\n";

    tell_room(MONKRUIN_DIR + "cry1", msg);
    tell_room(this_object(), msg);

    door_status = DOOR_CLOSED;
}

			     
