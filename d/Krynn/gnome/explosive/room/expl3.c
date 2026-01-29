/**
* Coded by Louie 2004
* 
* Design room.
* This room is where a player can get a design form (design.c) to
* design an explosive device.  All they have to do is pull the lever
* on the box.  If there designer gnome is here (design_gnome.c), he'll
* want to make sure that the player has a signed wavier...I mean request
* form before they can get a design form.
*
*
*/
#pragma strict_types

#include "../local.h"
inherit GNOME_IR;

/*prototypes*/
string state_descrip();
int do_pull(string str);

void
reset_gnome_room()
{
	object gnome;
	
	if (!present("_gnome_designer"))
	{
		gnome = clone_object(GNOME_NPC+"design_gnome");
		gnome->move_living("xxx",TO);
	}
}

void
create_gnome_room()
{

    SHORT("Design Room in the Explosives Development Center");
    LONG("This is the Design Room of the Explosives Development Center " +
    	"of Gnomish "+
      "Industries.  " +
      "The room contains many tables with various papers strewn " +
      "about all over them.  " +
      "The walls are covered with several large drawings and "+
      "schematics.  " +
      "There is a large metal box attached to the wall.  " +
      "@@state_descrip@@" +
      "\n");

    ITEM(({"table","tables","papers"}),
    	"There are several tables, all of them being covered in " +
    	"massive amounts of paper and design work.\n");

    ITEM(({"wall","walls","drawings","drawing",
    	"design drawings","schematic","schematics"}),
    	"All of the walls are completely covered by design drawings.  "+
    	"Most of them make no sense at all.  " +
    	"\n");
    	
    ITEM(({"box","metal box","large box","large metal box"}),
    	"The large metal box is attached firmly to the wall.  It has a " +
    	"lever on the side of it.  " +
    	"\n");
    	
    ITEM(({"lever"}),
    	"The lever can be pulled.  Tempting, isn't it?  " +
    	"\n");

    EXIT(GNOME_ROOM + "expl2", "south", 0, 1);
    
    reset_gnome_room();
    

}

string
state_descrip()
{
    string desc = "";

    if (IS_EXPL) 
    {
	
	desc = "Screams can be heard to the south, " +
		"while a loud alarm bell rings incessantly.  ";

    } 


    return desc;

}

void
init()
{
	::init();
	add_action("do_pull","pull");
}

/*
* Get a design form.
* If the designer gnome is here, he'll want to make sure that the 
* player has an approved request form (waiver.c).  The designer gnome
* is also the one who approves request forms.
*/
int
do_pull(string str)
{
	object ob, gnome;

	if (!strlen(str) || !(str == "lever"))
	{
		NF("Pull what?\n");
		return 0;
	}
	
	if (gnome = present("_gnome_designer")) {
	
		if (
			!(ob = present("_gnome_request_form",TP))
			||
			!(ob->is_approved())
			) {
				gnome->command("rolleyes");
				gnome->command("say ICan'tLetYouHaveA"+
					"DesignFormUntilYouGiveMeASignedRequestForm!");
		
				NF("The gnome stops you from getting a design form.\n");
				return 0;
		}
		
		write("The gnome glances at your approved request " +
			"form and lets you continue.\n");
	}
	
	write("You pull the lever and a horrific grinding sound emits from the box.\n");
	SAY(" pulls the lever on the metal box, causing a horrific grinding sound.");
		
	/* clone a design paper */
	if (!present("_gnome_design_form",TP)) {
		ob = clone_object(GNOME_OBJ+"design");
	    ob->move(TP);
	    write("A piece of paper slides out the bottom, which you take.\n");
	    SAY(" takes a piece of paper that slides out from the bottom of the box.");
	} else {
		write("Nothing comes out, perhaps because you already have a design form.\n");
	}
	
	return 1;
	
}