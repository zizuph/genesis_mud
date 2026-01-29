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
      barkeeper = clone_object(FNPC + "innkeeper1");
      barkeeper->move_living("xxx", TO);
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
   set_short("The Jetties Inn");
   set_long("@@long_descr");
   
   add_item("shadows","The Inn's common room seems to be " +
      "blanketed in shadows, good if you want to be " +
      "unnoticed. \n");
   add_item(({"lamp","oil lamp"}),"A half-filled oil lamp, " +
      "swinging slightly, causing shadows to dance across " +
      "the room. \n");
   add_item(({"adventurers","characters"}),"You can't make out " +
      "many details " +
      "about this group of six, except that they are well " +
      "armed and eye you suspiciously. The two facing you are " +
      "a barbarian couple, probably from the nearby deserts of " +
      "Khur, or the arid plains of Nordmaar. \n");
   add_item(({"bar","short bar"}),"A short, ale stained bar. " +
      "On it sits a menu. \n");
   add_item(({"wooden table","table","tables"}),"These " +
      "battered wooden tables are currently occupied.\n");
   add_item("stairway","A sagging, wooden stairway, that " +
      "leads to the bedrooms on the next level. \n");
   add_item("door","The door leads out of the Inn.\n");
   add_item(({"sign","menu"}),"Has words on it. How about " +
      "reading it? \n");
   add_cmd_item("menu", "read", "@@read");
   add_cmd_item("sign", "read", "@@read_sign");
   
   add_exit(FROOM + "street27","out","@@out",0);
   add_exit(FROOM + "upper_inn01","up","@@up",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "You enter the common room of the Jetties " +
   "Inn in the town of Flotsam. Shadows sway against the " +
   "walls as an oil lamp swings to a gust of wind that blows " +
   "through the door at your entrance. The few tables here " +
   "are at present occupied by shady looking characters, " +
   "or adventurers who don't want to draw attention to " +
   "themselves. On a short bar at the side of the room " +
   "sits a menu. A sign hangs above it. A stairway leads " +
   "up into the Inn's rooms.\n";
}


int
out()
{
   write("You open the door and step into the streets...\n");
   return 0;
}

int
up()
{
   write("You climb the sagging stairway... \n");
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
   add_action("rent","rent");
}

int
rent(string str)
{
   NF("Rent what?\n");
   if (str == "room")
      {
      if (!present("gold coin",TP))
         {
         write("The innkeeper says: I only take gold for my rooms.\n");
         return 1;
       }
      if (!MONEY_MOVE(1,"gold",TP,0))
         {
         write("You pay 1 gold coin for a room.\n");
         this_player()->set_temp_start_location(FROOM + "upper_inn01");
         return 1;
       }
      return 0;
   }
   return 0;
}


int
read_sign(string str)
{
   write("   To start at this Inn the next time \n" +
      "   you log in, you may rent a room for \n" +
      "   one gold piece. \n" +
      "   Take note that the Innkeeper only \n" +
      "   accepts gold coinage. \n");
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
      " \n" +
      "   Seaweed salad               30 cc\n" +
      "   Warm soup                   80 cc\n" +
      "   Seafood platter            210 cc\n" +
      "\n" +
      "NOTE: The Jetties cook will not prepare \n" +
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
      case "soup":
      case "soups":
      case "warm":
      case "warm soup":
      name = "soup";
      price = num * 80;
      break;
      case "salad":
      case "salads":
      case "seaweed":
      case "seaweed salad":
      name = "weed";
      price = num * 30;
      break;
      case "platter":
      case "platters":
      case "seafood":
      case "seafood platter":
      name = "platter";
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
       cheater_log(this_player(), this_object(), "buy 0 units");
   
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
      file = "/d/Ansalon/balifor/flotsam/obj/food/" + name;
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

