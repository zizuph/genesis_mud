/* 
 * Props to Nick
 * Morning coffee shop by Mortis 08.2005
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <money.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

inherit CITY_ROOMBASE;
inherit "/lib/trade";

#define VIEWSOUTH	(ROOM + "plaza")
#define NUM	sizeof(MONEY_TYPES)

string
query_to_jail()
{
  return "south";
}

int test;        /* Test has been removed. */
object barista;  /* The barista that serves customers. */
/* object jakey;     */

/*
 * Prototypes
 */
int move_item(mixed arg); 
                  
/*
 * Function name: reset_room
 * Description:   Set up the objects at reset
 */

void
reset_palan_room()
{
  if (!objectp(barista))
    {
      barista = clone_object(LIV + "ebarista");
	  /*barista->arm_me();*/
      barista->move(TO);
    }

 /* if ( !jakey )
  {
     jakey = clone_object("/d/Krynn/qualinesti/npc/hunter");
     jakey->move(TO, 1);
     jakey->command("sit at bar");
  }
  */
}

/*
 * Function name: create_room
 * Description:   Set up default trade and configure it if wanted.
 */

/*
 * Function name: init
 * Description:   Initalize the pub actions
 */    
 
void 
init()
{    
    ::init();
    add_action("action_sit", "sit");
	add_action("action_stand", "stand");
    add_action("order", "buy");
    add_action("order", "order");
}

int 
action_sit(string str)
{
        if(TP->query_prop(TSIT))
        {
                write("But you are already sitting by a table! How do you expect to sit in two places at once?\n");
                return 1;
        }
           
        if(TP->query_prop(FSIT))
        {
                write("But you are already sitting by the window! How do you expect to sit in two places at once?\n");
                return 1;
        }
           
        if(TP->query_prop(BSIT))
        {
                write("But you are already sitting by the counter! How do you expect to sit in two places at once?");
                return 1;
        }
           
        if(str == "around table" | str == "around a table" | str == "at table" | str == "at a table" | str == "by table" | str == "by a table" | str == "table" | str == "chair around table" | str == "in chair around table" | str == "in a chair around a table" | str == "chair at table" | str == "in chair at table" | str == "in a chair at a table" | str == "chair by table" | str == "in chair by table" | str == "in a chair by a table") 
        {
                TP->catch_msg("You sit down in one of the comfortable chairs near a table.\n");
                say(QCTNAME(TP) + " sits down in one of the comfortable looking chairs near a table.\n");
                TP->add_prop(TSIT, 1);
                TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting near a table");
                return 1;
        }
        
        if(str == "around window" | str == "around the window" | str == "by window" | str == "by the window" | str == "window" | str == "chair around window" | str == "in chair around window" | str == "in a chair around the window" | str == "chair by window" | str == "in chair by window" | str == "in a chair by the window") 
        {
                TP->catch_msg("You sit down in one of the comfortable chairs near the window.\n");
                say(QCTNAME(TP) + " sits down in one of the comfortable looking chairs near the window.\n");
                TP->add_prop(FSIT, 1);
                TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting near the window");
                return 1;
        }
	
	        if(str == "at bar" | str == "at the bar" | str == "by bar" | str == "by the bar" | str == "bar" | str == "stool at bar" | str == "in stool at bar" | str == "in a stool at the bar" | str == "stool by bar" | str == "in stool by bar" | str == "in a stool by the bar")
        {
                TP->catch_msg("You sit down on one of the stools at the counter.\n");
                say(QCTNAME(TP) + " sits down on a stool at the counter.\n");
                TP->add_prop(BSIT, 1);
                TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting at the counter");
                return 1;
        }
	
        else
        {
                TP->catch_msg("Where would you like to sit?  By the window, the bar, or around a table?\n");
                return 1;
        }
        
        return 1;
}

int 
action_stand(string str)
{
        if(str == "up" || !str)
        {
                if(TP->query_prop(TSIT))
                {
                        
                        TP->catch_msg("You stand up and leave the table.\n");
                        say(QCTNAME(TP)+" stands up from the table.\n");
                        TP->remove_prop(TSIT);
                        TP->remove_prop(LIVE_S_EXTRA_SHORT);
                        return 1;
                }
                
                if(TP->query_prop(FSIT))
                {
                        TP->catch_msg("You stand up and move away from the window.\n");
                        say(QCTNAME(TP)+" stands up and moves away from the window.\n");
                        TP->remove_prop(FSIT);
                        TP->remove_prop(LIVE_S_EXTRA_SHORT);
                        return 1;
                }
                
                if(TP->query_prop(BSIT))
                {
                        TP->catch_msg("You stand up from your stool at the counter.\n");
                        say(QCTNAME(TP)+" stands up from a stool at the counter.\n");
                        TP->remove_prop(BSIT);
                        TP->remove_prop(LIVE_S_EXTRA_SHORT);
                        return 1;
                }
        }
        
        else
        {
                TP->catch_msg("Stand?  Stand up?\n");
                return 1;
        }
	 	TP->catch_msg("You would need to sit first.\n");
		return 1;
}

void leave_inv(object ob, object to)
{
        ::leave_inv(ob, to);    
        
        if(!objectp(to) || !objectp(ob))
                return;
                
        if(TP->query_prop(TSIT))
        {
                TP->catch_msg("You stand up from the table before leaving.\n");
                say(QCTNAME(TP) + " stands up from the table as "+ HE(TP) +" leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);
                TP->remove_prop(TSIT);
        }
          
        if(TP->query_prop(FSIT))
        {
                TP->catch_msg("You stand up from your spot near the window before leaving.\n");
                say(QCTNAME(TP) + " stands up from " + HIS(TP) + "spot at the window as " + HE(TP) +" leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);            
                TP->remove_prop(FSIT);
        }
        
        if(TP->query_prop(BSIT))
        {
                TP->catch_msg("You stand up from the counter before leaving.\n");        
                say(QCTNAME(TP) + " stands up from the counter as " + HE(TP) +" leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);
                TP->remove_prop(BSIT);
        }
}

nomask public void
create_palan_room()
{
    config_default_trade();

    SHORT("A small cafe");
    LONG("Though the floor and ceiling of this cafe are of polished, "
	+ "translucent marble, the walls are paneled in wood painted grey at the "
	+ "bottom and fading gently into pale swaths of pink, purple, and "
	+ "orange.  A long, brightwood counter is to your east along the southern "
	+ "wall behind which is a high, thin window peering out at the clouds "
	+ "and building tops in the south of the plaza.  Below the window is a "
	+ "chalkboard menu with today's offerings chalked in pastel lettering.  "
	+ "Brightwood tables lit by candle and padded chairs are arrayed "
	+ "throughout the cafe with a bar to sit at along the northern wall.\n");

	ITEM(({"wood", "brightwood"}), "The brightwood of the tables, chairs and "
	+ "counter is not so much bright as pale.  It is probably a type of birch "
	+ "or poplar.\n");
	ITEM(({"window", "high window", "thin window", "high thin window"}),
	  "A thin window runs nearly the length of the counter high on the "
	+ "southern wall.  Painted in grey letters is the name of the cafe, "
	+ "`Light Hart Cafe' with its logo of an antlered deer head before "
	+ "thin clouds in between the words Hart and Cafe.  You can peer out "
	+ "the window to see who's in the plaza with <view plaza>.\n");
	ITEM("counter", "A well built counter of brightwood lines the southern "
	+ "wall wrapping around to the east wall and a kitchen door in the "
	+ "northeast.  Behind it work the waitresses of the Light Hart.  Near "
	+ "the door atop the counter is a great brew apparatus for serving "
	+ "coffees.\n");
	ITEM(({"chairs", "chair", "tables", "table", "bar", "furniture"}),
	  "Constructed in simple designs from a pale birch or poplar wood is the "
	+ "furniture of the Light Hart.  Chairs have a thin, grey pad or cushion "
	+ "to sit on and tables are draped with grey table cloths with one large "
	+ "stripe of white through their middle.  Atop the tables are small "
	+ "oil well candles set within carved, yellow glass cylinders.\n");
	ITEM("floor", "The marble blocks of the floor are checkered grey and "
	+ "white and polished to a reflective shine.\n");
	ITEM(({"ceiling", "marble"}), "The translucent marble of the "
	+ "floor and ceiling is polished and clean.\n");
	ITEM(({"wall", "walls"}), "The walls of the cafe are paneled in wood "
	+ "painted grey at the bottom and fading gently into pale swaths of "
	+ "pink, purple, and orange.\n");
	ITEM(({"candle", "candles", "cylinder", "cylinders"}), "Small candles "
	+ "atop each table shed yellow light from within their yellow glass "
	+ "holders.  The candles burn a clear oil and are set within cylinders "
	+ "of yellow glass somehow carved to give the appearance of raised "
	+ "pyramids covering their exterior.\n");
	ITEM(({"brewer", "apparatus"}), "The bell and whistle atop this "
	+ "polished steel apparatus hint at its origins.  Steam rises from the "
	+ "apparatus below the counter along with the rich smell of coffees being "
	+ "brewed.\n");

	ITEM(({"sign", "menu", "list", "pricelist", "offering", "offerings",
		"chalkboard"}),
	  "A large, black chalkboard hangs below the window behind the counter.  "
	+ "You can read it to see what the Light Hart Cafe is offering today.  "
	+ "Its list of menu items is written in various pale pastel colours.\n");

	CMD(({"sign", "menu", "list", "pricelist", "offering", "offerings",
		"chalkboard"}), "read", "@@read");
	CMD(({"plaza", "the plaza"}), "view",
		  "@@view_plaza");

	EXIT(ROOM + "plaza", "south", 0, 0);

    reset_palan_room();
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
      "  ._____________________________________.\n" +
	  "  | Today's Coffees:                   ||\n" +
	  "  |------------------------------------||\n" +
	  "  | Evening Vanilla Roast     | 155 cc ||\n" +
	  "  | Light Hart Special Blend  | 125 cc ||\n" +
	  "  |                           |        ||\n" +
	  "  |---------------------------+--------||\n" +
	  "  | Delectables:              |        ||\n" +
	  "  |---------------------------+--------||\n" +
	  "  | Hartvale Red, by glass    |  95 cc ||\n" +
	  "  |                           |        ||\n" +
	  "  | Aniseed Toast             |  80 cc ||\n" +
	  "  | Turkey Paninos            | 190 cc ||\n" +
	  "  | Bowl of Risotto           | 170 cc ||\n" +
      "  |___________________________|________||\n" +
      "  \\___________________________\\________\\|" + "\n");
    return 1;
}

/*
 * Function name: order
 * Description:   The buyer orders a drink
 * Arguments:     str - name of drink and possibly description on how to pay and
 *                      get the change
 */

int
order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;
    
    NF("The barista is not here to fix your order.\n");
    if (!barista || !P(barista, TO))
      return 0;
    
    NF("Buy what?\n");
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
	case "roast":
	case "roasts":
	case "evening roast":
	case "evening roasts":
	case "vanilla roast":
	case "vanilla roasts":
	case "evening vanilla roast":
	case "evening vanilla roasts":
	  name = "evening_vanilla";
	  price = num * 155;
	  break;
	case "coffee":
	case "coffees":
	case "blend":
	case "blends":
	case "special blend":
	case "special blends":
	case "light hart special blend":
	case "light hart special blends":
	  name = "special_blend";
	  price = num * 125;
	  break;
	case "wine":
	case "wines":
	case "red":
	case "reds":
	case "hartvale red":
	case "hartvale reds":
	case "glass of wine":
    case "glasses of wine":
	case "red wine":
	case "red wines":
	  name = "hartvale_red";
	  price = num * 95;
	  break;
	case "toast":
	case "toasts":
	case "aniseed toast":
	case "aniseed toasts":
	  name = "aniseed";
	  price = num * 80;
	  break;
	case "paninos":
	case "panino":
	case "turkey panino":
	case "turkey paninos":
	  name = "panino";
	  price = num * 190;
	  break;
	case "risotto":
	case "bowl":
	case "bowl of risotto":
	case "bowls":
	case "risottos":
	case "bowls of risotto":
	  name = "risotto";
	  price = num * 170;
	  break;
	default:
	  NF("Smiling softly the Lady says:  I don't understand what you "
	   + "want to buy.\n");
	  return 0;
      }
    if (num > 10)
      {
	  NF("The staff is good but can only fix a maximum of 10 items at a "
	  + "time.\n");
	  return 0;
      }
    
    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
    
    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
      write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
    write("The waitresses fix your order.\n");
    
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

view_plaza()
{
	/* This function returns an equivalent of 'look' from plaza
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string vdesc;

	write(VIEWSOUTH->long());
	target = find_object(VIEWSOUTH);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(vdesc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write("Through the window along the south wall, you can make out "
	+ vdesc + " on the ground.\n");

	if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write("Outside in the plaza you see " + vdesc + ".\n");

	say(QCTNAME(TP) + " gazes out the window along the south wall.\n");
 
	return 1;
}
