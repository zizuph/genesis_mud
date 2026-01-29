/**********************************************************************
 * - restraunt.c                                                    - *
 * - modified by Antharanos                                         - *
 * - Updated by Damaris@Genesis 02/2006                             - *
 * - Added more food, cleaned up the menu. Also added a special     - *
 * - seating at a table orginal code from Shire/special table.      - *
 **********************************************************************/
#pragma strict_types

inherit "/d/Kalad/lib/pub";
inherit "/d/Khalakhor/lib/special_table";
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

string
dummy_menu()
{
	read_menu("menu");
	return "";
}

public void
create_room()
{
	::create_room();
	hear_bell = 1;
	INSIDE;
	set_short("The Rickety Roaring Rumbling Restaurant");
	set_long("This restaurant looks very big and many people are "+
	"dining here. You see lot's of tables which are occupied by "+
	"eating people. You might even find a table for yourself, so "+
	"the waiter can serve you a meal. There are two latrines in "+
	"the back of the restaurant, one for women and one for men. "+
	"Strange noises come from the kitchen. The smell from the "+
	"kitchen however, is delicious. There is a menu next to a plaque "+
	"on the wall "+
	"here too.\n");
	add_item(({"here", "restaurant", "area", "room"}), query_long);
	
	add_item("menu", dummy_menu);
	add_item(({"noises"}),"The noises can be heard.\n");
	add_item(({"table"}),
	"Maybe you should take a seat so you can order your meal.\n");
	add_item(({"kitchen"}),
	"The kitchen is closed for customers.\n");
	add_item(({"plaque", "small plaque", "gold plaque"}),
	"      The gold plated plaque reads:\n"+
	"          +-------------------+\n"+
	"          |     tablehelp     |\n"+
	"          +-------------------+\n");
	add_cmd_item(({"plaque","small plaque", "gold plaque"}),"read",
	"      The gold plated plaque reads:\n"+
	"          +-------------------+\n"+
	"          |     tablehelp     |\n"+
	"          +-------------------+\n");
	
	/* To add drinks */	
	add_drink(({"beer", "beers", "kabal", "kabal beer"}),
	"beer", "kabal", 125, 10, 24, "kabal beer", "kabal beers",
	"A local drink, its what most of the regulars order.\n", 0);

	add_drink(({"beer", "beers", "lager", "kabal lager"}),
	"lager", "kabal", 125, 20, 54, "kabal lager", "kabal lagers",
	"A lager that has the famous Kabal kick to it.\n", 0);

	add_drink(({"wine", "wines", "sweet", "sweet wine"}),
	"wine", "sweet", 250, 30, 120, "sweet wine", "sweet wines",
	"A sweet wine that tastes very good.\n", 0);

	add_drink(({"wine", "wines", "ruby", "ruby wine"}),
	"wine", "ruby", 250, 30, 120, "ruby wine", "ruby wines",
	"A sweet ruby red wine that tastes very good.\n", 0);

	add_drink(({"absinthe", "absinthe", "glass of", "glass of absinthe" }),
	"absinthe", "glass of", 250, 40, 140, "glass of absinthe", "glasses of absinthe",
	"This lush green emerald drink is brewed on wormwood, "+
	"anise and other herbs, served with ice and sugar.\n", 0);
 
        /* To add foods */
	add_food(({"apple", "apples"}),
	"apple", "crunchy", 30, 30, "crunchy apple", "cruncy apples",  
	"A freshly-picked apple, it looks very crunchy.\n", 0);

	add_food(({"steak", "steaks"}),
	"steak", "grilled", 270, 180, "grilled steak", "grilled steaks",
	"A thick juicy steak, fresh from the grill.\n", 0);

	add_food(({"duck", "roasted duck", "roast"}),
	"duck", "roast", 150, 150, "roasted duck", "roasted ducks",
	"A sumptious-looking roasted duck. The aroma is quite pleasing.\n", 0);

	add_food(({"pheasant", "roasted pheasant", "roast"}),
	"pheasant", "roast", 170, 170, "roasted pheasant", "roasted pheasants",
	"A sumptious-looking roasted pheasant. It has a tangy but "+
	"quite pleasant taste.\n", 0);

	add_food(({"bread", "crusty bread", "piece of"}),
	"bread", "piece of", 30, 20, "piece of crusty bread", "pieces of crusty bread",
	"A torn piece of crusty bread.\n", 0);

	add_food(({"cheese", "chunk", "chunk of"}),
	"cheese", "chunk of", 35, 35, "chunk of cheese", "chunks of cheese",
	"A chunch of finely aged cheese. It goes perfect with a "+
	"crusty bread and wine.\n", 0);
	
	add_food(({"soup", "bowl", "spicy", "bowl of"}),
	"soup", "bowl of", 45, 65, "bowl of spicy soup", "bowls of spicy soup",
	"A hot bowl of spicy beef and potato soup.\n", 0);
	
	add_exit(TRADE(tsquare/c2),"northwest",0,-1,-1);
	add_exit(TRADE(ladies),"ladies","@@check_male@@");
	add_exit(TRADE(gentlemen),"gentlemen","@@check_female@@");
}
void
pub_hook_menu_header()
{
    write(sprintf("%|76s\n\n", "The Rickety Roaring Rumbling Restaurant"));
}
int
check_male()
{
	if (TP->query_gender() != 1)
	{
		write("You enter the ladies bathroom, but suddenly "+
		"several ladies start to scream! A couple of moments "+
		"later a guardsman comes in to put you in jail. It's "+
		"a fine mess you got yourself into...\n");
		say(QCTNAME(this_player()) + " enters the ladies "+
		"bathroom. But immediately as "+
		"" + this_player()->query_pronoun() +" enters, "+
		"several ladies start to scream! A few moments later "+
		"a guardsman comes in to take " + QCTNAME(TP) + " away "+
		"and put "+this_player()->query_objective()+" in jail.\n");
		TP->move_living("out the door with the guard",TRADE(jail),1,0);
		return 1;
	}
	return 0;
}

int
check_female()
{
	if (TP->query_gender() !=0)
	{
		write("You enter the men's bathroom, and suddenly "+
		"several men start to shout. A moment later a "+
		"guardsman appears to throw you in jail. It's a "+
		"fine mess you've gotten yourself into this time.\n");
		say(QCTNAME(TP) + " enters the men's bathroom, but as "+
		"soon as " + TP->query_pronoun() +" enters, some men "+
		"start shouting! A few moments later the guard comes "+
		"in to take " + QCTNAME(TP) + " away "+
		"and put " + TP->query_objective() + " in jail.\n");
		TP->move_living("out the door with the guard",TRADE(jail),1,0);
		return 1;
	}
	return 0;
}
void
init()
{
	::init();
	init_pub();
	init_table();  
}


