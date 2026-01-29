inherit "/d/Kalad/room_std";
inherit "/lib/trade";
#include "/d/Kalad/defs.h"
#define CDIR "/d/Kalad/common/wild/pass/drow/obj/"
#define NUM sizeof(MONEY_TYPES)
int test;
object powner;
/* object drinker1...2...3 */
int move_item(mixed arg);
/* by Antharanos */
void
reset_room()
{
   if(!powner)
      {
      powner = clone_object(CPASS(drow/npc/pub_owner));
      powner -> arm_me();
      powner -> move_living("X",TO);
   }
}
void
create_room()
{
   config_default_trade();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("The gaudy drow drinking pit, Undraeth");
   set_long("You are within the stalagmite compound.\n"+
      "Despite the darkened stone from which this building was constructed, "+
      "the numerous magical lights known as faerie fire make this place of "+
      "food and drink practically gleam with light. At the far end of the "+
      "room is a counter of sorts, above which a menu can be seen hanging.\n");
   add_item(({"stalagmite compound","compound","building"}),
      "It is where you are, look around.\n");
   add_item(({"darkened stone","stone"}),
      "A rock the color of midnight, the entire building is constructed from "+
      "the material.\n");
   add_item(({"numerous magical lights","numerous lights","magical lights","lights","light","faerie fire","fire"}),
      "Enchantments that have been used to decorate this otherwise plain "+
      "room. Several of the enchanted fires depict drow, though the majority "+
      "have spiders as their subject matter.\n");
   add_item(({"counter"}),
      "Nothing more than a gleaming black stone slab, which blocks your access of the "+
      "opposite side of this place.\n");
   add_item("menu","Several glowing words have been written on it.\n");
   add_cmd_item("menu", "read", "@@read");
   add_exit(CPASS(drow/d21),"west","@@leave_msg",-1,-1);
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
      " Fungus beer......................24 copper\n"+
      " Dark purple wine.................100 copper\n"+
      " Moldy fungus.....................20 copper\n"+
      " Tender juicy rothe...............200 copper\n"+
      " Roasted lizard...................140 copper\n"+
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
   if(!powner || !present(powner, TO))
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
      case "fungus beer":
      case "fungus beers":
      name = "drow_beer";
      price = num * 24;
      break;
      case "wine":
      case "wines":
      case "dark purple wine":
      case "dark purple wines":
      case "dark wine":
      case "dark wines":
      case "purple wine":
      case "purple wines":
      name = "drow_wine";
      price = num * 100;
      break;
      case "fungus":
      case "fungi":
      case "moldy fungus":
      case "moldy fungi":
      name = "drow_fungus";
      price = num * 20;
      break;
      case "rothe":
      case "tender juicy rothe":
      case "tender rothe":
      case "juicy rothe":
      name = "drow_rothe";
      price = num * 200;
      break;
      case "lizard":
      case "lizards":
      case "roasted lizard":
      case "roasted lizards":
      name = "drow_lizard";
      price = num * 140;
      break;
      default:
      NF("I don't understand what you want to buy.\n");
      return 0;
   }
   
   if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
      
   write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
   if (text(exclude_array(arr, 0, NUM-1)))
      write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
   write("The innkeeper gets to work.\n");
   
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
      set_alarm(1.0,0.0,"move_item",({name,num,ob}));
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
   write("You leave the noise of the drinking pit behind.\n");
   say(QCTNAME(TP) + " leaves the noise of the drinking pit behind.\n");
   return 0;
}
