/**
* Coded by Louie 2004
* 
* The main desk (first room) of the gnomish explosive area.
* Here the player can sign a request form (waiver.c) which will get them
* started on the "build a bomb" quest.
* There's also a cool little door leading west (to expl6).
*
*/
#pragma strict_types

#include "../local.h"
inherit GNOME_IR;

int ipen = 0;

/*prototypes*/
void dry_pen();
int sign_doc(string str);
string state_descrip();
string pen_state();
int dip_pen(string str);
int push_button(string str);
string door_state();
void open_door();
int try_west();

/*
* Reset
*/
void
reset_gnome_room()
{
	object gnome;
	
	if (!present("_gnome_receptionist"))
	{
		gnome = clone_object(GNOME_NPC+"recep_gnome");
		gnome->move_living("xxx",TO);
	}
}

/*
* Create
*/
void
create_gnome_room()
{

	seteuid("_gnome_expl1");
    SHORT("Explosives Development Center of Gnomish Industries");
    LONG("This is the Explosives Development Center of Gnomish "+
      "Industries.  It is one of the new facilities in the " +
      "colony, built with the help of dwarven masons.  " +
      "An enormous wooden desk is situated near the middle of " +
      "the room.  " +
      "Signs are posted above the north and south exits, " +
      "while east leads back to the rest of the colony.  " +
      "Behind the desk to the west a gigantic metal door " +
      "@@door_state@@" +
      ".  " +
      "@@state_descrip@@" +
      "\n");

    ITEM(({"desk","wooden desk","enormous desk","plank",
	"enormous wooden desk","huge desk", "huge wooden desk"}),
      "This desk is huge!  " +
      "Even more impressive is that fact that the top of the " +
      "desk is made of one enormous plank of wood.  " +
      "On the desk rests many pieces of paper, an inkwell, " +
      "and a quill pen.\n");

    ITEM(({"paper","papers","pieces of paper","pieces","forms",
	"many pieces","many pieces of paper","many forms",
	"many papers","waivers","many waivers"}),
      "These papers are forms, detailing a request to design " +
      "and build an explosive device.  It also serves as a " +
      "waiver, freeing the Explosives Development Center of " +
      "Gnomish Industries from any liability in the event " +
      "all of your body parts spontaneous move away from each " +
      "other at a very high rate of speed.  It appears there " +
      "are enough copies that you could sign a form if " +
      "you wished.\n");

    ITEM(({"pen","quill pen","black pen","black quill pen","quill",
	"black quill"}),
      "This black quill pen can be used to sign documents.  " +
      "@@pen_state@@" +
      "\n");

    ITEM(({"inkwell","ink well","ink"}),
      "This inkwell contains ink for dipping a pen into.\n");
      
    ITEM(({"door","metal door","gigantic door","gigantic metal door"}),
    	"This door is solid metal in the form of a circle and is " +
    	"at least 2 hand spans thick!  " +
    	"A button is in the middle of the door.  " +
    	"The door " +
    	"@@door_state@@" +
    	".  " +
    	"\n");


    EXIT(GNOME_ROOM + "expl2", "north", 0, 1);
    EXIT(GNOME_ROOM + "expl5", "south" ,0, 1);
    EXIT(GNOME_ROOM + "expl6", "west", "@@try_west", 1);
EXIT("/d/Krynn/gnome/cavern15","east", 0, 1);
    
    reset_gnome_room();

}

void
init()
{
	::init();
	ADD("sign_doc","sign");
	ADD("dip_pen","dip");
	ADD("push_button","push");
	ADD("push_button","press");
}

int
sign_doc(string str)
{

    object ob;
    
    if (!strlen(str) || (
    	!(str == "form") && !(str == "a form")
    	&& !(str == "request form") && !(str == "request forms")
    	&& !(str == "paper") && !(str == "a paper") ) )
    {
		NF("Sign a form?\n");
		return 0;
    }
    
        
    if (ipen) 
    {
		write("You sign a request form and take it from the " +
			"desk.\n");
		SAY(" signs a request form to develop an explosive " +
	  		"device, and takes it from the desk.");
	  	

		if (!present("_gnome_request_form",TP)) {
		      ob = clone_object(GNOME_OBJ+"waiver");
		      ob->set_owner(TP->query_name());
		      ob->move(TP);
		      return 1;
		}
		
		return 1;

    }
    
    NF("The pen has no ink on it!\n");
    return 0;

}

int
push_button(string str)
{

	if (!strlen(str) || (!(str == "button") && !(str == "the button")))
	{
		NF("Push the button?\n");
		return 0;
	}
	
	if (DOOR1_STATE)
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
	
string
state_descrip()
{
    string desc;

	desc = "<<<BUG here, please report.>>>";

    if (IS_EXPL) 
    {
	
	desc = "Framed pictures which obviously should " +
	"be on the walls litter the floor.  " +
	"Screams can be heard from the north and west, " +
	"while a loud alarm bell rings incessantly.  ";

    } 

    if (!(IS_EXPL))
    {
	desc = "Framed pictures hang somewhat haphazardly " +
	"upon the walls of the room.  " +
	"Faint voices can be heard coming from the hallway " +
	"to the north.  ";
    }


    return desc;

}

string
door_state()
{
	string doordesc;
	
	if (DOOR1_STATE) {
		doordesc = "is wide open";
	} else {
		doordesc = "is sealed closed";
	}
	
	return doordesc;
}

int
try_west()
{
	if (DOOR1_STATE) {
		write("You enter the tunnel.\n");
		SAY(" enters the tunnel to the west.");
		return 0;
	}
	
	write("The way is blocked by the closed metal door.\n");
	return 1;
}

string
pen_state()
{
    string desc;

    if (ipen)
    {
		desc = "The pen has ink on it.  ";
    } 
    else
    {
		desc = "The pen is dry.  ";
    }
    
    return desc;

}

int 
dip_pen(string str)
{

    if (str == "pen" || str == "pen in ink" ||
      str == "pen in inkwell" ||
      str == "the pen in ink" ||
      str == "the pen in the inkwell" ||
      str == "the pen") 
    {
		write("You dip the pen in the inkwell, covering it with ink.\n");
		SAY(" dips the black quill pen in the inkwell.");
		ipen = 1;
		set_alarm(20.0, 0.0, "dry_pen");
		return 1;
    }
    
    NF("Dip what in what?\n");
    return 0;
    
}

void
dry_pen()
{
    ipen = 0;
}

void open_door()
{
	/*Close door2 to open door1.*/
	tell_room(GNOME_ROOM+"expl1",
		"A buzzer hums somewhere.\n");
	DOOR2_CLOSE;
}


