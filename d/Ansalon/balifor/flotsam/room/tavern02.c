/* Inn in solace, coded by Nick */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

inherit FLOTSAM_IN;
inherit "/lib/trade";
inherit "/d/Ansalon/common/cheater";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

int test; /* to indicate that a test is going on, no money given. */
object barkeeper; /* object tika; */
object drac1;
object drac2;
object gob;
object merc;

/*
* Prototypes
*/
int move_item(mixed arg);

/*
* Function name: reset_room
* Description:   Set up the objects at reset
*/
void
reset_flotsam_room()
{
   if (!barkeeper)
      {
      barkeeper = clone_object(FNPC + "barkeeper2");
      barkeeper->arm_me();
      barkeeper->move_living("xxx", TO);
   }
   if(!objectp(drac1))
      {
      drac1 = clone_object(KNPC + "sivak");
      drac1->move(TO);
   }
   if(!objectp(drac2))
      {
      drac2 = clone_object(KNPC + "baaz");
      drac2->move(TO);
   }
   if(!objectp(gob))
      {
      gob = clone_object(KNPC + "goblin");
      gob->move(TO);
   }
   if(!objectp(merc))
      {
      merc = clone_object(KNPC + "mercenary");
      merc->move(TO);
   }
}


/*
* Function name: create_room
* Description:   Set up default trade and cofigure it if wanted.
   */
void
create_flotsam_room()
{
   config_default_trade();
   set_short("The Tanked Troll");
   set_long("@@long_descr");
   
   add_item("furniture","Furniture that has been used many " +
      "times in, as well as been the victim of, savage brawls... " +
      "brawls that seem to be quite common in this lawless " +
      "town. \n");
   add_item("bar","A sturdy wooden bar. A menu sits at the end of it. \n");
   add_item("menu","A menu. Read it. \n");
   add_cmd_item("menu", "read", "@@read");
   
   
   add_exit(FROOM + "street41","west","@@out",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "This is the tavern of the Tanked Troll. If it " +
   "seemed disreputable from the outside, it certainly " +
   "loses none of its charm on the inside. This rowdy " +
   "place is roughly furnished in hastily mended furniture. " +
   "It is crowded, dark, and smells of stale beer, a good " +
   "example of just how bad a tavern can be. You can just " +
   "make out a bar at the back of the room. \n";
}

int
out()
{
   write("You step out of the Tanked Troll...\n");
   return 0;
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
      "\n" +
      "   Small beer                 12 cc\n" +
      "   Imported brew              24 cc\n" +
      "   Some really sweet wine     72 cc\n" +
      "   Dragon Breath             200 cc\n" +
      "\n" + "\n");
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
   string name, str1, str2, str3, teststr;
   int *arr, price, num;
   
   NF("The barkeeper isn't here to answer your call.\n");
   if (!barkeeper || !P(barkeeper, TO))
      return 0;

   
   NF("Buy what?\n");
   if (!str)
   {
       return 0;
   }

   teststr = explode(str, " ")[0];
   if(explode(str, " ")[0] == "0")
   {
       return 0;
   }
   
    if (check_cheater(TP, barkeeper))
        return 1;
   
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
      case "beer":
      case "beers":
      case "small":
      case "small beer":
      name = "beer";
      price = num * 12;
      break;
      case "brew":
      case "brews":
      case "imported":
      case "imported brew":
      name = "beer1";
      price = num * 25;
      break;
      case "wine":
      case "wines":
      case "sweet":
      case "sweet wine":
      name = "wine";
      price = num * 72;
      break;
      case "breath":
      case "breaths":
      case "dragon":
      case "Dragon Breath":
      name = "d_breath";
      price = num * 200;
      break;
      default:
      NF("I don't understand what you want to buy.\n");
      return 0;
   }
   if (num > 10)
      {
      NF("The barkeeper cannot count higher than 10! \n");
      return 0;
   }
   if (num < 1)
       cheater_log(this_player(), this_object(), "buy 0 units");
   
   if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
      
   write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
   if (text(exclude_array(arr, 0, NUM - 1)))
      write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
   write("The barkeeper gets to work.\n");
   
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
      file = "/d/Ansalon/balifor/flotsam/obj/drink/" + name;
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

