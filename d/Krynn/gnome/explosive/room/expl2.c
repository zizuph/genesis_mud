/**
* Coded by Louie 2004
* 
* Just a hallway.
*
*/
#pragma strict_types

#include "../local.h"
inherit GNOME_IR;

/*prototypes*/
string state_descrip();

void
create_gnome_room()
{

    SHORT("Hallway in the Explosives Development Center");
    LONG("This is a hallway in the Explosives Development Center " +
    	"of Gnomish "+
      "Industries.  " +
      "It is a rather plain hallway with doorways leading " +
      "north, east, and south.  " +
      "There is a sign above each doorway.  " +
      "@@state_descrip@@" +
      "\n");

    ITEM(({"hallway","hall"}),
    	"This hallway is rather plain.\n");

    ITEM(({"sign","signs"}),
    	"There is a sign above each exit to the north, " +
    	"south, and east.  " +
    	"\n");
    	
    ITEM(({"northern sign","north sign"}),
    	"The sign to the north reads:  Design Room for the Explosives " +
    	"Development Center of Gnomish Industries.\n");

  	CMD(({"northern sign", "north sign"}),
    	"read",
    	"The sign to the north reads:  Design Room for the Explosives " +
    	"Development Center of Gnomish Industries.\n");

	ITEM(({"southern sign","south sign"}),
    	"The sign to the south reads:  Entrance Room for the Explosives " +
    	"Development Center of Gnomish Industries.\n");

  	CMD(({"southern sign", "south sign"}),
    	"read",
    	"The sign to the south reads:  Entrance Room for the Explosives " +
    	"Development Center of Gnomish Industries.\n");
    	
	ITEM(({"eastern sign","east sign"}),
    	"The sign to the east reads:  Design Approval Room for the Explosives " +
    	"Development Center of Gnomish Industries.\n");
    	    	
    CMD(({"eastern sign", "east sign"}),
    	"read",
    	"The sign to the east reads:  Design Approval Room for the Explosives " +
    	"Development Center of Gnomish Industries.\n");

    EXIT(GNOME_ROOM + "expl1", "south", 0, 1);
    EXIT(GNOME_ROOM + "expl3", "north" ,0 ,1);
    EXIT(GNOME_ROOM + "expl4", "east", 0, 1);

}

string
state_descrip()
{
    string desc = "";

    if (IS_EXPL) 
    {
	
	desc = "Screams can be heard in the distance, " +
		"while a loud alarm bell rings incessantly.  ";

    } 


    return desc;

}