/*
* The code for the forsaken inn is basically the same as for the prancing 
* pony in Bree, /d/Shire/common/bree/inn.c
* The code for The Foaming Mug inn is taken from both of the above.
*/

inherit "/d/Shire/room";
inherit "/lib/trade";

#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#define NUM sizeof(MONEY_TYPES)
#define PRICELIST_ID ({"pricelist", "list", "menu", "prices"})
#define EXIT1 ER_DIR + "er12","out",0,1

void reset_room();

static object barman;

void
create_room()
{
   config_default_trade();
   set_short("The Foaming Mug");
   set_long(
      "This is The Foaming Mug inn, a large and cheerful inn in "+
      "the village of Waymeet.  It is a two story wooden inn, and "+
      "it is full of hobbits and travellers weary from their "+
      "travels along the Great East Road.  There are several long "+
      "wooden tables and chairs against the walls, and a well "+
      "stocked bar.  The windows are closed, and the room is "+
      "illuminated by a flickering fire, that casts long shadows "+
      "across the room, adding to its character.  Above the bar "+
      "is a menu.  There is a set of stairs leading up to a locked "+
      "door.\n");
   add_item("bar",
      "The bar is made from oak, and has been polished lovingly "
      +"over the years until it glows with a soft sheen.\n");
   add_item(({"chairs","tables"}),
      "The chairs and tables by the window are covered in stains "
      +"and puddles from spilt ale.  However, they are in good "
      +"condition, and are obviously looked after.\n");
   add_item("windows",
      "Little light comes in through the closed windows, that block "
      +"out the outside world.\n");
   add_item("fire", "Burning away in its fireplace, the fire provides a "
      +"ruddy glow for the room, as it crackles and hisses in the "
      +"corner.\n");
   add_item("stairs", "The flight of stairs leads up to the first story of "
      +"the inn.  There is a polished bannister to prevent people "
      +"from falling over the stairs after a long night at the bar.\n");
   add_item("door", "The door at the top of the stairs is locked from "
      +"the inside.\n");
   add_item(PRICELIST_ID, "@@pricelist_desc");
   
   add_prop(ROOM_I_INSIDE, 1);
   reset_room();
   
   add_exit(EXIT1);
}

string
pricelist_desc()
{
   return "Prices:\n\n"+
   "1.     'Ale'                                      25 cc\n"+
   "2.     'House Wine'                               55 cc\n"+
   "3.     'Whiskey'                                 100 cc\n"+
   "4.     'Elven Wine'                              150 cc\n"+
   "5.     'House Special'                           180 cc\n";
}

void
reset_room()
{
   if (!barman)
      barman = clone_object("/d/Shire/eastroad/npc/tarlas");
   if (!present(barman))
      barman->move(TO);
   /*if (!thief)
      {
      thief = clone_object(ER_DIR +"npc/thief");
      thief->arm_me();
      thief->move(TO);
   }
   if (!scoundrel)
      {
      scoundrel = clone_object(ER_DIR +"npc/bummer");
      scoundrel->arm_me();
      scoundrel->move(TO);
   }
   if (!noisy)
      {
      noisy = clone_object(ER_DIR +"npc/sad_man");
      noisy->arm_me();
      noisy->move(TO);
   }*/
}

void
init()
{
   ::init();
   add_action("do_read", "read", 0);
   add_action("do_buy", "buy", 0);
   add_action("do_buy", "order", 0);
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
   string str1,str2,str3;
   int*arr, price, silent, i;
   
   if (!str)
      {
      NF("Buy <item> with <money type> and get <type of money>.\n");
      return 0;
   }
   
   if (!barman || !present(barman))
      {
      NF("There is no-one here to sell you anything.\n"+
         "The innkeeper must be out.\n");
      return 0;
   }
   
   if (sscanf(str, "%s and get %s", str1, str2, str3) != 3)
      {
      str3 = "";
      if (sscanf(str, "%s with %s", str1, str2) != 2)
         {
         str2 = "";
         str1 = str;
       }
   }
   
   switch(str1)
   {
      case "ale":
      case "some ale":
      case "pint of ale":
      case "1":
      order = clone_object("/std/drink");
      order->set_name("ale");
      order->set_pname("ales");
      order->set_short("pint of ale");
      order->set_pshort("pints of ale");
      order->set_adj(({"pint", "mug"}));
      order->set_long("The drink that the inn is named "
         +"after, this is a large mug of foaming ale, "
         +"perfect after a long day on the road.\n");
      order->set_soft_amount(115);
      order->set_alco_amount(7);
      order->add_prop(OBJ_I_WEIGHT, 200);
      order->add_prop(OBJ_I_VOLUME, 220);
      price = 25;
      break;
      
      case "wine":
      case "house wine":
      case "glass of wine":
      case "glass of house wine":
      case "2":
      order = clone_object("/std/drink");
      order->set_name("wine");
      order->set_pname("wines");
      order->set_short("glass of wine");
      order->set_pshort("glasses of wine");
      order->set_adj("glass");
      order->set_long("This is a glass of house wine.  "
         +"It isn't particularly nice, but it is what "
         +"you paid for.\n");
      order->set_soft_amount(91);
      order->set_alco_amount(14);
      order->add_prop(OBJ_I_WEIGHT, 200);
      order->add_prop(OBJ_I_VOLUME, 200);
      price = 55;
      break;
      
      case "whiskey":
      case "whisky":
      case "3":
      order = clone_object("/std/drink");
      order->set_name("whiskey");
      order->set_pname("whiskies");
      order->set_short("glass of whiskey");
      order->set_pshort("glasses of whiskey");
      order->set_long("A tumbler of neat golden whiskey,.\n");
      order->set_soft_amount(50);
      order->set_alco_amount(30);
      order->add_prop(OBJ_I_WEIGHT, 100);
      order->add_prop(OBJ_I_VOLUME, 100);
      price = 100;
      break;
      
      case "elven wine":
      case "glass of elven wine":
      case "4":
      order = clone_object("/std/drink");
      order->set_name("elven");
      order->set_pname("elven");
      order->set_short("elven wine");
      order->set_pshort("elven wines");
      order->set_long("A glass of rare, elven wine from "
         +"beyond the Twin Towers.\n");
      order->set_soft_amount(70);
      order->set_alco_amount(30);
      order->add_prop(OBJ_I_WEIGHT, 120);
      order->add_prop(OBJ_I_VOLUME, 120);
      price = 150;
      break;
      
      case "house special":
      case "5":
      order = clone_object("/std/drink");
      order->set_name("special");
      order->set_pname("specials");
      order->set_short("glass of the house special");
      order->set_pshort("glasses of the house special");
      order->set_long("This is a potent mix of vodka and "
         +"some other type of alcohol, normally ordered "
         +"by thirsty dwarves.\n");
      order->set_soft_amount(150);
      order->set_alco_amount(33);
      order->add_prop(OBJ_I_WEIGHT, 300);
      order->add_prop(OBJ_I_VOLUME, 300);
      price = 180;
      break;
      
      default:
      NF("Buy <item> with <type of money> and get <type of money>.\n");
      return 0;
   }
   
   arr = pay(price, 0, str2, 0, 0, str3, 0);
   
   if (sizeof(arr) == 1)
      {
      if (sizeof(arr[0] == 1))
         NF("You must give me more to choose from.\n");
      else
         if (arr[0] == 2)
         NF("You don't have that kind of money!\n");
      return 0;
   }
   
   write("You pay "+text(exclude_array(arr, NUM, NUM*2-1))+".\n");
   if (text(exclude_array(arr, 0, NUM-1)))
      {
      write("You get "+text(exclude_array(arr, 0, NUM-1)) +".\n");
      say(QCTNAME(TP)+" and "+QCTNAME(barman)+" exchange some coins.\n");
   }
   else
      say(QCTNAME(TP)+" gives "+QCTNAME(barman)+" some money.\n");
   write("The innkeeper hands you "+order->short()+".\n");
   say(QCTNAME(barman)+" hands "+QCTNAME(TP)+" "+order->short()+".\n");
   if (order->move(TP))
      {
      write("You place the "+order->short()+" on the bar.\n");
      say(QCTNAME(TP)+" places a "+order->short()+" on the bar.\n");
      order->move(TO);
   }
   return 1;
}

