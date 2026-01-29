/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/houses/pub.c
* Comments: Modified copy of inn in solace, coded by Nick.  Improved (?) by Ged & Gresolle
*		edited by Luther Oct. 2001
*/

inherit  "/std/room";
inherit "/lib/trade";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Cirath/common/mobber.h"

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

int test; /* to indicate that a test is going on, no money given. */
object tika; /* Unci */
object t;

/*
 * Prototypes
 */
int move_item(mixed arg);
                  
/*
 * Function name: reset_room
 * Description:   Set up the objects at reset
 */
 
void
reset_room()
{ 	
	object npc = present ("unci", TO);
    	if(!objectp(npc))
	{
    		bring_room_mob("unci", CIU_NPC + "unci", 1, 1);
	}
}
 
int
pressa(string str)
{
  	write("When you push the barrels you discover a hole, which you "+
        	"jumps into.\n");
  //	TP->move_living("through the hole",CIUBORI+"undergrund1");
  	return 1;
}

/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
 
void
create_room()
{
    	config_default_trade();
    	set_short("Ciubori City Hotel");
    	set_long("You are standing inside a dark pub. This is the place, "+
        	"the citizens of Ciubori use to go to after work to have "+
        	"a beer or three. There is a menu lying on the bar and some "+
        	"barrels standing in a corner of the room.\n");
    
    	add_item("bar", "An ordinary bar.\n");
    	add_item("menu", "It has a lot of readable words on it.\n");
    	add_item(({"barrel","barrels"}),"They are or have been filled with beer. They"+
             "look very heavy, in fact, you doubt that you could move them.\n");
    	add_item("chairs", "They look nice.\n"); 
    	add_item("tables", "They're here.\n");
    	add_cmd_item("menu", "read", "@@read");
    	add_cmd_item("barrels","push","@@pressa");

	INSIDE;
	
    	add_exit(CIU_STR + "tstreet3", "west", 0, 1); 
    	reset_room();
}

/*
 * Function name: init
 * Description:   Initalize the pub actions
 */
void
init()
{
    	::init(); /* Since it's a room this must be done. */
    	add_action("order", "buy");
    	add_action("order", "order");
}

/*
 * Function name: read
 * Description:   Read the menu
 * Arguments:     str - hopefully the menu
 */
int
read(string str)
{
    write("" +
        "   Bier                        20 copper\n" +
        "Try 'buy bier with gold' if you want to specify what to\n" +
        "pay with. You can also do  'buy 10 bier' would get you\n" +
        "ten biers from the bar, but it takes a little while to\n" +
        "give them all to you. You can't buy more than 10 at a time.\n");
    return 1;
}

/*
 * Function name: order
 * Description:   The buyer orders a drink
 * Arguments:     str - name of drink an possibly description on how to pay and
 *                      get the change
 */
int
order(string str)
{	
    	object guard = present ("unci", TO);
    	string name, str1, str2, str3;
    	int *arr, price, num;

    	NF("Unci isn't here.\n");
   	if (!guard)
        	return 0;
	
	NF("buy what?\n");
    	if (!str)
        	return 0;

    	if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
    	{
    	/* Well, maybe player has defined how payment will be done atleast? */
        str3 = "";
        	if (sscanf(str, "%s with %s", str1, str2) != 2)
        	{
            		str2 = "";
            		str1 = str;
        	}
    	}

    	if (sscanf(str1, "%d %s", num, str1) != 2)
        	num = 1;

    	if (num > 10) num = 10;

    	switch(str1)
    	{ 
    	case "bier":
    	case "biers":
      		name = "bier";
      		price = num * 10;
      		break;
    	default:
        	NF("I don't understand what you want to buy.\n");
        	return 0;
    	}

    	if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
        	return 0;  /* pay() handles notify_fail() call */
    
    	write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    	if (text(exclude_array(arr, 0, NUM-1)))
        	write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    		write("Unci starts working with your order.\n");
    		return move_item(({name, num, TP}));
}

int
move_item(mixed arg)
{
    	object drink, ob;
    	string file, name;
    	int i, num;

    	name = arg[0];
    	num = arg[1];
    	ob = arg[2];

    	for (i = 0; i < 10; i++)
    	{
        	num--;
       		file = OBJ + name;
        	drink = clone_object(file);

        	if (!test && (drink->move(ob)))
       	 	{
            		ob->catch_msg("You drop the " + drink->short() +
                		" on the floor.\n");
           		say(QCTNAME(ob) + " drops a " + drink->short() +
                		" on the floor.\n", ob);
            		drink->move(TO);
        	} 
        	else if (!test) 
        	{
            		if (num == 0)
            		{
                	if (arg[1] > 1)
                	{
                    	ob->catch_msg("You get some " + drink->plural_short() +
                        	".\n");
                    	say(QCTNAME(ob) + " buys some " + drink->plural_short() +
                        	".\n", ob);
                	} 	
                	else 
                	{
                    		ob->catch_msg("You get the " + drink->short() + ".\n");
                    		say(QCTNAME(ob) + " buys " + drink->short() + ".\n",
                        	ob);
                	}
            		}
        	} 	
        	else 
        	{
            		say(QCTNAME(ob) + " seems to be estimating something.\n",
                		ob);
        		return 1;
        	}
        	if (num < 1)
           		break;
    	}

    	if (num > 0)
        	call_out("move_item", 1, ({name, num, ob}));
    		return 1;
}

/*
 * Function name: test
 * Description:   To allow the buyer to see what would happen with change and
 *                payment depending on how the buyer chooses to pay.
 * Arguments:     str - name of drink an possibly description on how to pay and
 *                      get the change
 */
int
test(string str)
{
    	int i;
    	string str1;
    
    	NF("Test what?\n");
    
    	if (sscanf(str, "buy %s", str1)) {
        	test = 1;
        	write("This would be the result of a buy:\n");
       		i = order(str1);
        	test = 0;
        	return i;
    	}
}
