/**
* Coded by Louie 2004
* 
* Hatch room.
* The room above the Arming Room in the gnome explosive center.
*/
#pragma strict_types

#include "../local.h"
inherit GNOME_IR;

/*prototypes*/
string state_descrip();


void
reset_gnome_room()
{
	object gnome;
	
	if (!present("_hatch_gnome"))
	{
		gnome = clone_object(GNOME_NPC+"hatch_gnome");
		gnome->move_living("xxx",TO);
	}
}

/*
*Create
*/
void
create_gnome_room()
{

    SHORT("Hatch Room in the Explosives Development Center");
    LONG("This is a small room in the Explosives Development Center " +
    	"of Gnomish "+
      "Industries.  " +
      "There are only two things in this room; a large blast shield "+
      "and a hatch in the floor.  " +
      "This room connects to the Arming Room below, and a " +
      "guard room to the east.  " +
      "@@state_descrip@@" +
      "\n");

	clone_object(GNOME_OBJ+"hatch")->move(TO);
	
	ITEM(({"shield","blast shield","large shield","large blast shield"}),
		"The blast shield is simply a large slab of metal that could "+
		"possibly protect someone from an explosion.  "+
	   	"\n");

    EXIT(GNOME_ROOM + "expl7", "east", 0, 1);

    reset_gnome_room();

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
