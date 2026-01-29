/* 
   Wayreth.
   inn.c
   -----  

   Coded ........: 96/12/06
   By ...........: Kentari

   Latest update : 97/03/13
   By ...........: Karath
   Reason........: Typo log fix
  
*/

#include "../local.h"
#include <macros.h>
#include <money.h>

inherit TOWERROOM;
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

/*
 * Prototypes
 */
int move_item(mixed arg);
                
/*
 * Function name: create_room
 * Description:   Set up default trade and configure it if wanted.
 */

void
create_tower_room()
{
    config_default_trade();
    set_short("Inn of Wayreth Tower");
    set_long("You find yourself in the inn of Wayreth Tower, a pleasant " +
            "place where you can buy wines and intoxicating herbal " +
	    "mixtures. From somewhere in the room you hear the " +
 	    "delicate music of a lyre, though you can't detect its " +
	    "source. A counter adorns the back of the room, with a " +
	    "small plaque floating behind it, and a menu resting upon it.\n");
    AI(({"lyre","music"}),
	    "You can't seem to locate any visible source of the music " +
	    "and assume that it is another mystical manifestation of " +
	    "the Tower of Wayreth.\n");
    AI(({"plaque","floating plaque"}),
	    "Though obviously magical, you should still be able to read " +
            "it.\n");
    AI("menu",
	    "Orderly and legible, this shows the wares of the " +
            "Inn. You are able to read the menu.\n");
   
   set_tell_time(180);
   add_tell("The gentle music of the lyre soothes your thoughts and " +
	    "eases the worries and stresses of life.\n");
   add_tell("As the tune of the lyre switches to something a bit more " +
	    "upbeat, you feel yourself tapping your foot in time " +
	    "with the rhythm.\n");
   add_tell("The music turns to a merry drinking song, rowdy for mages, " +
	    "and mellow compared to the typical tavern, and you " +
	    "feel inclined to buy a drink and join in.\n");
   add_tell("Suddenly a sour note, followed by a twang sounds, and the " +
	    "tune stops. What can only be the tuning of an instrument " +
	    "follows, and the song continues from where it left off.\n");

   add_exit(WTOWER + "lobby", "south", 0);
}

public void
enter_inv (object ob, object from)
{
	::enter_inv(ob,from);
        if (interactive(ob))
	    start_room_tells();
}

/*
 * Function name: init
 * Description:   Initalize the pub actions
 */
void
init()
{
    ::init(); /* Since it's a room this must be done. */
    add_action("do_read", "read");
    add_action("order", "buy");
    add_action("order", "order");
}  	     

/*
 * Function name: read
 * Description:   Enables players to read room items
 * Arguments:     str - the menu or the plaque
 */
int
do_read(string str)
{
	if ((str=="plaque")||(str=="magical plaque"))
         {
	   write("Etched into the plaque are these words: 'The Solemn " +
		"Scholar' - An inn created by the magic of Kentari.\n");
	   say(QCTNAME(TP)+ " reads the plaque.\n");
           return 1;
         } else
	if ((str=="menu")||(str=="list"))
	  {
	   write("This is what we have to offer at the Solemn Scholar:\n\n" +
	  "   Hot Coffee and Tea	Free in the waiting rooms downstairs\n" + 
	  "   Cup of Milk                           12 cc\n" +
	  "   Dab of Honey                         162 cc\n" +
	  "   Glass of Brandy                       18 cc\n" +
	  "   Imported Silvanesti Wine             144 cc\n" +
	  "   Slice of Thorbardin Cheese            18 cc\n" +
	  "   Kendermore Potato Surprise            60 cc\n" +
	  "   Stew of the Ice Folk                  80 cc\n");
	   say(QCTNAME(TP)+ " reads the menu.\n");
	   return 1;
	 }
	NF("Read what?\n");
	return 0;
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

    switch(str1)
    {
    case "milk":
    case "milks":
    case "cup":
    case "cups":
    case "cup of milk":
    case "cups of milk":
      name = "milk";
      price = num * 12;
      break;
    case "brandy":
    case "brandies":
    case "brandys":
    case "glasses":
    case "glasses of brandy":
    case "glass":
    case "glass of brandy":
      name = "brandy";
      price = num * 18;
      break;
    case "wine":
    case "wines":
    case "imported":
    case "Silvanesti wine":
    case "silvanesti wine":
    case "imported silvanesti wine":
    case "imported Silvanesti wine":
      name = "wine";
      price = num * 144;
      break;
    case "cheese":
    case "cheeses":
    case "slice":
    case "slices":
    case "Thorbardin cheese":
    case "thorbardin cheese":
    case "thorbardin cheeses":
      name = "cheese";
      price = num * 18;
      break;
    case "potato":
    case "potatoes":
    case "Kendermore potatoes":
    case "potato surprise":
    case "surprise":
    case "surprises":
    case "potato surprises":
    case "Kendermore potato":
    case "kendermore potato surprise":
      name = "potato";
      price = num * 60;
      break;
    case "honey":
    case "dab of honey":
    case "honey dab":
    case "dabs of honey":
    case "honeys":
	name = "honey";
	price = num * 162;
	break;
    case "ice folk stews":
    case "ice folk stew":
    case "stews of the ice folk":
    case "stews of the Ice Folk":
    case "stew":
    case "stews":
      name = "stew";
      price = num * 80;
      break;
    default:
      NF("Sorry, we don't sell that here.\n");
      return 0;
  }

    if (member_array(name, ({"fruit"})) &&
	present("cirath_broken_teeth",TP))
    {
        write("You are toothless, how do you plan to eat that?\n");
	return 1;
    }

    if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
    
    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
      write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    
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

    if (num <= 0)
      return 1;

    for (i = 0; i < 10; i++)
      {
	  num--;
	  file = TOBJ + name;
	  drink = clone_object(file);
	  
	  if (drink->move(ob))
	    {
		ob->catch_msg("You drop " + drink->short() +
			      " on the floor.\n");
		say(QCTNAME(ob) + " drops " + drink->short() +
		    " on the floor.\n", ob);
		drink->move(TO);
	  } else if (num == 0) {
	      if (arg[1] > 1)
		{
		    ob->catch_msg("You get some " + drink->plural_short() +
				  ".\n");
		    say(QCTNAME(ob) + " buys some " + drink->plural_short() +
			".\n", ob);
	      } else {
		  ob->catch_msg("You get " + drink->short() + ".\n");
		  say(QCTNAME(ob) + " buys " + drink->short() + ".\n",
		      ob);
	      }
	  }
	  
	  if (num < 1)
	    break;
      }
    
    if (num > 0)
      set_alarm(0.2,0.0,"move_item", ({name, num, ob}));
    return 1;
}


