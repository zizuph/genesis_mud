/*
  The shop of the Rangers of Gondor.
  - Modified to use Olorin's standard-Gondor-shop, July 1994.
  - Modified by Randor 1992
  - From the Hobbiton Shop, 1991, by Elessar.
*/

inherit "/d/Gondor/common/lib/shop";
inherit "/d/Gondor/common/lib/friend_or_foe";

#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"
#include "/d/Gondor/common/guild/lib/shop_items.h"
         /* Where are the items stored? */
#define STORE_ROOM "/d/Gondor/common/guild/gondor/store"

string *standard_equip;

void  set_standard_equip(string *str);

void
create_shop()
{
    set_store_room(STORE_ROOM);
    set_short("The Rangers Equipment Store");
    set_long(BSN(
      "You are in the Rangers Equipment Store. "+
      "There are lots of strange items lying around, probably brought "+
      "here from distant lands. There is a poster on the wall, and " +
      "the exit from the store leads back south."));
    set_shop_name("The Rangers Equipment Store");
    set_keeper_file(RANGER_DIR+"npc/fredegar");
    set_no_sell_prop(({GONDOR_M_RANGERS_NO_SELL,
			 GONDOR_M_ROHIRRIM_NO_SELL,
			 GONDOR_M_TIRITH_NO_SELL}));
    set_hated_race(({"goblin"}));
    set_favoured_race(({"human","elf"}));
    add_item("poster","It has readable words on it.\n");
    add_item(({"door"}), BSN(
        "The door is probably leading into the storeroom of the "+
        "shop. The door is standing open, but the shop keeper " +
        "probably would not be amused if you tried to go there. "));
    add_exit(RANGER_DIR+"wcorr", "south", 0,0);
    set_standard_equip(GONDOR_EQUIP);
}

string
exa_poster()
{
  return "\nWelcome to the Rangers Equipment Store!\n" +
         "You can try these instructions: \n" +
         "    buy sword for gold and get copper back\n" +
         "    buy sword for gold coins\n" +
         "    sell sword for copper coins\n" +
         "    sell all  - will let you sell all items except for\n" +
         "                items you wield or wear.\n" +
         "    sell all! - will let you sell ALL items you have, well\n" +
         "                at least the droppable, and no coins.\n" +
         "    sell sword, sell second sword, sell sword 2, sell two swords\n" +
         "                also works. You might want to change the verb to\n" +
         "                'value' or 'buy' too. Beware, you will never buy\n"+
         "                more than one item at a time. So if you really\n" +
         "                want those three expensive swords, you have to \n" +
         "                repeat yourself three times.\n" +
      "    If you want a list of the special equipment available, do:\n"+
      "     'list equipment'.\n"+
         "    If you want a list of all swords available in the store, the\n" +
         "    correct syntax is: list swords\n" +
         "                'list weapons', 'list armours' also works.\n\n";
}

void
set_standard_equip(mixed x)
{
    if (stringp(x))
        standard_equip = ({ x });
    else if (pointerp(x))
        standard_equip = x;
    else
        standard_equip = GONDOR_EQUIP;
}

int
not_welcome()
{
    NF("The shopkeeper says: Forget it! I do not trade with the enemy!\n");
    return 0;
}

int
ranger_blocked()
{
    NF("The shopkeeper says: I am sorry, but you are not "+
       "allowed to trade here.\n"+
       "The shopkeeper says: The Council of Rangers informed "+
       "me that such is your\n"+
       "      punishment for breaking the rules.\n");
    return 0;
}

int
query_buy_price_special(object ob)
{
    int seed;

    sscanf(OB_NUM(ob), "%d", seed);
    return 2 * ob->query_prop(OBJ_I_VALUE) * (query_money_greed_buy() +
        15 - this_player()->query_skill(SS_TRADING) / 4 +
        random(15, seed)) / 100;
}

object *
clone_and_buy_it(string str1, string str2, string str3)
{
  int price, i, j, k, n,
      num = sizeof(query_money_types()),
      *value_arr = allocate(2 * num),
      *arr, error, err;
  object ob;
  mixed tmp;
    string *s_arr,
           *adjs;

  seteuid(getuid());

    if (!strlen(str1))
        return 0;

    s_arr = explode(str1, " ");
    if (sizeof(s_arr) != 1)
        str1 = s_arr[sizeof(s_arr) - 1];
    s_arr -= ({ str1 });
    while (n < sizeof(standard_equip) && !objectp(ob))
    {
        if (standard_equip[n]->id(str1))
        {
            adjs = standard_equip[n]->query_adjs();
            if (!sizeof(s_arr) || (sizeof(s_arr) == sizeof(adjs & s_arr)))
                ob = clone_object(standard_equip[n]);
        }
        n++;
    }
  if (!objectp(ob))
    return 0;

  price = query_buy_price_special(ob);
  
  if (err = ob->move(this_player()))
  {
      shop_hook_buy_cant_carry(ob, err);
      ob->remove_object();
      return 0;
  }
  
  if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
    {
      shop_hook_buy_cant_pay(ob, arr);
      ob->remove_object();
      return 0;
    }
  
  if (error = arr[sizeof(arr) - 1])
    {
      if (error < -1)
        {
	  /* Couldn't take the money from player, the coins were stuck */
	  shop_hook_buy_magic_money(ob);
	  ob->remove_object();
        }
      /* We don't want the money so no move error to us, if there was one
	 it was because the player couldn't hold all coins, and if so the
	 drop text is already written, but the deal is still on :) */
    }
  
  for (k = 0; k < 2 * num; k++)
    value_arr[k] += arr[k];
  
  if (objectp(ob))
    shop_hook_buy_pay_money(
      text(arr[0 .. num - 1]), text(arr[num .. 2 * num - 1]));
  
  return ({ ob });
}

int
do_buy(string args)
{
    int     res;
    object *item;
    string  str,
            str2,
            str3;
  
    if (!check_keeper())
        return 0;

    if (query_friend_or_foe(TP)<0)
        return not_welcome();
    else if (TP->query_skill(PUNISHMENT)==NOTRADE
	  || TP->query_skill(PUNISHMENT)==NOACCESS)
	return ranger_blocked();
    else if (!args || args == "")
    {
        NF("The shopkeeper says: Buy what?\n");
        return 0;
    }
    if (sscanf(args,"%s for %s and get %s", str, str2, str3) != 3)
    {
        str3 = "";
	if (sscanf(args,"%s for %s", str, str2) != 2)
        {
	    str2 = "";
	    str = args;
        }
    }
    if (res = ::do_buy(args))
        return res;
    else
    {
	item = clone_and_buy_it(str,str2,str3);
	if (sizeof(item))
            return shop_hook_bought_items(item);
        else
            return 0;
    }
    return 0;
}

int
do_value(string args)
{
  if (check_keeper()) {
    if (query_friend_or_foe(TP)<0)
      return not_welcome();
    else
      if (TP->query_skill(PUNISHMENT)==NOTRADE
          || TP->query_skill(PUNISHMENT)==NOACCESS)
        return ranger_blocked();
    else
      return ::do_value(args);
    }
  return 0;
}

int
do_sell(string args)
{
  if (check_keeper()) {
    if (query_friend_or_foe(TP)<0)
      return not_welcome();
    else
      if (TP->query_skill(PUNISHMENT)==NOTRADE
        || TP->query_skill(PUNISHMENT)==NOACCESS)
      return ranger_blocked();
    else
      return ::do_sell(args);
    }
  return 0;
}

int
do_list(string args)
{
  string list_txt;
  int n;
  if (check_keeper()) {
    if (query_friend_or_foe(TP)<0)
      return not_welcome();
    else
      if (TP->query_skill(PUNISHMENT)==NOTRADE
          || TP->query_skill(PUNISHMENT)==NOACCESS)
        return ranger_blocked();
      else
	{
	  if (args != "equipment" && args)
	    return ::do_list(args);
	  else if (!args || args == "")
    {
	    ::do_list(args);
        write(" --- Standard equipment available by 'list equipment'.\n");
        return 1;
    }
       write(" Standard Ranger equipment in stock: ----------------------\n");
	  while (n < sizeof(standard_equip))
	    {
	      call_other(standard_equip[n], "load_me");
	      shop_hook_list_object(find_object(standard_equip[n]),
			standard_equip[n]->query_prop(OBJ_I_VALUE));
	      n++;
	    }
	  write(" ----------------------------------------------------------\n");
	  return 1;
	}
  }
  return 0;
}

mixed
shop_hook_filter_sell(object x)
{
  return 0;
}

void
shop_hook_stolen_item(object pl, object ob)
{
  keeper->command("eyebrow");
  keeper->command("say Where did you get this "+ob->short()+"?");
  if (ob->query_prop(GONDOR_M_RANGERS_NO_SELL) && !pl->query_company())
    {
      keeper->command("say This is official Ranger equipment.");
      keeper->command("say You are not supposed to be carrying this,");
      keeper->command("say you must have stolen it .... or even....!");
      keeper->command("say Get out! Out of my sight!");
    }
  else if (ob->query_prop(GONDOR_M_ROHIRRIM_NO_SELL))
    {
      keeper->command("say This was crafted by our allies, the Rohirrim!");
      keeper->command("say You must have stolen it....or even worse!");
      keeper->command("say Get out, before I call the guards on you!");
    }
  else if (ob->query_prop(GONDOR_M_TIRITH_NO_SELL))
    {
      keeper->command("say This is official Gondorian equipment!");
      keeper->command("say You are not supposed to be carrying this,");
      keeper->command("say you must have stolen it...or even worse!");
      keeper->command("say Leave! Or I call the guards!");
    }
}

