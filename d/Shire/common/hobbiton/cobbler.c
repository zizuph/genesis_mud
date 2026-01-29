inherit "/d/Shire/room";
inherit "/lib/trade";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Shire/common/defs.h"

#define NUM           sizeof(MONEY_TYPES)
#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})

/* Prototype */
void reset_room();

static object rory;
void
create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
  config_default_trade();

  set_short("The local cobbler");
  set_long("The smell of leather oil permeates this small shop. It is crowded with "+
   "shoe lasts, bottles of different kinds of cleaning and conditioning agents, "+
   "a few worktables and stools and a counter behind which "+
   "the cobbler usually stands. A pricelist is on the wall.\n");

   add_item(({"bottle","bottles","agents"}),
   "There must be leather oil in some of these bottles, but "+
   "the others are obscure to you.\n");
   add_item(({"worktable","worktables","table","stool","stools"}),
   "The worktables and even the stools are covered with tools and "+
   "what must be works in progress. This store is a mess, it seems "+
   "impossible for anything to actually get done in it.\n");
   add_item(({"counter"}),"The counter separates the entry-way from "+
   "the work area.\n");
   add_item("wall","It keeps the roof up.\n");
   add_item("roof","It keeps the rain out.\n");
  add_item(PRICELIST_ID, "@@pricelist_desc");

  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_NO_ATTACK, 1);
  add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);

    add_exit("/d/Genesis/start/hobbit/v/bw_road5","north",0,1);
  reset_room();
}


string
pricelist_desc()
{
   return "\n\nSandals:\n\n"+
   "     For hobbits:          140 cc\n"+
   "     For gnomes:           140 cc\n"+
   "     For dwarves:          140 cc\n"+
   "     For goblins:          140 cc\n"+
   "     For elves:            140 cc\n"+
   "     For humans:           140 cc\n"+
   "\n\n\n\n\n"+
   "Note: Hobbits are size 1, gnomes 3, goblins 19, dwarves 21, elves 29 and humans 37.\n"+
   "Please order accordingly.\n"+
   "Rory the Cobbler of Hobbiton.\n";
}

void
reset_room()
{
  if (!rory)
   rory = clone_object("/d/Shire/common/hobbiton/npc/cobbler");
  if (!present(rory))
    rory->move(this_object());
}

void
init()
{
  ::init();
   add_action("do_read","read",0);
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
  if (!rory || !present(rory))
  {
    notify_fail("There is no-one here to buy anything from.\n"+
                "The shopkeeper has been killed!\n");
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
    case "hobbit sandals":
    case "sandals":
    case "1":
       order = clone_object("/d/Shire/common/hobbiton/obj/hobsandals");
      price = 140;
      break;

    case "gnome":
    case "gnome sandals":
    case "3":
       order = clone_object("/d/Shire/common/hobbiton/obj/gnosandals");
      price = 140;
      break;

    case "dwarf":
    case "dwarf sandals":
    case "21":
      order = clone_object("/d/Shire/common/hobbiton/obj/dwasandals");

      price = 140;
      break;

    case "goblin":
    case "goblin sandals":
    case "19":
       order = clone_object("/d/Shire/common/hobbiton/obj/gobsandals");
      price = 175;
      break;

    case "elf":
    case "elf sandals":
    case "29":
       order = clone_object("/d/Shire/common/hobbiton/obj/elfsandals");
      price = 140;
      break;

    case "human":
    case "human sandals":
    case "37":
        order = clone_object("/d/Shire/common/hobbiton/obj/humsandals");
      price = 140;
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
    say(QCTNAME(this_player())+" and " + QCTNAME(rory)+" exchange "+
      "some coins.\n");
  }
  else say(QCTNAME(this_player())+" gives "+QCTNAME(rory)+" some "+
    "money.\n");
  write("The shopkeeper hands you "+order->short()+".\n");
  say(QCTNAME(rory)+" hands "+QCTNAME(this_player())+" "+
    order->short()+".\n");
  if (order->move(this_player())) {
    write("You drop the " + order->short() + " on the floor.\n");
    say(QCTNAME(this_player())+" drops a " + order->short()+" on the "+
      "floor.\n");
    order->move(this_object());
  }
  return 1;
}
