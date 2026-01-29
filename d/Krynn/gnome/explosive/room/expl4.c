/**
* Coded by Louie 2004
* 
* Approve Room.
* This is where the gnomish committee will approve someone's design
* for an explosive device.
*
*/
#pragma strict_types

#include "../local.h"
inherit GNOME_IR;

/*prototypes*/
string state_descrip();
int do_approve(string str);
int do_read(string str);

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

		if (everything[i]->id("_gnome_explosive_design_approver"))
		{
			g++;
		}
	}
	
	while (g < 6)
	{
		gnome = clone_object(GNOME_NPC+"approve_gnome");
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
	
    SHORT("Approval Room in the Explosives Development Center");
    LONG("This is the Approval Room of the Explosives Development Center " +
    	"of Gnomish "+
      "Industries.  " +
      "This sparse room contains only a large, oval table surrounded " +
      "by many chairs.  " +
      "It is the room where the Approval Committee meets to determine " +
      "if a design is worth using to make an explosive.  " +
      "Their approval is needed to continue with the production of " +
      "any explosive design.  " +
      "There is a sign hanging on the wall.  " +
      "@@state_descrip@@" +
      "\n");

    ITEM(({"table","large table","oval table","large oval table"}),
    	"The large oval table is surrounded by many chairs.  " +
    	"At one end of the table is a metal stamp.  \n");

    ITEM(({"chair","chairs"}),
    	"The chairs encircle the large oval table, where the Committee " +
    	"meets.  " +
    	"\n");
    	
    ITEM(({"sign"}),
    	"The sign reads:  Please give your design to a Committee member " +
    		"to have it approved.  " +
    	"\n");
    
    ITEM(({"stamp","metal stamp"}),
    	"This metal stamp is used by the Committee to approve designs.  \n");
    	

    EXIT(GNOME_ROOM + "expl2", "west", 0, 1);
    
    reset_gnome_room();
    

}

string
state_descrip()
{
    string desc = "";

    if (IS_EXPL) 
    {
	
	desc = "Screams can be heard to the west, " +
		"while a loud alarm bell rings incessantly.  ";

    } 


    return desc;

}

void
init()
{
	::init();
	add_action("do_approve","approve");
	add_action("do_approve","stamp");
	add_action("do_read","read");
}

int
do_read(string str)
{

	if (!strlen(str) || !(str == "sign"))
	{
		NF("Read what?\n");
		return 0;
	}
	
	write("The sign reads:  Please give your design to a Committee member " +
		"to have it approved.  " +
    	"\n");
    return 1;
}


/*
* Attempt to approve a design.  Only committee gnomes (approve_gnome.c) are 
* supposed to do this, but if a player happens to slaughter them all, then they
* can do it themselves - but there may be bonus xp given for letting 
* the gnomes do it.
*/
int
do_approve(string str)
{
	
	object ob, gnome;
	
	if (!strlen(str) || ( !(str == "design") && !(str == "my design") 
		&& !(str== "a design") && !(str == "form") && !(str == "a form")
		&& !(str== "a design form") && !(str== "design form")) )
	{
		NF("Approve a design?\n");
		return 0;
	}
	
	if (!present("_gnome_design_form",TP)) 
	{
		NF("You are not holding a design!\n");
		return 0;
	}
	
	if ((gnome = present("_gnome_explosive_design_approver"))
		&& !(TP->id("_gnome_explosive_design_approver"))) {

		SAY(" reaches for the stamp of approval but is stopped.");		
		gnome->command("scowl");
		gnome->command("say IWillOnlyAllowCommitteeMembersToApproveDesigns!");
		NF("The gnome stops you from approving your own design.\n");
		return 0;
	}
		
	ob = present("_gnome_design_form",TP);
	
	ob->approve();
	
	write("You slam the metal stamp on the design form, giving it " +
		"the Committee's seal of approval.\n");
	SAY(" slams the metal stamp on a design form, embossing it with " +
		"the Committee's seal of approval.");
		

	return 1;
	
}