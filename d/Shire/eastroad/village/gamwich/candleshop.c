
/* candleshop.c
 * Coded originally by Dunstable
 * Adaptations made 19 Feburary 1995 by Farlong
 * for the village of Gamwich
 */

inherit "/d/Shire/room";
inherit "/lib/trade";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define NUM           sizeof(MONEY_TYPES)
#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})
#define GONDORFIREWOOD "/d/Gondor/common/guild/obj/firewood"
#define GONDORCAMPFIRE "/d/Gondor/common/guild/obj/firewood"

/* Prototype */
void reset_room();

static object torchman;

void
create_room()
{
  config_default_trade();
  set_short("A candlemaker's shoppe");
  set_long(
    "This is the shoppe of the Candlemaker of Gamwich, run by "+
    "a Mr. Gamgee, to be precise.  In the front of the shoppe, "+
    "near to the door is a counter.   Behind the counter, several "+
    "large steaming casks are visible, as well as a loom in the "+
    "back.  A heap of firewood is stacked in the back, behind the "+
    "casks, and the exit is out.  A small sign is attached to the "+
    "counter.\n");

  add_item(({"counter","sign"}), "The counter is but "+
  "a slab of wood across some old wine casks, and the small sign "+
  "hanging from it, merely states that the shoppe is open for business.\n");

  add_item(({"cask","casks","large casks","large steaming casks"}),
  "These casks must contain the boiling wax needed to make candles, or "+
  "the pitch necessary for torches.\n");

  add_item(({"loom"}),"The loom near the back of the shoppe must be "+
  "used for making cloth wicks or wrappings for the torches.\n");

  add_item(({"heap","firewood","heap of firewood"}),
  "The heap of firewood is very large, and the wood looks nicely aged, "+
  "not in the least bit green- it would burn nicely.\n");

  add_item(PRICELIST_ID, "@@pricelist_desc");

  add_prop(ROOM_I_INSIDE,1);

    add_exit(GAMWICH_DIR+"square_sw","east");
    add_exit(GAMWICH_DIR+"sw_path_1","south");
 
  reset_room();
}

string
pricelist_desc()
{
  return "\nCandles:\n\n"+
    "1. 'A very small candle'........   10 cc\n"+
    "2. 'An ordinary candle'...........   30 cc\n"+
    "3. 'A large candle' ...................   55 cc\n"+
    "4. 'A giant pillar candle'.......... 85 cc\n"+
    "\nTorches:\n\n"+
    "5. 'An ordinary torch' ..............  35 cc\n"+
    "6. 'A gigantic torch' ................  105 cc\n"+
    "\nCooking accessories:\n\n"+
    "7. 'A bit of firewood' ..............  45 cc\n"+
    "8. 'A great campfire'...................60 cc\n"+
    "9. 'A cooking kit'...........................95 cc\n\n\n";
}

void
reset_room()
{
  if (!torchman)
    torchman = clone_object(ER_DIR + "npc/torchman");
  if (!present(torchman))
    torchman->move(this_object());
}

void
init()
{
  ::init();
  add_action("do_read", "read", 0);
  add_action("do_buy","buy",0);
  add_action("do_buy","order",0);
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
  if (!torchman || !present(torchman))
  {
    notify_fail("There is no-one here to buy anything from.\n"+
                "The proprietor has been killed!\n");
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
    case "small candle":
    case "very small candle":
    case "1":
   order = clone_object("/std/torch");
   order->set_value(random(5));
   order->set_strength(1);
   order->set_time(150);
   order->add_prop(OBJ_I_WEIGHT, 100);
   order->add_prop(OBJ_I_VOLUME, 50);
   order->add_name("candle");
   order->set_short("very small candle");
   order->set_pshort("very small candles");
   order->set_long("This candle will provide some light when lit.\n");
   price = 10;
   break;

   case "ordinary candle":
   case "2":
   order = clone_object("/std/torch");
   order->set_value(random(5) + 20);
   order->set_strength(1);
   order->set_time(600);
   order->add_prop(OBJ_I_WEIGHT, 100);
   order->add_prop(OBJ_I_VOLUME, 50);
   order->add_name("candle");
   order->set_short("ordinary candle");
   order->set_pshort("ordinary candles");
   order->set_long("This candle will provide good light when lit.\n");
   price = 30;
   break;

   case "large candle":
   case "3":
   order = clone_object("/std/torch");
   order->set_value(random(5) + 40);
   order->set_strength(1);
   order->set_time(1200);
   order->add_prop(OBJ_I_WEIGHT, 100);
   order->add_prop(OBJ_I_VOLUME, 50);
   order->add_name("candle");
   order->set_short("large candle");
   order->set_pshort("large candles");
   order->set_long("This candle will provide powerful light when lit.\n");
   price = 55;
   break;

   case "candle":
   case "giant pillar candle":
   case "pillar candle":
   case "4":
   order = clone_object("/std/torch");
   order->set_value(random(5) + 70);
   order->set_strength(1);
   order->set_time(6000);
   order->add_prop(OBJ_I_WEIGHT, 100);
   order->add_prop(OBJ_I_VOLUME, 50);
   order->add_name("candle");
   order->set_short("giant candle");
   order->set_pshort("giant pillar candles");
   order->set_long("This candle will provide long, powerful light when lit.\n");
   price = 85;
   break;

   case "ordinary torch":
   case "5":
   order = clone_object("/std/torch");
   order->set_value(random(5) + 20);
   order->set_strength(1);
   order->set_time(600);
   order->add_prop(OBJ_I_WEIGHT, 100);
   order->add_prop(OBJ_I_VOLUME, 50);
   order->add_name("ordinary torch");
   order->set_short("ordinary torch");
   order->set_pshort("ordinary torches");
   order->set_long("This ordinary torch will light the darkness.\n");
   price = 35;
   break;

   case "torch":
   case "gigantic torch":
   case "6":
   order = clone_object("/std/torch");
   order->set_value(random(5) + 20);
   order->set_strength(1 + random(2));
   order->set_time(15000);
   order->add_prop(OBJ_I_WEIGHT, 100);
   order->add_prop(OBJ_I_VOLUME, 50);
   order->add_name("gigantic torch");
   order->set_short("gigantic torch");
   order->set_pshort("gigantic torches");
   order->set_long("This gigantic torch will overpower the darkness.\n");
   price = 105;
   break;

   case "firewood":
   case "bit of firewood":
   case "7":
   order = clone_object(GONDORFIREWOOD);
   order->set_burn_time(50);
   price = 45;
   break;

   case "campfire":
   case "gigantic campfire":
   case "8":
   order = clone_object(GONDORCAMPFIRE);
   order->set_burn_time(375);
   price = 360;
   break;


   case "kit":
   case "cooking kit":
   case "9":
   order = clone_object("/std/torch");
   order->set_value(random(5) + 20);
   order->set_strength(1 + random(2));
   order->set_time(15000);
   order->add_prop(OBJ_I_WEIGHT, 100);
   order->add_prop(OBJ_I_VOLUME, 50);
   order->add_name("gigantic torch");
   order->set_short("gigantic torch");
   order->set_pshort("gigantic torches");
   order->set_long("This gigantic torch will overpower the darkness.\n");
   price = 495;
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
    say(QCTNAME(this_player())+" and " + QCTNAME(torchman)+" exchange "+
      "some coins.\n");
  }
  else say(QCTNAME(this_player())+" gives "+QCTNAME(torchman)+" some "+
    "money.\n");
  write("The proprietor hands you "+order->short()+".\n");
  say(QCTNAME(torchman)+" hands "+QCTNAME(this_player())+" "+
    order->short()+".\n"); 
  if (order->move(this_player())) {
    write("You drop the " + order->short() + " on the floor.\n");
    say(QCTNAME(this_player())+" drops a " + order->short()+" on the "+
      "floor.\n");
    order->move(this_object());
  }
  return 1;
}
