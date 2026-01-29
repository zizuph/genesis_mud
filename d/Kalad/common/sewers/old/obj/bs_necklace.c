/*	Created by:	Sir Toby, 97-07-30
 *	Purpose:	Just a cool necklace with adding
 *			emotes to the player.
 *	Modified:	
 */

#pragma strict_types

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"

void
create_armour()
{
::create_armour();
    set_name("necklace");
    set_adj("black-steel");
    add_adj("chain");
    set_long("This is a very nice black-steel necklace. " +
	     "The chain is of medium length, connected to " +
	     "it is a small violet jewel in the shape of " +
	     "a teardrop.\n");

    add_item( ({"jewel","violet jewel","teardrop"}),"It is " +
	     "a small seemingly not too valuable jewel " +
	     "shaped like a teardrop.\n");
    add_item("chain","It is a nicely crafted chain.\n");

    set_ac(3);
    set_at(A_NECK);
    set_af(this_object());
 
    add_prop(OBJ_I_VALUE,500 + random(100));
    add_prop(OBJ_I_VOLUME,250 + random(50));
    add_prop(OBJ_I_WEIGHT,400 + random(70));

    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(OBJ_S_WIZINFO,"This is a necklace giving the player " +
	     "some nice emotes. And it is no_buy just to fool " +
	     "the players that it is something VERY good.\n");
    add_prop(MAGIC_AM_ID_INFO,({"The necklace is enchanted in " +
	     "some way.\n",10,
             "It seems to give the wearer additional powers.\n",30,
             "It will actually give the wearer rare ways of " +
             "expressing himself.\n",55,
	     "\nIf the wearer wants to utilize the powers of the " +
	     "necklace he must put an 'nec' in front of emotion " +
	     "desired.\n",85,
	     "The emotions are: \n" +
	     "   The Gentleman's	The Man's\n\n" +
	     "   -  assist              -  grin \n" +
	     "	 -  bow                 -  leave \n" +
	     "   -  first               -  legs \n" +
	     "   -  hand                -  point \n" +
	     "   -  kiss                -  thank \n" +
	     "   -  offer               -  think \n",95}));
}


int
wear(object what)
{

   if(TP->query_gender() == 0)
	{
	write("You wear the necklace with pride.\n");
   	return 0;
 	}

    write("The necklace resist your weak gender and " +
	  "you are unable to wear it.\n");
    return 1;
	
}


void
init()
{
    ::init();
    add_action("assist","necassist");
    add_action("bow","necbow");
    add_action("first","necfirst");
    add_action("hand","nechand");
    add_action("kiss","neckiss");
    add_action("offer","necoffer");
    add_action("grin","necgrin");
    add_action("leave","necleave");
    add_action("legs","neclegs");
    add_action("point","necpoint");
    add_action("thank","necthank");
    add_action("think","necthink");
}


void
assist()
{

    if(!TP->query_worn(this_object()))
	NF("Perhapps you should wear the necklace before you try that.\n");

    say(QCTNAME(this_player()) + " bows fluorishly and offers to " +
	"assist the lady in need.\n");
    
}


