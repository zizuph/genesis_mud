inherit "/d/Rhovanion/lib/room.c";
inherit "/lib/shop";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "def.h"
#include "/d/Rhovanion/defs.h"

#define STORE_ROOM THIS_DIR+"store" /* Where the items are stored */
#define MAXLIST 30
#define NUM 4
#define MONEY_TYPE ({ "cc","sc","gc","pc" })

object keeper;

/*
 * Function name: create_room
 * Destription:Initialize this room
 * Returns:
 */

void
  create_room()
{
  config_default_trade();
  set_money_give_max(1000);
  set_store_room(STORE_ROOM);
  set_short("Thranduil's Store");
  set_long(BS(
	      "You are in Thranduil's Store. "+
	      "There are a lot of strange items laying around, "+
	      "Probably brought here from distant lands. There "+
	      "is a poster on the wall, and a locked door leads "+
	      "south. the exit from the shop is north.\n"));

  add_item("poster","It has readable words on it.\n");
  add_item(({"shopkeeper","keeper","grocer"}),
	   BS("The shopkeeper is a stern elf with a sorrowfull eyes, " +
	      "making it very hard to do dealings with him."));

  set_noshow_obvious(1);
  add_exit(THIS_DIR+"cave6","north",0,0);
  add_exit(STORE_ROOM,"south","@@wiz_check");

  add_prop(ROOM_I_INSIDE,1);
}

do_read(string str)
{
  NF("Read what?\n");
  if (str != "poster") return 0;
  write("Welcome to Thranduil's Store!\n" +
	"You can try these instructions: \n" +
	"    buy sword for gold and get copper back \n" +
       "    buy sword for gold coins \n" +
	"    sell sword for copper coins \n" +
	"    sell all  - will let you sell all items except for \n" +
	"		items you wield or wear. \n" +
	"    sell all! - will let you sell ALL itmes you have, well " +
	"                at least the droppable, and no coins. \n" +
	"    sell sword, sell second sword sell sword 2, sell two swords \n"+
	"   also works. You might want to change the verb to\n"+
	"                'value' or 'buy' too. Beware, you will never buy\n"+
	"                more than one item at a time. So if you really \n"+
	"                want those three expensive sword, you have to \n"+
	"		 repeat yourself three times.\n"+
	"   If you want a list of all swords available in the store. the \n"+
	"   correct syntax is: list swords\n" +
	"                'list weapons','list armours' also works.\n" +
	"");
  return 1;
}

int
do_buy(string args)
{
  call_other(STORE_ROOM, "load_me");
  if(!present("torch",find_object(STORE_ROOM)))
    clone_object(OBJ_DIR+"torch")->move(STORE_ROOM);

  return ::do_buy(args);
}

int
do_list(string str)
{
  call_other(STORE_ROOM, "load_me");
  if(!present("torch",find_object(STORE_ROOM)))
    clone_object(OBJ_DIR+"torch")->move(STORE_ROOM);

  return ::do_list(str);
}

/*
 * Function name:init
 * Description:Is called for each living that enters this room
 * Returns:
 */
void
  init()
{
  ::init();
    init_shop();
  }

int
  shop_hook_sell_no_match(string str)
{
  NF("The shopkeeper says: You don't have any "+str+".\n");
  return 0;
}

int
  shop_hook_sold_nothing()
{
  NF("The shopkeeper says: You didn't have much to sell.\n");
  return 0;
}

void
  shop_hook_sell_no_value(object ob)
{
  NF("The shopkeeper says: "+capitalize(LANG_THESHORT(ob))+" is worthless.\n");
}
void
  shop_hook_sell_no_sell(object ob, string str)
{
  if (stringp(str)) NF(str);
  else
    NF("The shopkeeper says: I don't buy such items.\n");
}

void
  shop_hook_sell_object_stuck(object ob, int err)
{
  NF("The shopkeeper says: It seems you are stuck with that.\n");
}

void
  shop_hook_sell_get_money(string str)
{
  write("The shopkeeper gives you " + str + ".\n");
}

void
  shop_hook_buy_no_match(string str)
{
  NF("The shopkeeper says: I have no " + str + " to sell.\n");
}

void
  shop_hook_cant_carry(object ob, int err)
{
  NF("You drop the " + ob->short() + " on the floor.\n" +
     "The shopkeeper says: You can't carry more, I'm afraid.\n");
}

void
  shop_hook_buy_magic_money(object ob)
{
  write("The shopkeeper says: You are carrying magic money my friend, "+
	"no deal!\n");
}

void
  shop_hook_buy_pay_money(string str, string change)
{
  write("You give " + str + " to shopkeeper.\n");
  if (change)
    write("He gives you " + change + " back.\n");
}

void
  shop_hook_value_not_interesting(object ob)
{
  NF("The shopkeeper says: That item doesn't interest me.\n");
}

void
  shop_hook_value_held(object ob, string text)
{
  write(BS("The shopkeeper says: I could offer " + text + " for your "
	   + ob->short() + ".\n"));
}

void
  shop_hook_value_store(object ob, string text)
{
  write(BS("The shopkeeper says: I value the " + ob->short() +
	   " to " + text + ".\n"));
}

void
  shop_hook_value_asking(string str)
{
  say(QCTNAME(TP) + " asks the shopkeeper about the value of the "+
      str + ".\n");
}

int
  shop_hook_value_no_match(string str)
{
  NF("The shopkeeper says: We hold no '" + str + "' in stock.\n");
}

void
  shop_hook_list_empty_store(string str)
{
  NF("The shopkeeper says: We are currently sold out.\n");
}

int
  shop_hook_list_no_match(string str)
{
  NF("The shopkeeper says: We have no '" + str + "' in stock.\n");
}

/* The idea for this routine is got from Padermud. --Randor
 */

mixed
  neat_text(int *arr)
{
  int i;
  string temp;
  if (sizeof(arr) < NUM) /* invalid array */
    return;
  temp = "";
  for (i = NUM - 1; i >= 0; i--)
    {
      if (arr[i] > 0)
	temp += sprintf("%2d %2s ", arr[i], MONEY_TYPE[i]);
      else
	temp += "      ";
    }
  return temp;
}

void
  shop_hook_list_object(object ob, int price)
{
  string str, mess;
  mess = neat_text(split_values(price));
  if (!mess)
    mess = "That item wouldn't cost you much.\n";
  write(BS(sprintf("%-35s %20s\n", capitalize(LANG_ASHORT(ob)), mess)));
}
