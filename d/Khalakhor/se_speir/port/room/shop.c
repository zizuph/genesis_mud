/*
 * shop.c
 *
 * Local shop for the village of Port MacDunn.
 *
 * Khail - March 31/97
 * Modified to inheirt new /d/Khalakhor/lib/shop
 * by Damaris 01/2001
 */
#pragma strict_types

inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/shop";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"

object shopkeeper;

public int *
query_local_coords()
{
    return ({16,3});
}

public int *
query_global_coords()
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
public int
check_allowed()
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
public void
reset_room()
{
    ::reset_room();
    if (!shopkeeper)
    {
        shopkeeper = clone_object(NPC + "brom");
        shopkeeper->arm_me();
        shopkeeper->move(TO);
        tell_room(TO, QCTNAME(shopkeeper) + " wanders in from " +
            "the back room.\n");
        shopkeeper->set_shop(TO);
        shopkeeper->set_store_room(query_store_room());
        return;
    }
    else if (!present(shopkeeper))
    {
        if (shopkeeper->query_attack())
            return;
        else
        {
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
public string
exa_shelves()
{
    object *inv;
    string temp;

    seteuid(getuid());
    if (!find_object(ROOM + "store_room"))
        (ROOM + "store_room")->load_me();

    inv = all_inventory(find_object(ROOM + "store_room"));
    if (!sizeof(inv))
        return "The shelves and racks are all bare!\n";
    if (sizeof(inv) < 5)
        return "The shelves and racks are sparsely laden " +
            "with " + COMPOSITE_DEAD(inv) + ".\n";
    if (sizeof(inv) < 15)
        return "The shelves and racks are well-stocked with " +
            COMPOSITE_DEAD(inv) + ".\n";
    return "The shelves and racks are sagging under the load " +
        "of " + COMPOSITE_DEAD(inv) + ".\n";
}

/*
 * Function name: create_khalakhor_room
 * Description  : Turns this object into a room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_room()
{
    set_short("shop of Port MacDunn");
    set_long("   You've entered what appears to be the " +
        "local shop of Port MacDunn. The low-ceilinged " +
        "stone room has walls full of racks and shelves. " +
        "There's no counter here, just a small table where " +
        "the owner probably settles down to haggle with " +
        "the more tight-fisted customers. A small sign is " +
        "mounted on one wall, with some instructions you " +
        "can read.\n");

    add_item(({"small sign", "sign"}),
        "You could probably read it.\n");
    add_item(({"floor", "ground"}),
        "The floor of the bank is hard-packed dirt, and look " +
        "all you might, there's no loose change lying " +
        "forgotten anywhere in sight.\n");
    add_item(({"walls", "wall"}),
        "The walls of the bank are made from various sized " +
        "pieces of hard grey stone, carefully placed together " +
        "and packed with clay. A number of racks and " +
        "shelves cover the walls, for storage and display " +
        "of wares.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling of the bank is a simple thatch and wooden " +
        "rafter construction.\n");
    add_item(({"thatch", "seaweed", "seagrass"}),
        "The thatch looks to be tightly-bundled mats of " +
        "some sort of seagrass or seaweed.\n");
    add_item(({"rafters"}),
        "The thatch of the roof is supported by a handful of " +
        "very thin wooden rafters.\n");
    add_item(({"walls", "shelves"}),
        VBFC_ME("exa_shelves"));
    add_item(({"table", "small table"}),
        "It's a simple little wooden table, but sturdy enough " +
        "to do business on. A small sign is posted to the " +
        "wall behind it.\n");

    INSIDE;

    config_default_trade();
    set_money_give_max(1000);
    set_store_room(ROOM + "store_room");

    add_exit(ROOM + "store_room", "south", "@@check_allowed", 0, 1);
    add_exit(ROOM + "road_15_3", "west");
    reset_room();
}

/*
 * Function name: init (MASK)
 * Description  : Initializes shop commands in the player.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
init()
{
    ::init();
    init_shop();
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
public int
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
public int
do_sell(string str)
{
    if (shopkeeper && present(shopkeeper))
    {
        if (shopkeeper->query_no_deal(TP))
        {
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
public int
do_value(string str)
{
    if (shopkeeper && present(shopkeeper))
    {
        if (shopkeeper->query_no_deal(TP))
        {
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
public int
do_show(string str)
{
    if (shopkeeper && present(shopkeeper))
    {
        if (shopkeeper->query_no_deal(TP))
        {
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

