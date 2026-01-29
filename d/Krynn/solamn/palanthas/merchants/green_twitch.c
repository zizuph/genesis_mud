/* 
 * The Green Twitch Inn by Mortis 01.2006
 *
 * Room tells?
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <money.h>
#include <cmdparse.h>
#include <living_desc.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>

inherit MERCH_ROOMBASE;
inherit "/lib/trade";

#define VIEWSOUTH	(MERCH + "m04")
#define NUM	sizeof(MONEY_TYPES)

string
query_to_jail()
{
  return "west";
}

int test;        /* Test has been removed. */
object innkeep;  /* The innkeep that serves customers. */

int move_item(mixed arg); 
                  
void
reset_palan_room()
{
  if (!objectp(innkeep))
    {
      innkeep = clone_object(MERCH + "living/gtinnkeep");
      innkeep->move(TO);
    }
}
 
nomask public void
create_palan_room()
{
    config_default_trade();

    SHORT("A warm marble inn with a brick chimney");
    LONG("The inn is warm with the smells of ale and meats turning on spits "
	+ "in the red brick fireplace.  The floor and walls are of translucent "
	+ "marble, and great oakwood beams support the low ceiling.  Green paper "
	+ "lanterns hang from ceiling beams shedding green candlelight about the "
	+ "room.  Large round tables fill the room with a few by the windows "
	+ "beside the doors along the west wall, and cushioned stools stand by "
	+ "the bar in the east.  On the wall behind the counter is a marble "
	+ "sign.\n");

	ITEM(({"wood", "beams", "oakwood", "oak", "ceiling"}), "Great oakwood "
	+ "beams support a low ceiling above.  From them hang green paper "
	+ "lanterns.\n");
	ITEM(({"fire", "fireplace", "brick", "bricks", "spit"}), "There is a "
	+ "fireplace in the north of the inn built from red bricks.  Its "
	+ "considerable size allows for an iron spit.  Currently turning on the "
	+ "spit at the moment is " + "@@on_spit@@" + ".\n");
	ITEM(({"paper", "lantern", "lanterns", "paper lanterns", "green paper",
		   "green lanterns", "green paper lanterns"}), "Green paper "
	+ "lanterns hang from the great oakwood ceiling beams shedding green "
	+ "candlelight about the room adding to the warm atmosphere.\n");
	ITEM(({"window", "windows"}), "There are windows to either side of the "
	+ "entry door in the west wall.  You can peer out them with <view "
	+ "plaza>.\n");
	ITEM("bar", "A well built counter of darkwood lines the eastern "
	+ "wall.  Behind it works the innkeep of the Green Twitch Inn.  Stools "
	+ "with cushioned tops are arranged before it.\n");
	ITEM(({"chairs", "chair", "tables", "table", "furniture", "stool",
		"stools"}), "Constructed in simple designs from a dark stained wood "
	+ "is the furniture of the Green Twitch.  Chairs as well as stools have "
	+ "a brown pad or cushion to sit on and tables are draped with beige "
	+ "table cloths.\n");
	ITEM("floor", "The marble blocks of the floor are tinted beige likely "
	+ "from high traffic, but they are polished nonetheless.\n");
	ITEM(({"wall", "walls", "marble"}), "The translucent marble of the "
	+ "walls is polished and clean.\n");
	ITEM(({"sign", "menu", "list", "pricelist", "offering", "offerings",
		"chalkboard"}), "A large, marble sign hangs behind the counter.  "
	+ "You can read it to see what's on the menu for today.\n");

	CMD(({"sign", "menu", "list", "pricelist", "offering", "offerings",
		"chalkboard"}), "read", "@@read");
	CMD(({"plaza", "the plaza", "court", "cul-de-sac"}), "view",
		  "@@view_plaza");

	EXIT(MERCH + "m04", "west", 0, 0);
	EXIT(MERCH + "green_twitch_common", "south", 0, 0);

    reset_palan_room();
}

void 
init()
{    
    ::init();
    ADD("action_sit", "sit");
	ADD("action_stand", "stand");
	ADD("action_stand", "rise");
    ADD("order", "buy");
    ADA("order");
}

int
read(string str)
{
	write("" +
	"  .__________________________________________.\n" +
	"  | Today's Menu:                           ||\n" +
	"  |-----------------------------------------||\n" +
	"  | Rotisserie Pheasant            |  12 sc ||\n" +
	"  | Rack of Lamb                   |  13 sc ||\n" +
	"  | Rotisserie Chicken (whole)     |  50 sc ||\n" +
	"  | Roasted Pork Pickin'           |  13 sc ||\n" +
	"  | Roasted Boar (whole)           |  80 sc ||\n" +
	"  |                                |        ||\n" +
	"  |--------------------------------+--------||\n" +
	"  | Drinks:                        |        ||\n" +
	"  |--------------------------------+--------||\n" +
	"  | Mug of Twitch Ale              |  50 cc ||\n" +
	"  | Mug of Harrmoor Dark Beer      |  50 cc ||\n" +
	"  | Glass of Sancristiovese        |  60 cc ||\n" +
	"  | Black Meade                    | 100 cc ||\n" +
	"  |________________________________|________||\n" +
	"  \\________________________________\\________\\|\n" +
	"               8               8\n" +
	"               8               8\n" +
	"     _________/ \\_____________/ \\___________\n" +
	"    |                                       |\n" +
	"    |  Keys to the cots in the common room  |\n" +
	"    |  are available  for sale for 40cc if  |\n" +
	"    |  you <buy key>.                       |\n" +
	"    |_______________________________________|"	+ "\n");
	return 1;
}

string
on_spit()
{
	return one_of_list(({"a line of pheasants", "a small pig", "a small boar",
	"a pair of chickens", "a rack of lamb"}));
}

int
order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;
    
    NF("The innkeep is not here to fix your order.\n");
    if (!innkeep || !P(innkeep, TO))
      return 0;
    
    NF("Buy what?\n");
    if (!str)
      return 0;
    
	/* Has the player defined how payment will be done and 
	 * what change to get back? */  
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
    
	if (parse_command(str1, ({}), "[rotisserie] 'pheasant'"))
	{
		name = "roti_pheasant";
		price = num * 144;
	}

	else if (parse_command(str1, ({}), "[rack] [of] 'lamb'"))
	{
		name = "rack_lamb";
		price = num * 156;
	}

	else if (parse_command(str1, ({}), "[whole] [rotisserie] 'chicken' [whole]"))
	{
		name = "roti_chicken";
		price = num * 600;
	}

	else if (parse_command(str1, ({}), "[roasted] 'pork' / 'pickin' [pickin]"))
	{
		name = "roast_pork";
		price = num * 156;
	}

	else if (parse_command(str1, ({}), "[roasted] 'boar' [whole]"))
	{
		name = "roast_boar";
		price = num * 960;
	}

	else if (parse_command(str1, ({}), "[mug] [of] [twitch] 'ale' [mug]"))
	{
		name = "twitch_ale";
		price = num * 50;
	}

	else if (parse_command(str1, ({}), "[mug] [of] [harrmoor] [dark] 'beer' [mug]"))
	{
		name = "harrmoor_beer";
		price = num * 50;
	}

	else if (parse_command(str1, ({}), "[glass] [of] 'sancristiovese' [glass]"))
	{
		name = "glass_sancrist";
		price = num * 60;
	}

	else if (parse_command(str1, ({}), "[black] 'meade' / 'mead'"))
	{
		name = "black_meade";
		price = num * 100;
	}

	else if (parse_command(str1, ({}), "'key'"))
	{
		name = "green_twitch_key";
		price = num * 40;
	}

	else
	{
	  NF("Scratching his head, the innkeep says:  Wha... ?!?  What did you "
	   + "want to buy.\n");
	  return 0;
	}
    
	if (num > 10)
	{
		NF("The staff is good but can only fix a maximum of 10 items at a "
		+ "time.\n");
		return 0;
	}

	if (num > 1 && name == "green_twitch_key")
	{
		NF("Keys are only for sale one a piece.  How many cots did you "
		+ "intend to sleep on anyway?\n");
		return 0;
	}
    
    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
    
    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
		write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
    write("The innkeep fixes your order.\n");
    
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
	  file = MERCH + "obj/" + name;
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
	write("Through the windows along the west wall, you can make out "
	+ vdesc + " on the ground.\n");

	if (strlen(vdesc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write("Outside in the plaza you see " + vdesc + ".\n");

	say(QCTNAME(TP) + " gazes out the windows along the west wall.\n");
 
	return 1;
}

int 
action_sit(string str)
{
	NF("Where would you like to sit?  By the window, the bar, or around a "
	+ "table?\n");

	if (!str)
		return 0;

	if(TP->query_prop(TSIT))
	{
		write("But you are already sitting by a table! How do you "
		+ "expect to sit in two places at once?\n");
		return 1;
	}
           
	if(TP->query_prop(FSIT))
	{
		write("But you are already sitting by the window! How do you "
		+ "expect to sit in two places at once?\n");
		return 1;
	}
           
	if(TP->query_prop(BSIT))
	{
		write("But you are already sitting by the counter! How do "
		+ "you expect to sit in two places at once?");
		return 1;
	}
           
	if(parse_command(str, ({}), "[around] [at] [by] [in] [a] [the] 'table' / 'chair' [around] [at] [by] [in] [a] [the] [table]"))
	{
		TP->catch_msg("You sit down in one of the comfortable chairs near a "
		+ "table.\n");
		say(QCTNAME(TP) + " sits down in one of the comfortable looking "
		+ "chairs near a table.\n");
		TP->add_prop(TSIT, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting near a table");
		return 1;
	}
        
	if(parse_command(str, ({}), "[around] [at] [by] [in] [a] [the] 'table' / 'chair' / 'window' [around] [at] [by] [in] [a] [the] [table] [window]"))
	{
		TP->catch_msg("You sit down in one of the comfortable chairs near "
		+ "the window.\n");
		say(QCTNAME(TP) + " sits down in one of the comfortable looking "
		+ "chairs near the window.\n");
		TP->add_prop(FSIT, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting near the window");
		return 1;
	}
	
	if(parse_command(str, ({}), "[around] [at] [by] [in] [a] [the] 'stool' / 'bar' [around] [at] [by] [in] [a] [the] [bar]"))
	{
		TP->catch_msg("You sit down on one of the stools at the bar.\n");
		say(QCTNAME(TP) + " sits down on a stool at the bar.\n");
		TP->add_prop(BSIT, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting at the bar");
		return 1;
	}
	
	else
	{
		TP->catch_msg("Where would you like to sit?  By the window, the "
		+ "bar, or around a table?\n");
		return 1;
	}
	return 1;
}

int 
action_stand(string str)
{
	if(!str || str == "up")
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
		say(QCTNAME(TP) + " stands up from the table as "+ HE(TP)
		+ " leaves.\n");
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		TP->remove_prop(TSIT);
	}
          
	if(TP->query_prop(FSIT))
	{
		TP->catch_msg("You stand up from your spot near the window before "
		+ "leaving.\n");
		say(QCTNAME(TP) + " stands up from " + HIS(TP) + " spot at the "
		+ "window as " + HE(TP) +" leaves.\n");
		TP->remove_prop(LIVE_S_EXTRA_SHORT);            
		TP->remove_prop(FSIT);
	}
        
	if(TP->query_prop(BSIT))
	{
		TP->catch_msg("You stand up from the counter before leaving.\n");        
		say(QCTNAME(TP) + " stands up from the counter as " + HE(TP)
		+ " leaves.\n");
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		TP->remove_prop(BSIT);
	}
}
