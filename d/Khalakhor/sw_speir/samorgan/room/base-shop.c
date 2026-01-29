/*
 * Base SaMorgan Shop file
 * Tapakah, 06/2021
 */

#pragma no_clone
#pragma strict_types

#include <files.h>
#include <macros.h>
#include <cmdparse.h>

#include "../defs.h"

inherit "/d/Khalakhor/lib/shop";
inherit "/d/Khalakhor/lib/smith";

inherit SM_ROOM_BASE;

int    is_buyer = SHOP_BUYS_ALL;
int    is_smith = 0;
string smell = 0;
string shop_keeper;
string store_direction = 0;

string query_shop_sign () { return ""; }
void   configure_shop () {}

void
create_khalakhor_room ()
{
  configure_shop();
  config_default_trade();
  set_money_give_max(1728);

  string shop_name = file_name(TO);
  string store_room = shop_name + "-store";
  shop_keeper = NPC + FILE_NAME(shop_name) + "-keeper";
  if (file_size(shop_keeper+".c") > 0) {
    set_shopkeep(shop_keeper, TO);
    if (is_smith)
      set_smith(shop_keeper);
  }
  else {
    shop_keeper = 0;
  }
  if (file_size(store_room+".c") > 0) 
    set_store_room(store_room);

  add_item(({"sign"}), query_shop_sign);
  add_item(({"shop", "room", "area"}), query_long);
  if (store_direction)
    add_exit(store_room, store_direction, wiz_check);
  
  mixed *exits = query_exit();
  if (sizeof(exits))
    foreach (string exit:
             ({"north", "west", "east", "south",
               "southeast", "southwest", "northeast", "northwest"})
             ) 
      add_item(exit,
               exit == exits[1]
               ? "The street is in that direction.\n"
               : exit == store_direction
               ? "The storeroom is in that direction.\n"
               : "There is a wall in that direction.\n");
  
  add_item(({"bell", "small bell", "brass bell"}),
           "It is a small brass bell.\n");
}

int
shop_hook_allow_buy (object ob)
{
  object shopkeeper = query_shopkeep();

  if (! objectp(shopkeeper))
    NF0("There is no one here to deal with. The shopkeeper is gone.");
  return 1;
}

int
shop_hook_allow_sell (object ob)
{
  object shopkeeper = query_shopkeep();

  if (! objectp(shopkeeper))
    NF0("There is no one here to deal with. The shopkeeper is gone.");

  int fail = 0;
  if (! is_buyer) {
    shopkeeper->command("say We only sell things. Please read the sign.");
    fail = 1;
  }
  else if (is_buyer == SHOP_BUYS_ARM && ! IS_ARMOUR_OBJECT(ob)) {
    shopkeeper->command("say We only buy armours. Please read the sign.");
    fail = 1;
  }
  else if (is_buyer == SHOP_BUYS_WEP && ! IS_WEAPON_OBJECT(ob)) {
    shopkeeper->command("say We only buy weapons. Please read the sign.");
    fail = 1;
  }
  if (fail) {
    shopkeeper->command("emote points at the sign.");
    NF0("");
  }
  return 1;
}

int
do_bell (string str)
{
  if(!(str == "bell" || (str == "small bell") || (str == "brass bell")))
    NF0("Ring bell maybe?\n");
  write("You pick up the small brass bell and ring it "+
        "softly.\n");
  say(QCTNAME(TP)+" picks up the small brass bell and "+
      "rings it.\n");
  
  if (query_shopkeep())
    shopkeeper->command("say May I help you?");
  return 1;
}

object
figure_object (string str)
{
  object *items;
  
  if (is_buyer == SHOP_BUYS_NONE)
    return 0;

  string verb = query_verb();
  notify_fail(capitalize(verb) + " what?\n");
  if (! str)
    return 0;

	if (!sizeof(items = FIND_STR_IN_OBJECT(str,TP)))
    return 0;
  if (sizeof(items) > 1)
    NF0("Please be more specific. Which one?");
  return items[0];
}

/* necessary evil */
void
SmithSpeak (string str)
{
  object shopkeeper = query_shopkeep();
  shopkeeper->command("say " + str);
}

int
check_weapon_armour (object item)
{
  
  int is_weapon = IS_WEAPON_OBJECT(item);
  int is_armour = IS_ARMOUR_OBJECT(item);

  object shopkeeper = query_shopkeep();
  if (! is_weapon && is_buyer == SHOP_BUYS_WEP) {
    shopkeeper->command("say I only work on weapons, apologies.");
    return 1;
  }
  else if (! is_armour && is_buyer == SHOP_BUYS_ARM) {
    shopkeeper->command("say I only work on armours, apologies.");
    return 1;
  }
  else if (! is_weapon && ! is_armour) {
    shopkeeper->command("say I can only work on weapons and armours.");
    return 1;
  }
  return 0;
}

int
do_fix (string str)
{
  object item = figure_object(str);
  if (! objectp(item))
    return 0;

  if (check_weapon_armour(item))
    return 1;

  return ::do_fix(str);
}

int
do_cost (string str)
{
  object item = figure_object(str);
  if (! objectp(item))
    return 0;

  if (check_weapon_armour(item))
    return 1;

  return ::do_cost(str);
}

void
init ()
{
  ::init();
  init_shop();
  if (is_smith)
    init_smith();
  add_action(do_bell, "ring");
}

void
hook_smelled(string str)
{
  if (!strlen(str) || parse_command(str, ({}), "[the] 'air'")) {
    write(smell);
    return;
  }   
}

void
reset_room ()
{
  ::reset_room();
  if (! query_shopkeep() && shop_keeper) {
    set_shopkeep(shop_keeper, TO);
    tell_room(TO, "The shopkeeper steps out from the storeroom.\n", 0);
  }  
}
