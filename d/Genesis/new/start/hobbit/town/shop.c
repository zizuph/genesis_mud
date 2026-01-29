/*
 * File         : /d/Genesis/start/hobbit/town/shop.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/20/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The shop is owned by a young and alert hobbit and will allow
 *        selling new equipment like spades, sacks and gauntlets as well
 *        as buying and selling loot. NOTE this code is based on the
 *        example /doc/examples/trade/shop.c
 * 
 * TODO         :
 *        Add NPC shop owner, Add more descriptions, Set up a default
 *         inventory for the shop, Tune 'Cabinet' -> Shelfs
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

#pragma strict_types

/* inherits */
inherit "/std/room";
inherit "/lib/shop";


/* includes */
#include <stdproperties.h> 
#include <macros.h> 

#include "../hobbit.h"

/* defines */
#define STORE  EX_ROOM + "store"


/* prototypes */
void create_room();
void reset_room();

/* globals */
object Merchant;

/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("The village shop.");
    set_long(
      "A counter divides the rather darkish room. There is a sign on the " +
      "wall. On shelfs behind the counter all kinds of things resides, " +
      "ranging from crap to what seems to be unpolished treasures. The " +
      "dim light makes it hard to tell though. Behind the counter you " +
      "find the owner of the shop watching every move in the room with " +
      "a greedy and suspicous expression in his face.\n");
    add_item("counter", 
      "A sturdy piece of furniture made of oak is used as a counter. \n");
    add_item(({ "shelf", "shelfes", "storage", "goods" }), 
      "An unordered mix of older and newly made equipment resides on " +
      "shelfes in the back of the room. \n");
    add_item("smell", 
      "A light smell of leather and oil can be found in the dusty air. \n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG,
      "It's dark, you can't see anything.\n");
    add_prop(ROOM_S_DARK_MSG,
      "The darkness makes it impossible to");
    add_prop(ROOM_S_EXIT_FROM_DESC,
      "from the shop.");
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/20/99.\n");
    
    add_exit("portroad3.c", "northeast");
    
    
    config_default_trade();
    set_money_give_max(1000);
    set_store_room(STORE);
    
    
    
    /*
     * Add an exit to the store-room, the first parameter is the path to
     * the store, the second command to enter it and the third parameter
     * is a VBFC call to block all mortals players from using the exit.
     */
    
    add_exit(STORE, "cabinet", "@@check_wizard");
    reset_room();
}
/*
 * Function name:       reset_room
 * Description  :       replenish npc & stuff, if needed
 */
void
reset_room()
{
    setuid();
    seteuid(getuid());
    if (!objectp(Merchant))
    {
        Merchant = clone_object(EX_MON + "merchant");
        Merchant->move(this_object(), 1);
        tell_room(TO, QCTNAME(Merchant) + " arrives quickly.\n");
    }
    
}

void
init()
{
    ::init();
    // Init the shop
    init_shop();
    
    // Check if the NPC is here and let him check the player
    if (Merchant && present(Merchant))
    {
        Merchant->set_visitor(this_player());
    }
}

/*
 * We do not want mortal players to walk into the cabinet and help
 * themselves. However, wizards might need to go in there if something
 * is wrong. Therefore we block their exit.
 */
int
check_wizard()
{
    // wizards may use the exit.
    if (this_player()->query_wiz_level())
    {
        return 0;
    }
    
    // however, mortal players cannot...
    write("The cabinet is locked. You cannot get into it.\n");
    say(QCTNAME(this_player()) + " fails to enter the cabinet.\n");
    return 1;
}


