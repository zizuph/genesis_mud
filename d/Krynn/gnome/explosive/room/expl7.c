/**
* Coded by Louie 2004
* 
* A guard room that has guards.
* There's a door that is kinda nifty too.
*
*/
#pragma strict_types

#include "../local.h"
inherit GNOME_IR;

/*prototypes*/
string state_descrip();
string door2_state();
void open_door();
int try_east();
int push_button(string str);

/*
* Reset
*/
void
reset_gnome_room()
{
	object *everything;
	int i,
		g = 0;
	object gnome;
	
	everything = all_inventory(TO);

	for (i = 0; i < sizeof(everything); i++)
	{

		if (everything[i]->id("_gnome_guard"))
		{
			g++;
		}
	}
	
	while (g < 4)
	{
		gnome = clone_object(GNOME_NPC+"guard_gnome");
		gnome->move_living("xxx",TO);
		g++;
	}
}

/*
* Create
*/
void
create_gnome_room()
{

    SHORT("Guard Room in the Explosives Development Center");
    LONG("This is a guard room in the Explosives Development Center " +
    	"of Gnomish "+
      "Industries.  " +
      "The room is completely empty, being used only by guards standing guard.  " +
      "To the north is a metal hallway, and to the east a gigantic metal door " +
      "is " + 
      "@@door2_state@@" +
      ".  " +
      "To the west is a poorly lit room.  " +
      "@@state_descrip@@" +
      "\n");

	ITEM(({"door","metal door","gigantic door","gigantic metal door"}),
    	"This door is solid metal in the form of a circle and is " +
    	"at least 2 hand spans thick!  " +
    	"A button is in the middle of the door.  " +
    	"The door is " +
    	"@@door2_state@@" +
   		".  " +
	   	"\n");

    EXIT(GNOME_ROOM + "expl8", "north", 0, 1);
    EXIT(GNOME_ROOM + "expl10", "west", 0, 1);
    EXIT(GNOME_ROOM + "expl6", "east", "@@try_east", 1);
    
    reset_gnome_room();

}

void
init()
{
	::init();
	ADD("push_button","push");
	ADD("push_button","press");
}

string
state_descrip()
{
    string desc = "";

    if (IS_EXPL) 
    {
	
	desc = "A loud alarm bell rings incessantly.  ";

    } 

    return desc;

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
	
	tell_room(GNOME_ROOM+"expl7",
		"A buzzer hums somewhere.\n");
	
	/*To open door2, close door1*/
	DOOR1_CLOSE;

}	

int
try_east()
{
	if (DOOR2_STATE) {
		write("You enter the tunnel.\n");
		SAY(" enters the tunnel to the east.");
		return 0;
	}
	
	write("The way is blocked by the closed metal door.\n");
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
	
	if (DOOR2_STATE)
	{
		NF("You push the button and nothing happens since " +
			"the door is already open.\n");
		return 0;
	}
	
	write("You push the button in the gigantic metal door.\n");
	SAY(" pushes the button in the gigantic metal door.");
	set_alarm(2.0, 0.0, "open_door");		
	return 1;
}
