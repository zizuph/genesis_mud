/**
* Coded by Louie 2004
* 
* A metal tunnel.
* This room just has two doors, one east one west.  At any
* given time one door should be closed to protect the east side of
* the explosive center (and the rest of gnome land) from the building
* of bombs that goes on in the west side.
* To open a door, you push a button and the open door closes and the
* closed door opens.
*
*/
#pragma strict_types

#include "../local.h"
inherit GNOME_IR;

/*prototypes*/
int do_read(string str);
int push_button(string str);
void open_door();
string door1_state();
string door2_state();

/*
* Create
*/
void
create_gnome_room()
{

    SHORT("Metal Tunnel in the Explosives Development Center");
    LONG("A metal tunnel inside of the Explosives Development Center " +
    	"of Gnomish "+
      "Industries.  " +
      "This tunnel is entirely lined with metal.  " +
      "It is used to protect the outside world from any mishaps that may " +
      "occur during the manufacture of an explosive device.  " +
      "There are two metal doors, one to the east, and one to the west.  " +
      "The door to the east is " +
      "@@door1_state@@" +
      " and the door to the west is " +
      "@@door2_state@@" +
      ".  " +
      "A sign is posted in the middle of the tunnel.  " +
      "\n");

    ITEM(({"door","doors","east door","west door"}),
    	"The doors of the tunnel are made of metal.  " +
    	"The east door is " +
    	"@@door1_state@@" +
    	" and the west door is " +
    	"@@door2_state@@" +
    	".  " +
    	"The sign may give more " +
    	"information about them.\n");
        	
    ITEM(({"sign"}),
    	"The sign reads:  Push the button to open/close the doors.\n" +
    		"Under the sign is a button.\n");
    
    ITEM(({"button","the button"}),
    	"It is a small button.  You can push it.\n");
    	
    EXIT(GNOME_ROOM + "expl7", "west", "@@try_west", 1);
    EXIT(GNOME_ROOM + "expl1", "east", "@@try_east", 1);
    	
}


void
init()
{
	::init();
	ADD("do_read","read");
	ADD("push_button","push");
	ADD("push_button","press");
}

int 
do_read(string str)
{

	if (!strlen(str) || !(str == "sign")) 
	{
		NF("Read what?\n");
		return 0;
	}
	
	write("The sign reads:  Push the button to open/close the doors.\n" +
    		"Under the sign is a button.\n");
    
    return 1;
}

int
push_button(string str)
{

	if (!strlen(str) || (!(str == "button") && !(str == "the button")))
	{
		NF("Push the button?\n");
		return 0;
	}
		
	write("You push the button under the sign.\n");
	SAY(" pushes the button under the sign.");
	set_alarm(2.0, 0.0, "open_door");		
	return 1;
}

string
door1_state()
{
	string doordesc;
	
	if (DOOR1_STATE) {
		doordesc = "open";
	} else {
		doordesc = "closed";
	}
	
	return doordesc;
}

string
door2_state()
{
	string doordesc;
	
	if (DOOR2_STATE) {
		doordesc = "open";
	} else {
		doordesc = "closed";
	}
	
	return doordesc;
}

void
open_door()
{
	
	tell_room(GNOME_ROOM+"expl6",
		"A buzzer hums somewhere.\n");

	if (DOOR1_STATE) 
	{
		DOOR1_CLOSE;
	} else if (DOOR2_STATE)
	{
		DOOR2_CLOSE;
	}
}	

int
try_west()
{
	if (DOOR2_STATE) {
		write("You exit the tunnel.\n");
		SAY(" exits the tunnel to the west.");
		return 0;
	}
	
	write("The way is blocked by the closed metal door.\n");
	return 1;
}

int
try_east()
{
	if (DOOR1_STATE) {
		write("You exit the tunnel.\n");
		SAY(" exits the tunnel to the east.");
		return 0;
	}
	
	write("The way is blocked by the closed metal door.\n");
	return 1;
}