/*
 *  /d/Gondor/morgul/city/forge/forge_supplies.c
 * 
 *  Room where Bree smiths can buy supplies for their forging.
 *
 *  Created by Eowul, 11-12-2004
 */

#pragma strict_types

#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <composite.h>

#define IRON_COST       300
#define WOOD_COST       300
#define LEATHER_COST    300
#define SMITHSDIR_OBJ   "/d/Shire/guild/smiths/obj/"

inherit "/d/Gondor/morgul/city/morgul.c";

void reset_room();
string query_sign();

object  orc;

public void
create_morgul_room()
{
    set_extraline("This is the basement of Gorzag's Armoury. A small " +
        "doorway leads west while a set of stairs leads back up to the " +
        "armoury. Piles of old weapons and armours are stacked against " +
        "the smooth black stone walls. A small sign is attached to " +
        "the wall.");
    set_road(0);
    set_side("south");

    add_item( ({ "small sign", "sign" }), query_sign );
    add_cmd_item( ({ "small sign", "sign" }), "read", query_sign );
    add_item("basement", long);
    add_item("armoury", "It's upstairs and hard to see from here.\n");
    add_item(({ "doorway", "small doorway" }), 
        "It leads west into the forge.\n");
    add_item( ({ "set of stairs", "stairs" }), 
        "They lead back up to the armoury.\n");
    add_item( ({ "piles of old weapons and armours", "piles of weapons",
        "piles of armours", "piles", "pile", "weapons", "armours" }),
        "There are various piles with old weapons and armours, waiting " +
        "here to be melted down and reused as supplies.\n");
    add_item( ({ "smooth black stone walls", "smooth walls", "stone walls",
        "black walls", "walls", "stone", "black stone" }), 
        "It looks like the same black stone as the those used to " +
        "build the dark tower.\n");

    add_exit(MORGUL_DIR + "city/rooms/armoury",   "up",  "@@block_npc@@",1);
    add_exit("/d/Shire/guild/smiths/rooms/mage_forge",    "west", "@@check_exit",1);

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();

    // You hear hammering sounds comming through the western doorway.
    // A grumpy black orc walks by, his arms full with coals.
    // Unbearable heat rolls in through the western doorway.
}

/*
 * Function name: clone_and_move
 * Description  : Clone the number of items and move them to the player
 * Arguments    : filename - the item to clone
 *              : amount - the number of items to clone
 *              : cost - the price per item
 *              : player - the player to receive the items
 */
void clone_and_move(string filename, int amount, int cost, object player)
{
    object  *moved = ({});
    object  *dropped = ({});
    object  ob;
    int     i;

    // Check for the shopkeeper
    if(!objectp(orc) || (environment(orc) != this_object()))
    {
        write("The shopkeeper is not present.\n");
        return;
    }

    // Check for visibility
    if(!CAN_SEE_IN_ROOM(orc) || !CAN_SEE(orc, player))
    {
        orc->command("say Who's there?");
        return;
    }

    // Only sell to smiths
    if((this_player()->query_guild_name_craft() != "The Smiths Guild") &&
	   (!this_player()->query_wiz_level()))
    {
        orc->command("asay annoyed to " + OB_NAME(player) +
            " You couldn't even forge something if your life depended on it! " +
            "Begone!");
        return;
    }

    // Check for money
    if(!MONEY_ADD(player, -amount * cost))
    {
        orc->command("asay angrily to " + OB_NAME(player) +
            " You don't have enough money, maggot! Begone!");
        return;
    }

    // Clone and move
    for(i=0;i<amount;i++)
    {
        seteuid(getuid());
        ob = clone_object(filename);
        if(!ob->move(player))
            moved += ({ ob });
        else
        {
            ob->move(this_object(), 1);
            dropped += ({ ob });
        }
    }

    // Write the messages
    if(sizeof(moved))
    {
        tell_room(this_object(),
            QCTNAME(orc) + " gives " + QTNAME(player) + " " +
            COMPOSITE_DEAD(moved) + ".\n", player);
        player->catch_msg(QCTNAME(orc) + " gives you " + 
            COMPOSITE_DEAD(moved) + ".\n");
    }

    if(sizeof(dropped))
    {
        orc->command("asay amusedly to " + OB_NAME(player) + " " +
            "Weakling!");
        tell_room(this_object(),
            QCTNAME(orc) + " drops " + COMPOSITE_DEAD(dropped) + ".\n");
    }

    return;
}

/*
 * Function name: buy_cmd
 * Description  : Command for smith members to buy supplies
 * Arguments    : args - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
int buy_cmd(string args)
{
    string  amount_txt, item;
    int     amount;

    // Make sure we always have arguments
    if(!stringp(args) || !strlen(args))
    {
        notify_fail("Buy what?\n", 0);
        return 0;
    }

    // See what we want to buy
    if(!parse_command(args, ({}), "%d %s", amount, item))
    {
        parse_command(args, ({}), "%w %s", amount_txt, item);
        if(!strlen(item))
        {
            item = args;
            amount = 1;
        }
        else
        {
            amount = LANG_WORD2NUM(amount_txt);
        }
    }

    // Check the amount
    if((amount < 0) || (amount > 20))
    {
        notify_fail("You can only buy 20 items at a time.\n", 1);
        return 0;
    }

    // Allow the purchase of iron bars
    if(parse_command(item, ({}), "[iron] 'bar' / 'bars'"))
    {
        clone_and_move(SMITHSDIR_OBJ+ "ir_bar", amount, IRON_COST, TP);
        return 1;
    }

    /// Allow the purchase of leathers
    if(parse_command(item, ({}), "[dwarven] [elven] [hobbit] 'skin' / " +
        "'leather' / 'skins' / 'leathers'"))
    {
        clone_and_move(MORGUL_DIR + "city/forge/leather", amount, LEATHER_COST, TP);
        return 1;
    }

    // Allow the purchase of wooden poles
    if(parse_command(item, ({}), "[wooden] 'pole' / 'poles' / 'wood' / 'woods'"))
    {
        clone_and_move(SMITHSDIR_OBJ+ "sm_wood", amount, WOOD_COST, TP);
        return 1;
    }

    notify_fail("You can only buy iron bars, skins and wooden poles.\n");
    return 0;
}

/*
 * Function name: init
 * Description  : Add commands to the player
 */
void init()
{
    ::init();
    add_action(buy_cmd, "buy");
}

/*
 * Function name: reset_room
 * Description  : Make sure our shop orcsie is here
 */
void reset_room()
{
    // See if the orc is in our room
    if(!objectp(orc))
    {
        seteuid(getuid());
        orc = clone_object(MORGUL_DIR + "city/forge/owner");
        orc->arm_me();
    }

    if(environment(orc) != this_object())
    {
        orc->move_living("away", this_object());
    }
}

string query_sign()
{
    return
"      +--------------------------------------------------------------+\n"+
"      |    o                                                    o    |\n"+
"      |  o   o                                                o   o  |\n"+
"      |    o                                                    o    |\n"+
"      |                                                              |\n"+
"      |                 The Forge of Minas Morgul                    |\n"+
"      |                  --========oo=========--                     |\n"+
"      |                                                              |\n"+
"      |    Supplies are only sold to those who have the skills       |\n"+
"      |    to forge. For the low price of 300 copper coins,          |\n"+
"      |    we offer iron bars, various skins and wooden poles.       |\n"+
"      |                                                              |\n"+
"      |    o                                                   o     |\n"+
"      |  o   o                                               o   o   |\n"+
"      |    o                                                   o     |\n"+
"      +--------------------------------------------------------------+\n\n";

}
