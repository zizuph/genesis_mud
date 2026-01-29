/*
 * /d/Genesis/guilds/merc/room/inn, by Morrigan, 11/2001
 *
 * Adapted from code by Nick
 */

#include "../merc.h"
#include "room.h"

inherit  "/std/room";
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

int test;          /* to indicate that a test is going on, no money given. */
object waitress ;      /* waitress that serves in the inn. */

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
    /* Commenting this out. Taryn has left. (Gorboth)
  if (!waitress)
    {
      waitress = clone_object(MNPC + "taryn");
      waitress->move_living("xxx", TO);
    }
    */
}


int exit_tent()
{
    write(TENT_EXIT);
}

/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
void
create_room()
{
    config_default_trade();
    set_short("A small tent");
    set_long(INSIDE_TENT_DESC+
	"The smell of food fills this tent, which is obviously an inn "+
	"of some sort. Facing the entrance of the tent is a bar, upon "+
	"which sits a menu. A handful of chairs sit around a single "+
	"table.\n");
    add_item("bar", "A wooden bar with a small menu on it.\n");
    add_item("menu", "@@read");
    add_item("chairs",
        "The chairs sit around the lone table.\n"); 
    add_item("table", "The table looks fairly new. Judging from the "+
	"fact that there is only one table, it would seem most people "+
	"do not linger here.\n");
    add_cmd_item("menu", "read", "@@read");

    
    add_exit(MROOM + "center", "northeast", "@@exit_tent", 1, 0);
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
    add_action("test", "test");
}

/*
 * Function name: read
 * Description:   Read the menu
 * Arguments:     str - hopefully the menu
 */
string
read(string str)
{
    return ""+
          "   Light ale                  12 cc\n" +
          "   Red wine	                 72 cc\n" +
          "   Piece of bread             25 cc\n" +
          "   Dried fruit                80 cc\n" +
          "   Meat and Potato Rations   210 cc\n\n" +
          "Try 'buy ale with gold' if you wanna specify what to\n" +
          "pay with, or 'test buy ale' to see what would happen\n" +
          "if you typed 'buy ale'. 'buy 10 ale' would get you\n" +
          "ten beers from the bar, but it takes a little while to\n" +
          "give them all to you. You can only order a maximum of 10\n"+
        "items at a time.\n";
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
    
    NF("The waitress isn't here to answer your call.\n");
    if (!waitress || !P(waitress, TO))
      return 0;
    
    NF("buy what?\n");
    if (!str)
      return 0;
    
    /* Has the player defined how payment will be done and what change to get
back? */  
    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
      {
        /* Well, maybe player has defined how payment will be done atleast?*/
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
        case "ale":
        case "ales":
        case "light ale":
        case "light ales":
          name = "ale";
          price = num * 12;
          break;
        case "wine":
        case "wines":
        case "red wine":
        case "red wines":
          name = "wine";
          price = num * 72;
          break;
        case "bread":
        case "piece":
	case "piece of bread":
          name = "bread";
          price = num * 25;
          break;
        case "fruit":
        case "fruits":
        case "dried fruit":
        case "dried fruits":
          name = "fruit";
          price = num * 80;
          break;
        case "meat":
        case "potato":
        case "rations":
        case "potatoes":
        case "meats":
	case "ration":
          name = "rations";
          price = num * 210;    
          break;
        default:
          NF("I don't understand what you want to buy.\n");
          return 0;
      }
    if (num > 10)
      {
          NF("You can order only 10 items at a time!\n");
          return 0;
      }
    
    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
    
    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
      write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
    write(waitress->query_The_name(TP)+" gets to work.\n");
    
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
          file = MOBJ + name;
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
                            ob->catch_msg("You get some " + 
				drink->plural_short() +
                                          ".\n");
                            say(QCTNAME(ob) + " buys some " + 
				drink->plural_short() +
                                ".\n", ob);
                        }
                      else 
                        {
                            ob->catch_msg("You get " + drink->short() + ".\n");
                            say(QCTNAME(ob) + " buys " + drink->short() +".\n",
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
