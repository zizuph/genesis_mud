inherit "/d/Kalad/room_std";
inherit "/lib/trade";
#include "/d/Kalad/defs.h"
#define NUM sizeof(MONEY_TYPES)
#define CDIR "/d/Kalad/common/wild/pass/dwarf/obj/"
int test;
object jenn;
object stranger;
object gossiper;
int move_item(mixed arg);
/* by korat */
void
reset_room()
{
   if(!jenn)
      {
      jenn = clone_object(CPASS(dwarf/npc/inn_owner));
      jenn -> move_living("xxx",TO);
   }
   if(!gossiper)
      {
      gossiper = clone_object(CPASS(dwarf/npc/drunk_dwarf));
      gossiper -> move_living("xxx",TO);
      jenn -> team_join(gossiper);
   }
}
void
create_room()
{
   config_default_trade();
   INSIDE;
   set_short("The Golden Lump");
   set_long("You are within the 'Golden Lump'.\n"+
      "Here you can relax and have a nice meal and some to "+
      "drink with it. At least it is a nice way to forget the "+
      "turmoils of the life outside the door. In here the world "+
      "can become a distant horror of war and destruction, that "+
      "a drink or two can chase away for a short but welcome time. "+
      "The menu is on the wall.\n");
   add_item("menu", "It has a lot of readable words on it.\n");
   add_cmd_item("menu", "read", "@@read");
   add_exit(CPASS(dwarf/shop/m1),"east","@@leave_msg",-1,-1);
   reset_room();
}
void
init()
{
   ::init();
   add_action("order", "buy");
   add_action("order", "order");
}
int
read(string str)
{
   write("" +
      "   Dwarfish beer               24 copper\n"+
      "   Dwarf spirit               120 copper\n"+
      "   Fresh mushrooms             30 copper\n"+
      "   Juicy steak                 180 copper\n"+
      "   Roast chicken               150 copper\n"+
      "Try 'buy beer with gold' if you want to specify what to\n" +
      "pay with. You can also do 'buy 10 beer' to get yourself\n"+
      "ten beers from the bar, but it takes a little while to\n" +
      "give them all to you. You can't buy more than 10 at a time.\n");
   return 1;
}
int
order(string str)
{
   string name, str1, str2, str3;
   int *arr, price, num;
   
   NF("The innkeeper isn't here to answer your call.\n");
   if (!jenn || !present(jenn, TO))
      return 0;
   
   NF("Buy what?\n");
   if (!str)
      return 0;
   
   if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
      {
      str3 = "";
      if (sscanf(str, "%s with %s", str1, str2) != 2)
         {
         str2 = "";
         str1 = str;
       }
   }
   
   if (sscanf(str1, "%d %s", num, str1) != 2)
      num = 1;
   
   if (num > 10) num = 10;
   
   switch(str1)
   { 
      case "beer":
      case "beers":
      case "dwarfish beer":
      case "dwarfish beers":
      name = "inn_beer";
      price = num * 24;
      break;
      case "spirit":
      case "spirits":
      case "dwarf spirit":
      case "dwarf spirits":
      name = "inn_spirit";
      price = num * 120;
      break;
      case "mushroom":
      case "mushrooms":
      case "fresh mushroom":
      case "fresh mushrooms":
      name = "inn_mushroom";
      price = num * 30;
      break;
      case "steak":
      case "steaks":
      case "juicy steak":
      case "juicy steaks":
      name = "inn_steak";
      price = num * 180;
      break;
      case "chicken":
      case "chickens":
      case "roast chicken":
      case "roast chickens":
      name = "inn_chicken";
      price = num * 150;
      break;
      default:
      NF("The inn-keeper chuckles: We don't have that. Try our "+
      "excellent steak instead, or our local brewed spirit that "+
      "I promise will chase away any feel of hunger in you!.\n");
      return 0;
      break;
   }
   
   if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
      
   write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
   if (text(exclude_array(arr, 0, NUM-1)))
      write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
   write("The inn-keeper writes down your order and starts to work.\n");
   
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
      file = CDIR + name;
      drink = clone_object(file);
      
      if (!test && (drink->move(ob)))
         {
         ob->catch_msg("You drop the " + drink->short() +
            " on the floor.\n");
         say(QCTNAME(ob) + " drops a " + drink->short() +
            " on the floor.\n", ob);
         drink->move(TO);
        } else if (!test) {
         if (num == 0)
            {
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
        } else {
         say(QCTNAME(ob) + " seems to be estimating something.\n",
            ob);
         return 1;
        }
      if (num < 1)
         break;
   }
   
   if (num > 0)
      call_out("move_item", 1, ({name, num, ob}));
   return 1;
}
int
test(string str)
{
   int i;
   string str1;
   
   NF("Test what?\n");
   
   if (sscanf(str, "buy %s", str1)) {
      test = 1;
      write("This would be the result of a buy:\n");
      i = order(str1);
      test = 0;
      return i;
   }
}
leave_msg()
{
   TP->catch_msg("The sounds of drinking and merriment fade away.\n");
   return 0;
}
