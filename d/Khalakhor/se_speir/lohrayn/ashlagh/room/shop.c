/*
 * shop.c
 *
 * Local shop for the village of Baile Ashlagh, copied from Tabor Sogh
 *
 * Khail - March 31/97
 * Zima  - June 10/98
 * Modified to inheirt new /d/Khalakhor/lib/shop
 * by Damaris 01/2001
 * added Deliveries /d/Genesis/delivery/
 * Damaris@Genesis 11/2005
 */
#pragma strict_types
 
inherit "/d/Khalakhor/std/room";
inherit "/d/Khalakhor/lib/shop";
inherit "/d/Genesis/delivery/office"; 
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include "defs.h"
#include "/d/Khalakhor/sys/defs.h"
 
object shopkeeper;
 
public int * query_local_coords() { return ({3,6}); }
 
//
// check_allowed - allow only wizards and shopkeeper to enter store room
//
public int check_allowed()
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
 
//
// reset_room
//
public void reset_room()
{
	    reset_office();
	    ::reset_room();
	    if (!shopkeeper)
	    {
		    shopkeeper = clone_object(NPC + "shopkeeper");
		    shopkeeper->equip_me();
		    shopkeeper->move(TO);
		    tell_room(TO, QCTNAME(shopkeeper)+" wanders "+
		    "down from upstairs.\n");
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
                tell_room(TO, QCTNAME(shopkeeper) + " saunters down " +
                    "from the upstairs.\n");
            else
                tell_room(TO, QCTNAME(shopkeeper) + " rushes in from " +
                    "the courtyard.\n");
        }
    }
}
 
//
// exa_shelves
//
public string exa_shelves()
{
    object *inv;
    string temp;
 
    seteuid(getuid());
    if (!find_object(ROOM + "store_room"))
        (ROOM + "store_room")->load_me();
 
    inv = all_inventory(find_object(ROOM + "store_room"));
    if (!sizeof(inv))
        return "The shelves and racks are all bare.\n";
    if (sizeof(inv) < 5)
        return "The shelves and racks are sparsely laden " +
            "with " + COMPOSITE_DEAD(inv) + ".\n";
    if (sizeof(inv) < 15)
        return "The shelves and racks are well-stocked with " +
            COMPOSITE_DEAD(inv) + ".\n";
            "on a lower shelf.\n";
    return "The shelves and racks are sagging under the load " +
        "of " + COMPOSITE_DEAD(inv) + ".\n";
}
 
//
// create_khalakhor_room
//
public void create_khalakhor_room()
{
    set_short("shop of Baile Ashlagh");
    set_long("   You're in the small village shop of Baile " +
        "Ashlagh. It doesn't appear to be particularly fancy, " +
        "though it is neat and clean. The walls are lined with several "+
        "shelves to store goods and there is a small sign with "+
        "details on services offered here along with a poster. Aside "+
        "from a narrow staircase leading into an upper store room and a " +
        "small fireplace in one corner to warm customers on cold " +
        "nights, there's nothing else of any interest to " +
        "see aside from the shop's goods.\n");
 
    add_item(({"small sign", "sign"}),
        "You could probably read it.\n");
    add_item(({"floor", "ground"}),
        "The floor of the shop is made of long wooden planks.\n");
    add_item(({"walls", "wall"}),
        "The shop walls look much like they do from the " +
        "outside, made of wood painted in pastel pink framed and crossed "+
        "with long dark brown beams. With the exception of the shelves, " +
        "which, of course, are not present on the outside.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling of the shop is a simple thatch and wooden " +
        "rafter construction.\n");
    add_item(({"walls", "shelves"}),
        VBFC_ME("exa_shelves"));
    add_item(({"stairs","steps","staircase"}),
        "It is a small staircase which leads up to a store room. ");
    add_item("fireplace",
        "It is a small clay brick fireplace used to warm the shop.\n");
    set_office("shop of Baile Ashlagh",10); 
    add_item("poster", "@@delivery_poster@@");
    add_cmd_item("poster", "read", "@@delivery_poster@@");
    INSIDE;
 
    config_default_trade();
    set_money_give_max(1000);
    set_store_room(ROOM + "store_room");
 
    add_exit("store_room","up","@@check_allowed");
    add_exit("court3", "west");
    reset_room();
    do_list("foo");
}
 
//
// init
//
public void init()
{
	::init();
	init_shop();
    	init_office();
}
 
//
// shop_hook_filter_inventory
//
public int shop_hook_filter_inventory(object ob)
{
    if (living(ob))
        return 0;
    return 1;
}
 
//
// trans_ok - make sure shopkeeper here & willing to do business with TP
//
public int trans_ok(string trans)
{
    if (!(shopkeeper && present(shopkeeper)))
       write("There's no one here to "+trans+"!\n");
    else if (shopkeeper->query_no_deal(TP))
       {
       tell_object(TP, shopkeeper->query_The_name(TP) +
                   " refuses to have anything to do with you.\n");
       tell_room(environment(TP), QCTNAME(shopkeeper) +
                 " refuses to have anything to do with "+QTNAME(TP)+".\n");
       }
    else
        return 1;
    return 0;
}
 
//
// do_sell - prevent transactions of shopkeeper isn't here
//
public int do_sell(string str)
{
    if (trans_ok("buy anything from you"))
       return ::do_sell(str);
    else
       return 1;
}
 
//
// do_value - prevent transactions when shopkeeper not here
//
public int do_value(string str)
{
    if (trans_ok("help you judge its value"))
       return ::do_value(str);
    else
       return 1;
}
 
//
// do_show - prevent if shopkeeper not here
//
public int do_show(string str)
{
    if (trans_ok("show you anything"))
       return ::do_show(str);
    else
       return 1;
}
