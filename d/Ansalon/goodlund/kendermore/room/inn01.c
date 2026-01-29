/* Taken from Inn in solace, coded by Nick */
/* Scorched Scorpion Inn in Kendermore */
/* Added OotS revelation - Arman 2017 */
/* Added IDB export brew - Vitwitch 2021 */

#include "/d/Ansalon/common/brewcraft/brewcraft.h"

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Krynn/guilds/OotS/defs.h"

inherit KENDERMORE_IN;
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
reset_kendermore_room()
{
   if (!barkeeper)
      {
      barkeeper = clone_object(KNPC + "innkeeper1");
      barkeeper->move_living("xxx", TO);
   }
}


/*
* Function name: create_room
* Description:   Set up default trade and cofigure it if wanted.
   */
void
create_kendermore_room()
{
    config_default_trade();
    set_short("The Scorched Scorpion Inn");
    set_long("@@long_descr");
   
    add_item(({"door", "doors"}), "There are two, a back door to the east " + 
        "and the front door leading out to the northwest.\n");
    add_item("back door", "You can head out the back door to " + 
        "the east.\n");
    add_item("front door", "You can head out the front door to the street.\n");
    add_item("bar", "A menu is nailed down to the bar, likely to keep " + 
        "it from being borrowed.\n");
    add_item(({"table", "tables"}), "Several tables are set against the " + 
        "walls to the south and west. They are all full though, and " + 
        "there's not a seat to be found.\n");
    add_item(({"ground", "floor"}), "If you dropped something, you'd " + 
        "better pick it up quickly!\n");
    add_item("kitchen", "There's an awful lot of loud crashing sounds " + 
        "coming from that direction. The cook must be enjoying himself.\n");
    add_item("menu",
          " \n" +
          "   Provisions: " +
          " \n" +
          "   A red ripe strawberry       30 cc\n" +
          "   A piece of mulberry pie     75 cc\n" +
          "   A bowl of rabbit gumbo     150 cc\n" +
          "   A mongoose stew            300 cc\n" +
          "\n" +
          "   Drinks: " +
          " \n" +
          "   Fresh berry juice           15 cc\n" +
          "   Mug of foamy ale            50 cc\n" +
          "   Goodlund red wine           80 cc\n" +
          "   Blackberry brandy          100 cc\n" +
          "\n" +
          "NOTE: The Scorched Scorpion cook will not prepare \n" +
          "more than ten items at once. \n");

    set_tell_time(100);
    add_tell("A kender gives off a high-pitched drunken giggle.\n");
    add_tell("You hear a kender voice shouting: Another ale Bobbin!\n");
    add_tell("A kender says loudly: Bring on the mongoose stew! I could " + 
        "eat a horse I'm so hungry!\n"); 
    add_tell("The door slams shut behind a kender entering the inn.\n");
    add_tell("A loud voice from the corner asks: Did I ever tell you about " + 
        "the time I visited Dargaard Keep?\n");

    add_cmd_item("menu", "read", "@@read");
    add_cmd_item("sign", "read", "@@read_sign");
   
    add_exit(KROOM + "street03", "out", 0);
    add_exit(KROOM + "inn02", "up", 0);
    add_invis_exit(KROOM + "street02", "east", 0);
   
    reset_kendermore_room();
}

int
branchala_revelation(object ob)
{
     ob->catch_msg("\n\nThe music and joyous merrymaking of the inn washes " +
             "over you, and you are suddenly blessed with a divine revelation " +
             "about the Bard King Branchala!\n\n\n");
     OOTS_ADD_REV(ob,"branchala","the aspect of branchala"); 

}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

/*
    if (interactive(ob))
        start_room_tells();
*/
    if (living(ob))
    {
       if(IS_OOTS(ob))
       {
          if(!OOTS_QUERY_REV(ob, "branchala"))
          {
            set_alarm(3.0, 0.0, &branchala_revelation(ob)); 
          }
       }
    }

}

string
long_descr()
{
    return "This inn seems to have been built in the middle of the " + 
           "road! Travellers come in through the front door and exit " + 
           "through the back door. Many stop to satiate their thirst " + 
           "or fill their bellies, much to the innkeeper's delight. " + 
           "Several tables are set up out of the way of the foot traffic. " + 
           "Most of them seem to be filled with laughing kender. A " + 
           "silver-haired kender stands behind the bar chatting with " + 
           "his patrons, and you can glimpse some activity in the kitchen " + 
           "behind the bar. A delicious aroma wafts out from there. " + 
           "There is a sign bolted to the wall, and a menu nailed down " + 
           "to the bar.\n";
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
    if (!present(barkeeper))
    {
        write("The innkeeper isn't here to rent you a room. He must " + 
            "have gotten a minor case of wanderlust.\n");
        return 1;
    }

    if (KMASTER->query_banished(this_player()->query_real_name()))
    {
        write("The innkeeper won't deal with the likes of you!\n");
        return 1;
    }

    if ((str == "room")&&(present(barkeeper)))
    {
        if (!present("gold coin",TP))
        {
            write("The innkeeper says: I only take gold for my rooms.\n");
            return 1;
        }
        if (!MONEY_MOVE(1,"gold",TP,0))
        {
            write("You pay 1 gold coin for a room.\n");
            this_player()->set_temp_start_location(KROOM + "inn02");
            return 1;
        }
        return 0;
    }
    return 0;
}


int
read_sign(string str)
{
    write("  To rent a room for the night, you\n " + 
          "  can pay one gold piece to Bobbin, the\n " + 
          "  innkeeper. Please note that he only\n " + 
          "  accepts gold coins for his rooms.\n"); 
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
          "   Provisions: " + 
          " \n" + 
          "   A red ripe strawberry       30 cc\n" +
          "   A piece of mulberry pie     75 cc\n" +
          "   A bowl of rabbit gumbo     150 cc\n" +
          "   A mongoose stew            300 cc\n" + 
          "\n" +
          "   Drinks: " + 
          " \n" + 
          "   Fresh berry juice           15 cc\n" +
          "   Iron Delving Brew           24 cc\n" +
          "     (" + BREWCRAFT_MENU + ")  \n"+
          "   Mug of foamy ale            50 cc\n" + 
          "   Goodlund red wine           80 cc\n" + 
          "   Blackberry brandy          100 cc\n" + 
          "\n" +  
          "NOTE: The Scorched Scorpion cook will not prepare \n" +
          "more than ten items at once. \n");
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
   
    NF("The Innkeeper must have gotten a severe case of wanderlust!\n");
    if (!barkeeper || !P(barkeeper, TO))
        return 0;

    if (KMASTER->query_banished(this_player()->query_real_name()))
    {
        notify_fail("The innkeeper won't deal with the likes of you!\n");
        return 0;
    }
   
    NF("buy what?\n");
    if (!str)
        return 0;
    if (check_cheater(TP, barkeeper))
        return 1;
   
/* Has the player defined how payment will be done and what change to 
 * get back?  
*/ 
    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
        {
         /* Well, maybe player has defined how payment will be done at 
          *least? 
         */
            str3 = "";
    if (sscanf(str, "%s with %s", str1, str2) != 2)
         {
             str2 = "";
             str1 = str;
         }
   }
   
   if (sscanf(str1, "%d %s", num, str1) != 2)
      num = 1;
   
   switch(lower_case(str1))
   {
      case "strawberry":
      case "strawberries":
      case "red strawberry":
      case "ripe strawberry":
      case "red strawberries":
      case "ripe strawberries":
      case "red ripe strawberry":
      case "red ripe strawberries":  
          name = "strawberry";
          price = num * 30;
          break;
      case "pie":
      case "pies":
      case "mulberry pie":
      case "mulberry pies":
      case "mulberry":
      case "piece":
          name = "mulberry";
          price = num * 75;
          break;
      case "gumbo":
      case "gumbos":
      case "rabbit":
      case "rabbit gumbo":
      case "bowl":
      case "bowls":
          name = "gumbo";
          price = num * 150;
          break;
      case "stew":
      case "stews":
      case "mongoose stew":
      case "mongoose":
      case "mongoose stews": 
          name = "mongoose";
          price = num * 300;
          break;
      case "juice":
      case "juices":
      case "berry juice":
      case "berry juices":
      case "berry":
          name = "juice";
          price = num * 15;
          break;
      case "brew":
      case "brews":
      case "iron delving brew":
      case "iron delving brews":
          name = "brewcraft_beermug";
          price = num * 24;
          break;
      case "ale":
      case "ales":
      case "mug":
      case "mugs":
          name = "ale";
          price = num * 50;
          break;
      case "wine":
      case "wines":
      case "red wine":
      case "red wines":    
      case "red":
          name = "wine";
          price = num * 80;
          break;
      case "brandy":
      case "brandies":
      case "blackberry brandy":
      case "blackberry brandies":
      case "blackberry":
          name = "brandy";
          price = num * 100;
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
   write("The Innkeeper gives your order to the cook, and returns shortly.\n");
   
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
      if ( name != "brewcraft_beermug" ) 
          file = "/d/Ansalon/goodlund/kendermore/obj/" + name;
      else
          file = "/d/Ansalon/estwilde/obj/" + name;
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

