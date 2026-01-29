/* Inn in solace, coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

inherit  SOLINROOM;
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

int test;          /* to indicate that a test is going on, no money given. */
object tika ;      /* Tika, the girl that serves in the inn. */
object schorsch;   /* Gives out a tour quest. */

/*
 * Prototypes
 */
int move_item(mixed arg);
                  
/*
 * Function name: reset_room
 * Description:   Set up the objects at reset
 */
void
reset_solace_room()
{
  if (!tika)
    {
      tika = clone_object(NPC + "tika");
      tika->move_living("xxx", TO);
    }
  if(!schorsch)
    set_alarm(200.0, -1.0, "schorsch_comes");
}

void
schorsch_comes()
{
  if (schorsch)
    return;
  schorsch = clone_object("/d/Krynn/gnome/schorsch/schorsch");
  schorsch->move_living("comes in with slowly", TO);
}

/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
void
create_solace_room()
{
    config_default_trade();
    set_short("The Inn of The Last Home");
    set_long("You are in the Inn of The Last Home. There is a menu on the bar. " +
	     "You find this place rather cozy, with a lot of tables and chairs " +
	     "and a warm fireplace. The living tree in which it is built " +
	     "wraps its ancient branches around it lovingly. The walls " +
	     "and the fixtures are crafted around the boughs of the tree " +
	     "with such care as to make it impossible to tell where " +
	     "nature's work leaves off and man's begins. The bar seems " +
	     "to ebb and flow like a polished wave around the living " +
	     "wood that supports it. The stained glass in the window " +
	     "panes casts welcoming flashes of vibrant color across " +
	     "the room. You can smell the beer from the kegs " +
	     "and the food from the kitchen.\n");
    
    add_item("bar", "A nice looking wooden bar with a menu on it.\n");
    add_item("menu", "@@read");
    add_item(({"chairs", "walls", "fixtures"}),
        "They are made out of oak wood, as is the rest of the place.\n"); 
    add_item("tables", "They are made of oak wood, and their surfaces "+
        "are darkened by spilled beer.\n");
    add_cmd_item("menu", "read", "@@read");
    add_item(({"branches", "branch"}), 
        "The branches are huge, thick as many tree-trunks, and part of "+
        "the single, ancient Vallenwood tree which supports this structure.\n");
    add_item(({"window", "stained glass", "panes"}),
        "Vibrant in colour, the window allows sunlight to penetrate and "+
        "illuminate, but it is too opaque to see through.\n");
    add_item(({"tree", "vallenwood"}),
        "This tree seems particularly fond of this inn, as it seems to hold "+
        "the structure in loving arms. It is huge, and quite old. Perhaps it "+
        "pre-dates the Cataclysm.\n");
    add_item(({"kegs", "keg"}),
        "Otik brews the beer himself, since trade has been disrupted by so "+
        "much war. He would not be pleased if you tried to abscond with any "+
        "of his kegs, but would be happy to sell you some, instead.\n");
    
    add_exit(TDIR + "platform2", "out", 0);
/*    add_exit(TDIR + "kitchen", "north", 0); */
    reset_solace_room();
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
    add_action("test", "test");
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
	  "   Small beer                 12 cc\n" +
	  "   Some really sweet wine     72 cc\n" +
	  "   An apple                   25 cc\n" +
	  "   Potato soup                80 cc\n" +
	  "   Plate of spiced potatoes  210 cc\n\n" +
	  "Try 'buy beer with gold' if you wanna specify what to\n" +
	  "pay with, or 'test buy beer' to see what would happen\n" +
	  "if you typed 'buy beer'. 'buy 10 beer' would get you\n" +
	  "ten beers from the bar, but it takes a little while to\n" +
	  "give them all to you. You can only order a maximum of 10 items at a time\n" +
	  "since Tika isn't strong enough to carry more.\n");
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
    string name, str1, str2, str3;
    int *arr, price, num;
    
    NF("Tika isn't here to answer your call.\n");
    if (!tika || !P(tika, TO))
      return 0;
    
    NF("buy what?\n");
    if (!str)
      return 0;
    
    /* Has the player defined how payment will be done and what change to get back? */  
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

    if (num == 0)
      num = 1;
    
    switch(str1)
      {
	case "beer":
	case "beers":
	case "small":
	case "small beer":
	  name = "beer";
	  price = num * 12;
	  break;
	case "wine":
	case "wines":
	case "sweet":
	case "sweet wine":
	  name = "wine";
	  price = num * 72;
	  break;
	case "apple":
	case "apples":
	  name = "iapple";
	  price = num * 25;
	  break;
	case "potato":
	case "potato soup":
	case "soup":
	case "soups":
	  name = "isoup";
	  price = num * 80;
	  break;
	case "potatoes":
	case "spiced":
	case "plate of spiced potatoes":
	case "plate":
	case "plates":
	  name = "potatoes";
	  price = num * 210;	
	  break;
	default:
	  NF("I don't understand what you want to buy.\n");
	  return 0;
      }
    if (num > 10)
      {
	  NF("Tika can only carry a maximum of 10 items at a time!\n");
	  return 0;
      }
    
    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
    
    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
      write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
    write("Tika gets to work.\n");
    
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
			    ob->catch_msg("You get " + drink->short() + ".\n");
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
      set_alarm(1.0, 0.0, &move_item(({name, num, ob})));
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
    if (!str || !stringp(str))
      return 0;
    
    if (sscanf(str, "buy %s", str1)) 
      {
	  test = 1;
	  write("This would be the result of a buy:\n");
	  i = order(str1);
	  test = 0;
	  return i;
      }
}

