/**
* Coded by Louie 2004
* 
* A hallway.
*
*/
#pragma strict_types

#include "../local.h"
inherit GNOME_IR;

/*prototypes*/
string state_descrip();

/*
* Create
*/
void
create_gnome_room()
{

    SHORT("Metal hallway in the Explosives Development Center");
    LONG("This is simply a hallway reinforced and plated in metal.  " +
      "To the north is a small room, and to the south is the guard " +
      "room.  " +
      "@@state_descrip@@" +
      "\n");

	ITEM(({"hallway","wall","walls","metal","plating","metal walls",
		"metal plating"}),
		"The walls here have been reinforced with metal plating " +
		"in order to survive in case of an explosion.\n");

    EXIT(GNOME_ROOM + "expl9", "north", 0, 1);
    EXIT(GNOME_ROOM + "expl7", "south", 0, 1);
    

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

