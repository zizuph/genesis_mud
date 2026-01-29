/* Inn in guild, coded by Nick */

/* Revision History:
 * /Rastlin, 950215, You can only by soup and drinks if you don't have
 *                   any teeth.
 * /Teth, 960329, Added a bard.
 *
 * /Tibbit, 980312, fixed a typo 'excellant' to 'excellent'
 */

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "../local.h"

inherit ROOM_BASE
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */
#define VDIR "/d/Krynn/solamn/vkeep/"
#define MNSTR "/d/Krynn/solamn/vkeep/mnstrs/"

string
query_to_jail()
{
    return "east";
}


/*
 * Prototypes
 */
int move_item(mixed arg);

void
reset_palan_room()
{

}
                
/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
void
create_palan_room()
{
    config_default_trade();
    set_short("The Palanthian Honey-Bee");
    set_long("You find yourself in the midst of a wonderful array of " +
	"scents of baking goods. There is a display case with some "+
	"tasty looking pies and pastries in it. You see a menu posted "+
	"against the wall with a bronze plaque below it.\n");
    add_item("menu", "It has a lot of readable words on it.\n");
    add_item( ({"plaque", "bronze plaque"}), "It looks readable.\n");
    add_item("goods", "There are delicious baked goods all over the "+
	"place. The menu displays which ones are ready to purchase.\n");
    add_item( ({"pies", "pie", "pastries", "pastry"}), "The pies and "+
	"pastries look delicious. The menu shows which ones are ready "+
        "to be purchased.\n");
    add_item( ({"display case", "case", "display"}), "The case holds "+
	"pies and pastries. The menu shows which ones are ready for "+
	"sale.\n");
    
    add_cmd_item("menu", "read", "@@read");
    add_cmd_item( ({"plaque", "bronze plaque"}), "read", "@@plaque");
    add_item("sign", "It looks important.\n");
    add_exit(ROOM + "street15","east",0,1);

    reset_room();
    set_alarm(1.0,0.0,"reset_room");
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
 * Function name: plaque
 * Description:   Read the plaque
 * Arguments:     str - hopefully the plaque
 */
int
plaque(string str)
{
    write("The secrets of our baking are owed to a number of gnomish "+
	"oven-makers, several kender ingredient testers, the Wizards "+
	"of High Sorcery for their dispelling some of the enchantments "+
	"introduced by some of the less careful kender who like to drop "+
	"enchanted flour in the pots, Teth the wizard who developed "+
	"some excellent cooking methods to bring out the flavour in "+
	"our wares, and Karath because he threatened us with several "+
	"strange health-codes unless we honored him.\n");
    return 1;
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
	  "This is what we have to offer at the Palanthian Honey-Bee :\n\n" +
	  "   Yummy sugar cookies               25 cc each\n" +
	  "   Tasty chocolate brownies          50 cc each\n" +
	  "   Huge chocolate-covered donuts    150 cc each\n" +
	  "   Our famous ginger-bread men      250 cc each\n\n" +
          "** Reminder! Our wares are unique and special **\n" +
          "** Please eat them one at a time or the taste **\n" +
          "** will mix and seem strange and unpleasant!! **\n" +
	  "");
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

    NF("buy what?\n");
    if (!str)
        return 0;

    /* Has the player defined how payment will be done */
    /* and what change to get back? */  
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
    case "cookie":
    case "cookies":
    case "sugar cookie":
    case "sugar cookies":
	name = "cookie";
	price = num * 25;
	break;
    case "brownie":
    case "brownies":
    case "chocolate brownie":
    case "chocolate brownies":
	name = "brownie";
	price = num * 50;
	break;
    default:
    case "donut":
    case "donuts":
    case "chocolate donut":
    case "chocolate donuts":
    case "huge chocolate donut":
    case "huge chocolate donuts":
    case "chocolate-covered donut":
    case "chocolate-covered donuts":
    case "huge chocolate donuts":
    case "huge chocolate-covered donuts":
	name = "donut";
	price = num * 150;
	break;
    case "man":
    case "men":
    case "ginger-bread man":
    case "ginger-bread men":
    case "famous ginger-bread man":
    case "famous ginger-bread men":
    case "ginger bread man":
    case "ginger bread men":
    case "famous ginger bread man":
    case "famous ginger bread men":
	name = "gbread";
	price = num * 250;
	break;
      NF("I don't understand what you want to buy.\n");
      return 0;
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
	  file = OBJ + name;
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
      set_alarm(1.0,0.0,"move_item", ({name, num, ob}));
    return 1;
}
