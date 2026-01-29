/*
 * Goblin village shop
 * TAPAKAH, 09/2005
 */
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Khalakhor/sys/defs.h"

#include "../../daenbraigh.h"
#include "../../faction.h"
#include "../../village/village.h"

inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/shop";
inherit DAENBRAIGH_BASE;

object shopkeeper;
string storeroom = V_ROOM + "storeroom";
int check_allowed();

void
create_khalakhor_room()
{
  ::create_khalakhor_room();
  set_short(VILLAGE_NAME + " shop");
  set_long("The shop is a dirty, spacy building with numerous shelves. "     +
	   "It is built from clay and mortar. A small sign hangs on a wall.\n"
	   );

  add_item(({"small sign", "sign"}),
	   "You could probably read it.\n");
  add_item(({"floor", "ground"}),
	   "The floor of the shop hasn't met a broom for a long while.\n");
  add_item(({"walls", "wall"}),
	   "The walls of the shop are made of wooden logs.\n");
  add_item(({"shelves"}),"@@exa_shelves");

  config_default_trade();
  set_money_give_max(1000);
  set_store_room(storeroom);
  add_prop(ROOM_I_INSIDE,1);
  add_exit(storeroom,"west",&check_allowed());
  add_exit("we_2","south");
  reset_room();
}
/*
 * Function name: check_allowed
 * Description  : VBFC'd exit blocking routine to allow only
 *                wizards to enter the store room.
 * Arguments    : n/a
 * Returns      : 0 - Player may pass.                                         
 *                1 - Player can't pass.
 */
int
check_allowed()
{
  /* Let wizards through. */
  if (TP->query_wiz_level())
    return 0;
  /* Let the shopkeeper through. */
  if (TP == shopkeeper)
    return 0;
  /* Block anyone else. */
  write("You can't find your way into the storeroom\n");
  return 1;
}
/*
 * Function name: reset_room
 * Description  : Resets global variables in the room,
 *                such as resetting the shopkeeper if he's been                
 *                killed.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
reset_room()
{
  ::reset_room();
  if (!shopkeeper) {
    shopkeeper = clone_object(V_SHPKPR);
    shopkeeper->equip_me();
    shopkeeper->move(TO);
    shopkeeper->set_shop(TO);
    shopkeeper->set_store_room(query_store_room());
    return;
  }
  else if (!present(shopkeeper)) {
    if (shopkeeper->query_attack())
      return;
    else {
      tell_room(environment(shopkeeper), QCTNAME(shopkeeper) +
		" slaps his forehead and runs away.\n");
      shopkeeper->move_living("M", TO);
      if (shopkeeper->query_prop(LIVE_O_LAST_ROOM) == 
	  find_object(query_store_room()))
	tell_room(TO, QCTNAME(shopkeeper) + " appears from " +
		  "behind shelves and boxes.\n");
      else
	tell_room(TO, QCTNAME(shopkeeper) + " rushes in from " +
		  "the street outside.\n");
    }
  }
}
/*
 * Function name: exa_shelves
 * Description  : VBFC'd description for the shelves, so 
 *                players will see the storage room contents
 *                listed on them.
 * Arguments    : n/a
 * Returns      : A string describing store inventory.
 */
string
exa_shelves()
{
  object *inv;
  int capacity;

  seteuid(getuid());
  if (!find_object(storeroom))
    (storeroom)->load_me();

  capacity = sizeof(inv);
  
  inv = all_inventory(find_object(storeroom));
  if (!capacity)                                                          
    return "The shelves and racks are all bare!\n";
  if (capacity < 5)
    return "The shelves and racks are sparsely laden with " +
      COMPOSITE_DEAD(inv) + ".\n";
  if (capacity < 15)
    return "The shelves and racks are well-stocked with " +
      COMPOSITE_DEAD(inv) + ".\n";
  return "The shelves and racks are sagging under the load of " +
    COMPOSITE_DEAD(inv) + ".\n";
}

void
init()
{

  ::init();
  init_shop();
}

int
shop_hook_filter_inventory(object ob)
{
  if (living(ob))
    return 0;
  return 1;
}
/*
 * Function name: do_sell (MASK)
 * Description  : Called when the player tries to sell something.
 *                Used here to prevent transactions if the keeper
 *                has been killed.
 * Arguments    : str - What the player tried to sell.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
int
do_sell(string str)
{
  if (shopkeeper && present(shopkeeper)) {
    if (shopkeeper->query_this_faction(FACTION_DAENBRAIGH,TP) < FCT_VALUE_TOLERABLE) {
      shopkeeper->command("say you don't look like one I want to deal with.");
      return 1;
    }
    return ::do_sell(str);
  }
  write("There's no one here to buy anything from you!\n");
  return 1;
}
/*
 * Function name: do_value (MASK)
 * Description  : Called when the player tries to value something.
 *                Used here to prevent transactions if the keeper
 *                has been killed.
 * Arguments    : str - What the player tried to value.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
int
do_value(string str)
{
  if (shopkeeper && present(shopkeeper)) {
    if (shopkeeper->query_this_faction(FACTION_DAENBRAIGH,TP) < FCT_VALUE_TOLERABLE) {
      shopkeeper->command("say you don't look like one I want to deal with.");
      return 1;
    }
    return ::do_value(str);
  }
  write("There's no one here to evaluate anything for you!\n");
  return 1;
}
/*
 * Function name: do_show (MASK)
 * Description  : Called when the player tries to show something.
 *                Used here to prevent transactions if the keeper
 *                has been killed.
 * Arguments    : str - What the player tried to show.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
int
do_show(string str)
{
  if (shopkeeper && present(shopkeeper)) {
    if (shopkeeper->query_this_faction(FACTION_DAENBRAIGH,TP) < FCT_VALUE_TOLERABLE) {
      shopkeeper->command("say you don't look like one I want to deal with.");
      return 1;
    }
    return ::do_show(str);
  }
  write("There's no one here to present anything to you!\n");
  return 1;
}
/*
 * Function name: do_buy (MASK)
 * Description  : Called when the player tries to buy something.
 *                Used here to prevent transactions if the keeper
 *                has been killed.
 * Arguments    : str - What the player tried to buy.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
int
do_buy(string str)
{
  if (shopkeeper && present(shopkeeper)) {
    if (shopkeeper->query_this_faction(FACTION_DAENBRAIGH,TP) < FCT_VALUE_TOLERABLE) {
      shopkeeper->command("say you don't look like one I want to deal with.");
      return 1;
    }
    return ::do_buy(str);
  }
  write("There's no one here to buy anything from you!\n");
  return 1;
}

int *
query_local_coords()
{
  return ({-6,-1});
}
