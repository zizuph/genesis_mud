/* Crabshack in Palanthas 
 * coded by Arman, March 2021 */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

inherit NOBLE_ROOMBASE;
inherit "/lib/trade";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

int test; /* to indicate that a test is going on, no money given. */
object barkeeper; /* object bishon; */

int move_item(mixed arg);

void
reset_palan_room()
{
   if (!barkeeper)
      {
      barkeeper = clone_object(NOBLE + "living/bishon");
      barkeeper->move(TO, 1);
   }
}

void
create_palan_room()
{
   config_default_trade();
   set_short("Bishon's Crabbery");
   set_long("You stand within Palanthas' famed 'Bishon's Crabbery', the most " +
       "popular seafood restaurant along the Courrain Ocean coastline. " +
       "Clientele ranging from rugged sailors, well-to-do merchants, to " +
       "affluent nobles sit shoulder-to-shoulder along the simple " +
       "benches the delicious seafood is served on. A large menu hangs " +
       "upon the wall beside the door to the kitchen.\n");
   
   add_item( ({ "clientele", "sailors", "rugged sailors", "merchants", 
       "well-to-do merchants", "nobles", "affluent nobles", "benches",
       "simple wooden benches", "wooden benches" }),
       "Clientele of all sorts come to Bishon's Crabbery for the amazing " +
       "seafood meals, sitting shoulder-to-shoulder on simple wooden " +
       "benches where the food is speedily served.\n");

   add_item("door","There is a door that leads in to the kitchen here.\n");
   add_item(({"sign","menu"}),"Has words on it. How about " +
       "reading it? \n");
   add_cmd_item(({"door","kitchen"}), "enter", "Only staff may " +
       "enter the kitchen.\n");
   add_cmd_item("menu", "read", "@@read");
   
   EXIT(NOBLE + "ner6", "southeast", "@@out", 0);
   
   reset_palan_room();
}


int
out()
{
   write("You open the door and step into the streets...\n");
   return 0;
}

/*
* Function name: init
* Description:   Initalize the pub actions
*/
void
init()
{
   ::init(); 
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
      " \n" +
      "   Crab sticks                  5 cc each\n" +
      "   Shark fin soup              80 cc\n" +
      "   Black noodles              100 cc\n" +
      "   Fish platter               210 cc\n" +
      "\n" +
      "NOTE: The Crabbery's cook will not prepare \n" +
      "more " +
      "than ten items at once. \n");
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
   
   NF("The Innkeeper isn't here to answer your call.\n");
   if (!barkeeper || !P(barkeeper, TO))
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
   
   switch(str1)
   {
      case "sticks":
      case "stick":
      case "crab sticks":
      case "crab stick":
      name = "bishon_crabsticks";
      price = num * 5;
      break;
      case "soup":
      case "soups":
      case "fin soup":
      case "shark fin soup":
      name = "bishon_soup";
      price = num * 70;
      break;
      case "noodles":
      case "black noodles":
      name = "bishon_noodles";
      price = num * 100;
      break;
      case "platter":
      case "platters":
      case "fish":
      case "fish platter":
      name = "bishon_platter";
      price = num * 210;
      break;
      default:
      NF("I don't understand what you want to buy.\n");
      return 0;
   }
   if (num > 10)
      {
      NF("The cook screams from the kitchen: No more than 10 items! " +
         "Can you not read the sign? \n");
      return 0;
   }
   if (num < 1)
      {
      NF("You can't buy less than one item!\n");
      return 0;
   }
   
   if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
      
   write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
   if (text(exclude_array(arr, 0, NUM - 1)))
      write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
   write("The Innkeeper gets to work.\n");
   
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
      file = NOBLE + "obj/" + name;
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

