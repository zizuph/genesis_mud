/**
* Coded by Louie 2004
* 
* Parts shop.
* This room is where a player can get a box of parts to build a bomb,
* if they have the required paperwork.
*
*/
#pragma strict_types

#include "../local.h"
inherit GNOME_IR;
inherit "/lib/trade";
#include <money.h>

/*prototypes*/
string state_descrip();
int do_request(string str);
int do_read(string str);

/*
* Create
*/
void
create_gnome_room()
{
	
	config_default_trade();

    SHORT("Parts Shop in the Explosives Development Center");
    LONG("This is the Parts Shop of the Explosives Development Center " +
    	"of Gnomish "+
      "Industries.  " +
      "This is where someone, with proper approval for their explosives " +
      "design, could receive the parts to manufacture their explosive.  " +
      "The tiny room contains only a counter, behind which stands the " +
      "shopkeeper.  " +
      "A sign sits on the counter.  " +
      "@@state_descrip@@" +
      "\n");

    ITEM(({"counter"}),
    	"The counter is quite plain.  Behind the counter the shopkeeper is " +
    	"standing, waiting to assist someone.\n");

    ITEM(({"shopkeeper"}),
    	"The shopkeeper is an average-looking gnome whose job it is to supply " +
    	"materials when someone requests parts.  " +
    	"\n");
    	
    ITEM(({"sign"}),
    	"The sign reads:  Please have your design form approved "+
    	"before requesting parts.  \n" +
   		"Prices:\n"+
		"\tGnomish Inventors:  Free!\n"+
		"\tGnomes:  Half price!\n"+
		"\tOthers:  Fair market value!" +
    	"\n");
    	

    EXIT(GNOME_ROOM + "expl1", "north", 0, 1);
    

}

string
state_descrip()
{
    string desc = "";

    if (IS_EXPL) 
    {
	
	desc = "Screams can be heard to the north, " +
		"while a loud alarm bell rings incessantly.  ";

    } 


    return desc;

}

void
init()
{
	::init();
	add_action("do_request","request");
	add_action("do_request","buy");
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
	
	write("The sign reads:  Please have your design form approved " +
		"before requesting parts.  \n" +
		"Prices:\n"+
		"\tGnomish Inventors:  Free!\n"+
		"\tGnomes:  Half price!\n"+
		"\tOthers:  Fair market value!" +
    	"\n");
    return 1;
}

/*
* Request parts.
* Check for the paperwork and then give a box of parts to the
* player.  Getting parts costs money, the bigger the player, the
* more it costs :)  Power to the newb!
*/
int
do_request(string str)
{
	object ob;
	object ob2;
	int price;
	int statave;
	int *arr;

	if (!strlen(str) || !(str == "parts"))
	{
		NF("Request parts?\n");
		return 0;
	}
	
	/*Check for approval form, if there...*/
	if (!present("_gnome_design_form",TP)) 
	{
		NF("The shopkeeper says: YouDoNotHaveAnApprovedDesignFormICannotGiveYou"+
			"AnyParts!\n");
		return 0;
	}
	
	ob = present("_gnome_design_form",TP);
	
	if (!ob->is_approved()) {
		NF("The shopkeeper says: YouDoNotHaveAnApprovedDesignFormICannotGiveYou"+
			"AnyParts!\n");
		return 0;
	}

	ob2 = present("_gnome_parts_box",TP);
	if (ob2) 
	{
		NF("The shopkeeper says:  YouAreAleadyCarryingAPartsBoxYouShouldDropItIf"+
			"YouWantToGetAnotherOne!\n");
		return 0;
	}
	
	write("You show your approved design form and request the parts for your device.\n");
	SAY(" shows " + HIS(TP) + " approved design form and requests the parts " +
		"for " + HIS(TP) + " device.");
		
	/* do all the shop stuff */
	
	statave = TP->query_average_stat();
	
	price = statave * 50;	
	
	if (TP->query_race_name() == "gnome") 
	{
		price = price / 2; //gnomes half price!
	}
	
	if (TP->query_guild_name_race() == "Gnomish Inventors")
	{
		price = 0; //Inventors for free!
	} 
	
	if (TP->query_wiz_level())
	{
		write("Wizinfo: Price is:"+price+".\n");
	}
	
	arr = pay(price, TP);
	
	if (sizeof(arr) == 1) {
		/*failure but trade.c take care of the fail message*/
		return 0;
	}
	
	write("You receive a box of parts.\n");
	SAY(" receives a box of parts.");
	ob2 = clone_object(GNOME_OBJ+"parts_box");
	ob2->set_size(ob->component_ct());
	ob2->move(TP);
	
	return 1;
	
}
