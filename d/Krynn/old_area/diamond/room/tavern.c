/* 
   Diamond.
   tavern.c
   -----  

   Coded ........: May 1997
   By ...........: Kentari

   Latest update : May 1997
   By ...........: Kentari
  
*/

#include "../local.h"
#include <macros.h>
#include <money.h>

inherit IN_BASE;
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

/*
 * Prototypes
 */
int move_item(mixed arg);
                
void
create_dim_room()
{
    config_default_trade();
    set_short("The Golden Keg Tavern");
    set_long("This is the Golden Keg Tavern, quite possibly the " +
	    "greatest tavern ever to exist. A burning hearth is set " +
	    "within the northwest wall, what seems to be some type of " +
	    "music producing box is set into the south wall, and " +
	    "filled tables adorn the room, Your attention is drawn " +
	    "though to the feature of the tavern, the glorious bar " +
	    "that occupies the entire eastern half of the room. With " +
	    "stools resembling kegs of gold, you see one way the " +
	    "tavern got its name. Behind the polished bar there are " +
	    "numerous drinks backed by shiny mirrors. You still can't " +
	    "get over how BIG and well-stocked this bar is. There is " +
	    "a bar menu that lists what is offered and a sign hangs by " +
	    "the entrance.\n");

    AI(({"box","music box","gnomish box","music"}),
	    "This mysterious contraption seems to produce music and " +
	    "project it out of a funnel-like opening. Your first " +
	    "guess would be that is was a gnomish innovation, except " +
	    "for the fact that it actually works. It also is securely " +
	    "set into the wall to prevent theft.\n");
    AI(({"hearth","burning hearth","fire","northwest wall"}),
	    "This cheerfully burning fire is set within a well kept " +
	    "fireplace and gives warmth to the room.\n");
    AI(({"tables","filled tables","table","people"}),
	    "These polished wood tables are filled with patrons " +
	    "around the clock as they come from all over the world " +
	    "to sample the fineries offered by the Golden Keg.\n");
    AI(({"feature","bar","glorious bar","eastern half","polished bar"}),
	    "This bustling bar runs along two of the walls and hosts " +
	    "the most wonderful drinks imaginable. Every thirsty " +
	    "person's wishes can come true......for the right price.\n");
    AI(({"stools","keg stools","stool"}),
	    "These stools are made to look like golden kegs, with a " +
	    "plush golden cushion on top for comfort at the bar.\n");
    AI(({"drinks","numerous drinks","bar stock"}),
	    "Held in many intriguing bottles and containers are " +
	    "the plethora of drinks brought from all over to the " +
	    "Golden Keg. Read the menu for a list of what is offered./n");
    AI(({"mirrors","shiny mirrors","back of bar"}),
	    "Clean, clear mirrors line the walls behind the displayed " +
	    "drinks, giving the impression of even more than the " +
	    "amazing amount there already is. It also looks pretty classy.\n");
    AI(({"sign","entrance sign"}),
	    "Framed and kept clean, you should have no problem " +
	    "reading it.\n");

    AI(({"menu","bar menu","list"}),
	    "This easy to ready bar menu lists what is " +
	    "offered to patrons of the Golden Keg Tavern.\n");   

   set_tell_time(180);
   add_tell("The soft music relaxes you and makes you think of past " +
	    "comrades and adventures.\n");
   add_tell("As the tune of the music switches to something a bit more " +
	    "upbeat, you feel yourself tapping your foot in time " +
	    "with the rhythm.\n");
   add_tell("The music turns to a merry drinking song, lifting your " +
	    "spirits as you feel inclined to buy a drink and join in.\n");
   add_tell("As a song ends, a sound of static bound sheets being " +
	    "constantly separated emanates from the box, and a bartender " +
	    "hustles over and fiddles with it before the music continues.\n");
   add_tell("Suddenly from the music box you hear 'Zub nub weej fud " +
	    "Freddy is the Devil' and see a giggling kender scurry away " +
	    "from the bartender who fixes it muttering '..darn kender " +
	    "playing things backwards..'\n");

   add_exit(DIROOM + "ne1", "southwest", 0);
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
 * Description:   Initialize the pub actions
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
 * Arguments:     str - the menu or the sign
 */
int
do_read(string str)
{
	if ((str=="sign")||(str=="entrance sign"))
         {
	   write("The sign is a general disclaimer, reading:\n\n" +
		 "   We are not responsible for monitoring our patrons' " +
		 "level of intoxication. If you feel too inebriated we " +
		 "suggest you visit the bathroom of Diamond City. Enjoy " +
		 "our wares and thank you for your business.\n" +
		 "                 -The Golden Keg Management\n\n");
	   say(QCTNAME(TP)+ " reads the sign by the entrance.\n");
           return 1;
         } else
	if ((str=="menu")||(str=="list")||(str=="bar menu"))
	  {
	   write("\nWhat we currently have to offer at the Golden " +
		 "Keg Tavern:\n\n" +
	  "   Hot Coffee and Tea	Free in the waiting rooms downstairs\n" + 
	  "   Cup of Milk                           12 cc\n" +
	  "   Dab of Honey                         162 cc\n" +
	  "   Glass of Brandy                       18 cc\n" +
	  "   Imported Silvanesti Wine             144 cc\n" +
	  "   Slice of Thorbardin Cheese            18 cc\n" +
	  "   Kendermore Potato Surprise            60 cc\n" +
	  "   Stew of the Ice Folk                  80 cc\n\n" +
	  "  If there is something you would like but cannot find\n" +
	  "  it on our menu, please go to the City PO and mail\n" +
	  "  'Tapmaster' and we'll mix it up as soon as possible for\n" +
	  "  your delight!\n\n");
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
	  file = "/d/Krynn/wayreth/tower/obj/" + name;
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


