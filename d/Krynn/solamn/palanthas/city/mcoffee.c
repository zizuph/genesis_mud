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
#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

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
      barista = clone_object(LIV + "mbarista");
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
 * Description:   Set up default trade and cofigure it if wanted.
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
	
	        if(str == "at counter" | str == "at the counter" | str == "by counter" | str == "by the counter" | str == "counter" | str == "stool at counter" | str == "in stool at counter" | str == "in a stool at the counter" | str == "stool by counter" | str == "in stool by counter" | str == "in a stool by the counter")
        {
                TP->catch_msg("You sit down on one of the stools at the counter.\n");
                say(QCTNAME(TP) + " sits down on a stool at the counter.\n");
                TP->add_prop(BSIT, 1);
                TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting at the counter");
                return 1;
        }
	
        else
        {
                TP->catch_msg("Where would you like to sit?  By the window, the counter, or around a table?\n");
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

    SHORT("A small coffee shop");
    LONG("Though the floor and ceiling are of rich, translucent marble, the "
	+ "walls have been lined with dark, polished wood.  Low burning oil lamps "
	+ "hang high upon them from dark iron chains providing a soft glow from "
	+ "the corners.  The great window in the south wall as well as the one in "
	+ "the door is covered with a dark, dull green shade.  Wooden chairs and "
	+ "tables line the walls except in the north where from behind the "
	+ "counter a barista provides service.  Behind the counter is a glossy, "
	+ "white sign bearing the shop's offerings in black calligraphic "
	+ "strokes.\n");

	ITEM("counter", "A well built counter of oak, glass, and polished steel "
	+ "where food is displayed.  Several stools line the west end, the "
	+ "barista normally serves from behind the middle where small burners "
	+ "keep warm the coffee pots.  The east end is mostly glass and rows "
	+ "of food where the line from the door begins.\n");

    ITEM("food", "Behind the clean glass of the counter are rows of small, "
	+ "flat biscuits, dried apricots, grapefruit halves, and poppy-seed "
	+ "muffins.\n");

	ITEM(({"biscuit", "biscuits", "flat biscuits", "apricots",
	"dried apricots", "halves", "grapefruit", "grapefruit halves", "muffins",
	"poppy-seed muffins", "muffin"}), "Why don't you buy one and see?\n");

	ITEM(({"stool", "stools", "chairs", "chair", "tables", "table",
		"furniture"}), "Simple but sturdy wooden furniture.\n");

	ITEM(({"window", "windows"}), "Only the forms of passersby outside can "
	+ "be seen through the dull green window shades which cast a slight "
	+ "green tint upon the translucent marble of the floor.  You may look "
	+ "out the window onto the plaza with <view plaza>.\n");

	ITEM(({"floor", "ceiling", "marble"}), "The translucent marble of the "
	+ "floor and ceiling is polished and clean.\n");

	ITEM(({"lamp", "lamps"}), "Small oil lamps hang from thin, dark iron "
	+ "chains on iron pegs high on the wooden walls drawing little attention "
	+ "as they softly illuminate the corners.\n");

	ITEM(({"brewer", "brewers"}), "Two tall, polished metal cylinders brew "
	+ "the large amounts of coffee needed to run a coffee shop.  Nozzles at "
	+ "the bottom fill the pots from which the barista serves his "
	+ "customers.\n");

	ITEM(({"sign", "menu", "list", "pricelist", "offering", "offerings"}),
	  "A large, glossy white sign hangs from thin, dark iron chains on the "
	+ "wall behind the counter.  You may read it to see the Dawnbringer's "
	+ "offerings for the day.\n");

	CMD(({"sign", "menu", "list", "pricelist", "offering", "offerings"}), 
	  "read", "@@read_menu");
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

public int
read_menu()
{
	write("You peruse the menu.\n");

    write("" +
      "  .___________________________________.\n" +
	  "  | Strong Morne Coffee      | 125 cc ||\n" +
	  "  | Breakfast Biscuit        |  25 cc ||\n" +
	  "  | Box of Dried Apricots    |  45 cc ||\n" +
	  "  | Grapefruit Halves        |  30 cc ||\n" +
	  "  | Lemon Poppy-seed Muffin  | 150 cc ||\n" +
      "  |__________________________|________||\n" +
      "  \\__________________________\\________\\|" + "\n");

	say(QCTNAME(TP) + " peruses the menu behind the counter.\n");
	
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
	case "coffee":
	case "coffees":
	case "morne coffee":
	case "morne coffees":
	case "strong coffee":
	case "strong coffees":
	case "strong morne coffee":
	case "strong morne coffees":
	  name = "morne_coffee";
	  price = num * 125;
	  break;
	case "biscuit":
	case "biscuits":
	case "breakfast biscuit":
	case "breakfast biscuits":
	  name = "bbiscuit";
	  price = num * 25;
	  break;
	case "box":
	case "boxes":
	case "apricot":
	case "apricots":
	case "dried apricot":
	case "dried apricots":
	case "box of apricots":
    case "boxes of apricots":
	case "box of dried apricots":
	case "boxes of dried apricots":
	  name = "box_apricots";
	  price = num * 45;
	  break;
	case "grapefruit":
	case "grapefruits":
	case "half":
	case "halves":
	case "grapefruit half":
	case "grapefruit halves":
	  name = "grape_half";
	  price = num * 30;
	  break;
	case "muffin":
	case "muffins":
	case "poppy muffin":
	case "poppy muffins":
	case "poppy-seed muffin":
	case "poppy-seed muffins":
	case "lemon muffin":
	case "lemon muffins":
	case "lemon poppy-seed muffin":
	case "lemon poppy-seed muffins":
	case "lemon poppy muffin":
	case "lemon poppy muffins":
	  name = "lpmuffin";
	  price = num * 150;
	  break;
	default:
	  NF("Smiling slightly the Barista says:  I don't understand what you "
	   + "want to buy.\n");
	  return 0;
      }
    if (num > 10)
      {
	  NF("The barista is good but can only fix a maximum of 10 items at a "
	  + "time.\n");
	  return 0;
      }
    
    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
    
    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
      write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
    write("The barista fixes your order.\n");
    
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
    string desc;

	write(VIEWSOUTH->long());
	target = find_object(VIEWSOUTH);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write("Through the window along the south wall, you can make out "
	+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write("Outside in the plaza you see " + desc + ".\n");

	say(QCTNAME(TP) + " gazes out the window along the south wall.\n");
 
	return 1;
}
