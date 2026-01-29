inherit "/d/Shire/room";
inherit "/lib/trade";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define NUM           sizeof(MONEY_TYPES)
#define PRICELIST_ID  ({"pricelist","list","prices", "sign"})
#define MIN_AWARE 13

/* Prototype */
void reset_room();

static object togo;

object pan;

void
create_room()
{
   config_default_trade();
   set_short("Stock Bakery");
   set_long("This is the famous Stock bakery, as you "+
      "can quickly detect from the delicious smell of yeast and cooking "+
      "bread and pastries that floats through the shop.  There is a counter "+
      "full of delectable treats, and a pricelist listing all "+
      "the treats that you can buy in here.\n");
   add_item("counter", "@@counter_desc");
   add_item(PRICELIST_ID, "@@pricelist_desc");
   
   add_prop(ROOM_I_INSIDE,1);
   add_prop("_obj_s_search_fun","do_search");
   add_exit("/d/Shire/eastroad/village/whit/whitlane1","out");
   
   reset_room();
}

string
counter_desc()
{
   string my_desc;
   
   if(pan)
      {
      my_desc = "The counter is tall and narrow at the top, only a few things "+
      "could be placed on it at once, and nothing is there now.\n";
   }
   
   if(!pan)
      {
      my_desc = "The counter is tall and narrow at the top, and piled high with "+
      "things.  You could search the counter to see if anything of value is there.\n";
   }
   
   return my_desc;
}



string
pricelist_desc()
{
   return "\nRolls:\n\n"+
   "1. 'Sourdough Roll ............   5 cc\n"+
   "2. 'Cheese Roll ...............   8 cc\n"+
   "3. 'Rye Roll ..........   10 cc\n"+
   "\nLoaves:\n\n"+
   "4. 'White Loaf' ............  35 cc\n"+
   "5. 'Wholemeal Loaf' ..............  20 cc\n"+
   "6. 'Multigrain Loaf' ..............  25 cc\n"+
   "\nTarts:\n\n"+
   "7. 'Cherry Tart ............  40 cc\n"+
   "8. 'Strawberry Tart' ...........  40 cc\n"+
   "9. 'Custard Tart'.......30 cc\n\n"+
   "\nPastries:\n\n"+
   "10. Hathorpe Pastry........50 cc\n\n\n";
}

void
reset_room()
{
   pan = 0;
   if (!togo)
      togo = clone_object("/d/Shire/eastroad/village/stock/npc/togo");
   togo->arm_me();
   if (!present(togo))
      togo->move(this_object());
}

void
init()
{
   ::init();
   add_action("do_read", "read", 0);
   add_action("do_buy","buy",0);
   add_action("do_buy","order",0);
}


string
do_search(object searcher, string str)
{
   int awareness;
   
   awareness = searcher->query_skill(SS_AWARENESS);
   if(awareness < MIN_AWARE + random (MIN_AWARE)) return 0;
   if(!str || (str!= "counter" && str != "counter top")) return 0;
   if(pan) return 0;
   seteuid(getuid(TO));
   pan = clone_object(MICH_DIR + "obj/pan");
   pan->move(searcher,1);
   say(QCTNAME(searcher)+ " finds something on the baker's counter.\n");
   return "You find a "+pan->short()+" on the counter.\n";
}


int
do_read(string str)
{
   if (!str)
      return 0;
   if (member_array(str, PRICELIST_ID) == -1)
      return 0;
   write(pricelist_desc());
   return 1;
}

int
do_buy(string str) 
{
   object order;
   string str1, str2, str3;
   int *arr, price, silent, i;
   
   if (!str)
      {
      notify_fail("Buy 'item' with 'type of money' and get 'type of money'.\n");
      return 0;
   }
   if (!togo || !present(togo))
      {
      notify_fail("The baker is not present... you will have to wait "+
            "until he returns.\n");
      return 0;
   }
   if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3) {
      str3 = "";
      if (sscanf(str, "%s with %s", str1, str2) != 2) {
         str2 = "";
         str1 = str;
       }
   }
   switch (str1)
   {
      case "sourdough":
      case "sourdough roll":
      case "1":
      order = clone_object("/std/food");
      order->set_name("roll");
      order->set_pname("rolls");
      order->set_short("sourdough roll");
      order->set_pshort("sourdough rolls");
      order->set_long("This is a fresh, hot sourdough roll.\n");
      order->set_amount(20);
      order->add_prop(OBJ_I_WEIGHT, 20);
      order->add_prop(OBJ_I_VOLUME, 20);
      add_prop(HEAP_S_UNIQUE_ID,"heaps of sourdough rolls");
      price = 5;
      break;
      
      case "cheese":
      case "cheese roll":
      case "2":
      order = clone_object("/std/food");
      order->set_name("roll");
      order->set_pname("rolls");
      order->set_short("cheese roll");
      order->set_pshort("cheese rolls");
      order->set_long("This roll has a tasty crust of melted cheese.\n");
      order->set_amount(30);
      order->add_prop(OBJ_I_WEIGHT, 30);
      order->add_prop(OBJ_I_VOLUME, 30);
      add_prop(HEAP_S_UNIQUE_ID,"heaps of cheese rolls");
      price = 8;
      break;
      
      case "rye":
      case "rye roll":
      case "3":
      order = clone_object("/std/food");
      order->set_name("roll");
      order->set_pname("rolls");
      order->set_short("rye roll");
      order->set_pshort("rye rolls");
      order->set_long("This dark brown roll is made of rye.\n");
      order->set_amount(40);
      order->add_prop(OBJ_I_WEIGHT, 40);
      order->add_prop(OBJ_I_VOLUME, 40);
      add_prop(HEAP_S_UNIQUE_ID,"heaps of rye rolls");
      price = 10;
      break;
      
      case "white":
      case "white loaf":
      case "4":
      order = clone_object("/std/food");
      order->set_name("loaf");
      order->set_pname("loaves");
      order->set_short("white loaf");
      order->set_pshort("white loaves");
      order->set_long("This loaf has been made with bleached flour.\n");
      order->set_amount(60);
      order->add_prop(OBJ_I_WEIGHT, 60);
      order->add_prop(OBJ_I_VOLUME, 60);
      add_prop(HEAP_S_UNIQUE_ID,"heaps of white loaves");
      price = 53;
      break;
      
      case "wholemeal":
      case "wholemeal loaf":
      case "5":
      order = clone_object("/std/food");
      order->set_name("loaf");
      order->set_pname("loaves");
      order->set_short("wholemeal loaf");
      order->set_pshort("wholemeal loaves");
      order->set_long("This loaf has been made from tasty "+
         "wholemeal flour.\n");
      order->set_amount(60);
      order->add_prop(OBJ_I_WEIGHT, 60);
      order->add_prop(OBJ_I_VOLUME, 60);
      add_prop(HEAP_S_UNIQUE_ID,"heaps of wholemeal loaves");
      price = 20;
      break;
      
      case "multigrain":
      case "multigrain loaf":
      case "6":
      order = clone_object("/std/food");
      order->set_name("loaf");
      order->set_pname("loaves");
      order->set_short("multigrain loaf");
      order->set_pshort("multigrain loaves");
      order->set_long("This loaf has grains of kibble in it.\n");
      order->set_amount(65);
      order->add_prop(OBJ_I_WEIGHT, 65);
      order->add_prop(OBJ_I_VOLUME, 65);
      add_prop(HEAP_S_UNIQUE_ID,"heaps of multigrain loaves");
      price = 25;
      break;
      
      case "cherry":
      case "cherry tart":
      case "7":
      order = clone_object("/std/food");
      order->set_name("tart");
      order->set_pname("tarts");
      order->set_short("cherry tart");
      order->set_pshort("cherry tarts");
      order->set_long("This delicious tart has whole cherries in it.\n");
      order->set_amount(40);
      order->add_prop(OBJ_I_WEIGHT, 40);
      order->add_prop(OBJ_I_VOLUME, 40);
      price = 40;
      break;
      
      case "strawberry":
      case "strawberry tart":
      case "8":
      order = clone_object("/std/food");
      order->set_name("tart");
      order->set_pname("tarts");
      order->set_short("strawberry tart");
      order->set_pshort("strawberry tarts");
      order->set_long("This tart has large imported strawberries in it.\n");
      order->set_amount(45);
      order->add_prop(OBJ_I_WEIGHT, 45);
      order->add_prop(OBJ_I_VOLUME, 45);
      price = 40;
      break;
      
      case "custard":
      case "custard tart":
      case "9":
      order = clone_object("/std/food");
      order->set_name("tart");
      order->set_pname("tarts");
      order->set_short("custard tart");
      order->set_pshort("custard tarts");
      order->set_long("This tart is made with thick, warm custard.\n");
      order->set_amount(45);
      order->add_prop(OBJ_I_WEIGHT, 45);
      order->add_prop(OBJ_I_VOLUME, 45);
      price = 30;
      break;
      
      default:
      notify_fail("Buy 'item' with 'type of money' and get "+
            "'type of money'.\n");
      return 0;
   }
   
   arr = pay(price, 0, str2, 0, 0, str3, 0);
   
   if (sizeof(arr) == 1) {
      if (arr[0] == 1) notify_fail("You have to give me more to choose from.\n");
      else if (arr[0] == 2) notify_fail("You don't carry that kind of money!\n");
      return 0;
   }
   
   write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
   if (text(exclude_array(arr, 0, NUM-1))) {
      write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
      say(QCTNAME(this_player())+" and " + QCTNAME(togo)+" exchange "+
         "some coins.\n");
   }
   else say(QCTNAME(this_player())+" gives "+QCTNAME(togo)+" some "+
         "money.\n");
   write("The baker hands you "+order->short()+".\n");
   say(QCTNAME(hathorpe)+" hands "+QCTNAME(this_player())+" "+
      order->short()+".\n"); 
   if (order->move(this_player())) {
      write("You place the " + order->short() + " on the counter.\n");
      say(QCTNAME(this_player())+" places a " + order->short()+" on the "+
         "counter.\n");
      order->move(this_object());
   }
   return 1;
}
