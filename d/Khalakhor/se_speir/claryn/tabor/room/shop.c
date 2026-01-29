/*
 * shop.c
 *
 * Local shop for the village of Tabor Sogh.
 *
 * Khail - March 31/97
 * Modified to inheirt new /d/Khalakhor/lib/shop
 * by Damaris 01/2001
 * added Deliveries /d/Genesis/delivery/
 * Damaris@Genesis 11/2005
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "room.h"

#include "/d/Genesis/delivery/delivery.h"

#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/shop";
inherit "/d/Genesis/delivery/office";

object shopkeeper;

int *
query_local_coords ()
{
  return ({2,5});
}

int *
query_global_coords ()
{
  return VILLAGE_COORDS;
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
check_allowed ()
{
  /* Let wizards through. */
  if (this_player()->query_wiz_level())
    return 0;
  /* Let the shopkeeper through. */
  if (this_player() == shopkeeper)
    return 0;
  /* Block anyone else. */
  write("That area is off limits.\n");
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
reset_room ()
{
	reset_office(); /* For delivery */
	::reset_room();
	if (!shopkeeper) {
		shopkeeper = clone_object(NPC + "shopkeeper");
		shopkeeper->arm_me();
		shopkeeper->move(TO);
		tell_room(TO, QCTNAME(shopkeeper) + " wanders in from " +
              "the back room.\n");
		shopkeeper->set_shop(TO);
		shopkeeper->set_store_room(query_store_room());
		return;
  }
  else if (!present(shopkeeper)) {
    if (shopkeeper->query_attack())
      return;
    else {
      tell_room(environment(shopkeeper), QCTNAME(shopkeeper) +
                "suddenly looks around with a start, and rushes " +
                "off somewhere.\n");
      shopkeeper->move_living("M", TO);
      if (shopkeeper->query_prop(LIVE_O_LAST_ROOM) == 
          find_object(query_store_room()))
        tell_room(TO, QCTNAME(shopkeeper) + " saunters in " +
                  "from the store room.\n");
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
exa_shelves ()
{
  object *inv;
  string temp;

  seteuid(getuid());
  if (!find_object(ROOM + "store_room"))
    (ROOM + "store_room")->load_me();

  inv = all_inventory(find_object(ROOM + "store_room"));
  if (!sizeof(inv))
    return "The shelves and racks are all bare, except for an "+
      "old dusty box on a lower shelf.\n";
  if (sizeof(inv) < 5)
    return "The shelves and racks are sparsely laden " +
      "with " + COMPOSITE_DEAD(inv) + ". There is also an old "+
      "dusty box on a lower shelf.\n";
  if (sizeof(inv) < 15)
    return "The shelves and racks are well-stocked with " +
      COMPOSITE_DEAD(inv) + ". There is also an old dusty box "+
      "on a lower shelf.\n";
  return "The shelves and racks are sagging under the load " +
    "of " + COMPOSITE_DEAD(inv) + ".\n";
}

/*
 * Function name: create_khalakhor_room
 * Description  : Turns this object into a room.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_khalakhor_room ()
{
  set_short("village shop of Tabor Sogh");
  set_long("   You're in the small, village shop of Tabor " +
           "Sogh. It doesn't appear to be particularly fancy, " +
           "little more than a stone building with several " +
           "shelves to store goods on and a small sign with " +
           "details on services offered here along with a poster. "+
           "Aside from a doorway leading into a back room, and a small " +
           "fireplace in one corner to warm customers on cold " +
           "nights, there's nothing else of any interest to " +
           "see aside from the shop's goods.\n");

  add_item(({"box","suit"}),
           "There is an old dusty box sitting on one of the lower shelves. "+
           "It seems to have some kind of old leather suit in it. It "+
           "doesn't seem to be for sale, perhaps its just garbage.\n");
  add_item(({"small sign", "sign"}),
           "You could probably read it.\n");
  add_item(({"floor", "ground"}),
           "The floor of the bank is hard-packed dirt.\n");
  add_item(({"walls", "wall"}),
           "The shop walls look much like they do from the " +
           "outside, comprised of thin plates of stone stacked " +
           "atop one another. With the exception of the shelves, " +
           "which, of course, are not present on the outside.\n");
  add_item(({"roof", "ceiling"}),
           "The ceiling of the shop is a simple thatch and wooden " +
           "rafter construction.\n");
  add_item(({"thatch", "seaweed", "seagrass"}),
           "The thatch looks to be tightly-bundled mats of " +
           "some sort of seagrass or seaweed.\n");
  add_item(({"rafters"}),
           "The thatch of the roof is supported by a handful of " +
           "very thin wooden rafters.\n");
  add_item(({"walls", "shelves"}),
           VBFC_ME("exa_shelves"));
  add_item("poster", "@@delivery_poster@@");
  add_cmd_item("poster", "read", "@@delivery_poster@@");
  set_office("village shop of Tabor Sogh",10);
  INSIDE;

  config_default_trade();
  set_money_give_max(1000);
  set_store_room(ROOM + "store_room");

  add_exit(ROOM + "store_room", "east", "@@check_allowed");
  add_exit(ROOM + "road_1_5", "west");
  reset_room();
  do_list("foo");
}



/*
 * Function name: shop_hook_filter_inventory
 * Description  : Used to filter certain objects out of the inventory
 *                available to players. In this case, we'll filter out
 *                livings.
 * Arguments    : ob - Object pointer to the object to test.
 * Returns      : 0 - Don't include in inventory.
 *                1 - Include in inventory.
 */
int
shop_hook_filter_inventory (object ob)
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
do_sell (string str)
{
  if (shopkeeper && present(shopkeeper)) {
    if (shopkeeper->query_no_deal(TP)) {
      tell_object(TP, shopkeeper->query_The_name(TP) +
                  " refuses to have anything to do with you.\n");
      tell_room(environment(TP), QCTNAME(shopkeeper) +
                " refuses to have anything to do with " +
                QTNAME(TP) + ".\n");
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
do_value (string str)
{
  if (shopkeeper && present(shopkeeper)) {
    if (shopkeeper->query_no_deal(TP)) {
      tell_object(TP, shopkeeper->query_The_name(TP) +
                  " refuses to have anything to do with you.\n");
      tell_room(environment(TP), QCTNAME(shopkeeper) +
                " refuses to have anything to do with " +
                QTNAME(TP) + ".\n");
      return 1;
    }
    return ::do_value(str);
  }
  write("There's no one here to help you judge its value!\n");
  return 1;
}

/*
 * Function name: do_show (MASK)
 * Description  : Called when the player tries to examine something.
 *                Used here to prevent transactions if the keeper
 *                has been killed.
 * Arguments    : str - What the player tried to see.
 * Returns      : 0 - Keep threading.
 *                1 - Stop threading.
 */
int
do_show (string str)
{
  if (shopkeeper && present(shopkeeper)) {
    if (shopkeeper->query_no_deal(TP)) {
      tell_object(TP, shopkeeper->query_The_name(TP) +
                  " refuses to have anything to do with you.\n");
      tell_room(environment(TP), QCTNAME(shopkeeper) +
                " refuses to have anything to do with " +
                QTNAME(TP) + ".\n");
      return 1;
    }
    return ::do_show(str);
  }
  write("There's no one here to show you anything!\n");
  return 1;
}

/*
 * Function name: init (MASK)
 * Description  : Initializes shop commands in the player.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
init ()
{
  ::init();
  init_shop();
  init_office();
}
