/* A portion of the caves which make up the bandits lair in the Blackwall
   Mountains.
   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

inherit "/d/Emerald/thief_lair/base_cave.c";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include "/d/Emerald/sys/paths.h"

/* Determines whether or not there are several bandits present in this
   chamber. Returns false if fewer than 3 bandits are in the room, 
   returns a pointer to one of the bandits if there are more than that number
   present.
*/

mixed
bandits_home()
{
    object *bandits = filter(all_inventory(this_object()), &->query_bandit());

    if (sizeof(bandits) > 2 )
    {
	return bandits[0];
    }

    return 0;
}


/* Allows a player to purchase some overpriced venison. Returns 1
   (true) if this is done (i.e. the player had the money, the
   bandits were in, and the bandits were willing to sell to her)
   or 0 (false), if the player failed to purchase food. (Perhaps
   through poor syntax).
*/

int
purchase_food(string str)
{
    int price; // The price a player will pay for the venison.
    object venison; // food to be given to the player (if applicable)
    mixed abandit = bandits_home(); // one of the bandits in the room

    if (!(parse_command(str, ({}), "[roast] [some] 'food' / 'venison'")))
    {
	// command failed:
	notify_fail("Purchase what?\n");
	return 0;
    }
    
    if (! abandit)
    {
	write("There is nothing here to purchase!\n");
	return 1; 
    }

    // Calculating the asking price:

    price = 300 - (this_player()->query_skill(SS_TRADING));


    if (! MONEY_ADD(this_player(), - price))
    {
	// the player cannot afford to pay the bandits
	
	abandit->command("scowl");
	abandit->command("say No money, no food!");
	return 1; //command successful
    }

    venison = clone_object(THIEF_LAIR_DIR + "obj/roast_venison");
    if (venison->move(this_player()))
    {
	// move returned true, therefor player could not carry the venison

       	venison->move(this_object()); //move the venison into the room
	write("You are unable to carry the venison, and thus drop it "+
	      "on the ground.\n");
	say(capitalize(QCTNAME(this_player())) + " cannot carry the "+
	    "skewer of venison and thus drops it to the ground.\n");
    }

    tell_room(this_object(), capitalize(QCTNAME(this_player())) + 
	      " negotiates briefly with " + QTNAME(abandit) + ". " + 
	      capitalize(this_player()->query_pronoun()) + 
	      " hands over a few coins, and, in turn, is "+
	      "handed a skewer of roast venison.\n", this_player());
    
    this_player()->catch_msg("You negotiate briefly with " + 
			     QTNAME(abandit) + " and " + 
			     abandit->query_pronoun() + " agrees "+
			     "to sell you some of the venison for "+
			     MONEY_TEXT_SPLIT(price) + ". You pay the price, "+
			     "and are handed a juicy skewer of roast venison.\n"); 

    return 1; //command succesful
}	      
    

        

/* Called when the player tries to leave the room, this function prevents
   him from so doing if he is currently fighting more than 3 foes. This
   is rather likely to be the case if the bandits have taken a disliking 
   to him or her.
*/
int combat_block()
{
    int i; // loop index
    object player;
    object *foes; // All current enemies of the player.
    
    player = this_player();
    foes = player->query_enemy(-1);
   
    /* If the player is presently fighting more than 2 individuals (perhaps he has
       annoyed the bandits), they will not allow him to leave the room.
    */
       
    if (sizeof(foes) > 2)
    {
	write("Your foes are too numerous - they will not allow "+
			   "you to escape!!!\n");
	return 1;
    }
    
    return 0; // That is not the case - the player can leave normally.
}

/* Prevents players from investigating cave10 or 11 if there are 
   bandits present. Called from add_exit.
*/

int 
prevent_passage()
{    
    object *bandits = filter(all_inventory(this_object()), &->query_bandit());
    
    if (sizeof(bandits))
    {
	this_player()->catch_msg(QCTNAME(bandits[0]) + " firmly denies you access "+
				 "to that corner of the cavern.\n");
	return 1;
    }
   
    return combat_block(); // Check to see if the player is engaged with
                           // multiple foes before allowing him to leave.
 }
	
    
/* VBFC for the long description. It varies with the presence or absance
   of the bandits who normally inhabit it.
*/

string
long_descrip()
{ 
    if (!bandits_home())
    {
	return ("A large underground cavern. A bubbling brook meanders its "+
		"way across the cavern floor while a narrow fissure in the "+
		"ceiling extends as far as open sky. A pile of half-burnt "+
		"logs and ashes can be found in the center of the cavern. The "+
		"main entrance to the cavern can be found by following "+
		"the stream to the south, while alcoves extend from the "+
		"cavern to the northeast, and to the west.\n");    }

    return ("In a large underground cavern, occupied by a motley crew of "+
	    "unscrupulous looking individuals. They are gathered around a "+
	    "large campfire set in the middle of the cavern so that the "+
	    "smoke billows directly through a long, thin crevice in "+
	    "the ceiling. The smell of woodsmoke and cooked venison permeates "+
	    "the air. A bubbling brook flows through the center of the cavern, "+
	    "providing egress to the south, while alcoves extend from the "+
	    "cavern to the northeast, and to the west.\n");
}

/* Simple function to return different descriptions of the bonfire, depending
   whether its raging, or has died out due to the absance of the bandits.
*/

string
fire_descrip()
{
    if (bandits_home())
    {
	return ("A good-sized bonfire sits in the middle of the cavern. "+
		"You can see a couple of deer roasting over the bonfire "+
		"courtesy of two iron spits which are laid right through "+
		"it. Columns of smoke drift up from the fire towards the "+
		"fissure in the ceiling.\n");
    }
   
   return ("The remains of what must have been a fair-sized bonfire is "+
	   "set in the middle of the cavern floor, directly under the "+
	   "fissure in the ceiling. Mostly burnt logs are piled haphazardly "+
	   "amongst a pile of ashes.\n"); 
}

/* Function to return the description of the roasting venison. If the 
   bandits are not present, there will be no such venison.
*/

string
meat_descrip()
{
    if (bandits_home())
    {
	return ("A pair of delicious-looking deer carcasses are roasting "+
		"over the bonfire. If you are hungry, it may be possible to "+
		"'purchase' some roast venison.\n");
    }

    return ("Examine what?\n"); // No venison if there is no campfire.
}

void
create_banditcave_room()
{
    set_short("The bandits lair.");
    set_em_long("@@long_descrip@@");  

    add_item(({"wall", "walls"}),
	     "The walls of this cavern are composed of black "+
	     "basalt. They are lined with moisture and frequently covered "+
	     "in growths of green moss.\n");

    add_item(({"floor", "ground"}),
	    "Along the perimetre of the cavern, the ground is uneven and "+
	    "frequently moss covered. The cavern is cut in two by a bubbling "+
	    "underground stream. The ground in the center of the cavern, "+
	    "near the ashes has been smoothed out by constantly being "+
	    "trampled underfoot.\n");

    add_item(({"roof", "ceiling", "fissure", "crevice", "crack"}),
	     "The roof of the cavern is cut in two by a dramatic crevice "+
	     "which extends all the way to the surface of the mountain, "+
	     "hundreds of feet above you. From time to time, a chill breeze "+
	     "descends from this fissure invoking a rapid movement of air "+
	     "throughout the cavern. Thus, the air here is much less stale "+
	     "and humid then it is elsewhere under the mountain.\n");

    add_item(({"moss", "green moss"}),
	     "It is  a harmless seeming moss, dark-green in color. The "+
	     "sort which commonly carpets the ground in dark, wet "+
	     "places.\n");

    add_cmd_item(({"moss", "green moss"}), ({"eat"}),
             "You carefully pick some of the moss, then stick it "+
	     "cautiously in your mouth.\nYuck! It tastes terrible!\n");

    add_item(({"stream", "water", "brook", "bubbling brook"}),
	     "A bubbling brook enters the cavern through an impassibly "+
	     "narrow crack in the north wall and continues across the "+
	     "cavern to leave via a larger tunnel in the south wall. The "+
	     "water it carries appears to be clear and wholesome.\n");

    add_item(({"fire", "ashes", "logs", "burnt logs", "bonfire"}),
	     fire_descrip);

    add_item(({"meat", "venison", "deer", "roasting deer"}),
	     meat_descrip);

    add_exit(THIEF_LAIR_DIR + "cave8", "south", combat_block, 1, 0);
    add_exit(THIEF_LAIR_DIR + "store_inventory", "northeast", prevent_passage, 1, 0);
    add_exit(THIEF_LAIR_DIR + "cave10", "west", prevent_passage, 1, 0);
} 

void
init()
{
    ::init();
    add_action(drink_from_stream, "drink");
    add_action(purchase_food, "purchase");
}  



