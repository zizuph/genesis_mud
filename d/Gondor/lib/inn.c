/*  
 *  /d/Gondor/lib/inn.c
 *
 *  Generic inn/pub/tavern for use within Middle Earth. 
 *  Example usage:
 *
 *  create_room() 
 *  {  
 *      setuid(); 
 *      seteuid(getuid());
 *
 *      // Optional, if not used, the barkeeper will put the item on the ground
 *      // if people can't carry it.
 *      object bar = clone_object("/d/Gondor/std/inn_bar");
 *      bar->move(this_object());
 *      set_bar(bar);  
 *
 *      add_menu_item("/doc/examples/obj/dutch_beer");
 *      add_menu_item("/doc/examples/obj/egg");
 *   
 *      config_default_trade();
 *      configure_inn();
 *  }
 *
 *  init
 *  {
 *      ::init();
 *      init_inn();
 *  }
 *
 *  remove_object()
 *  { 
 *      remove_inn_object();
 *      ::remove_object();
 *  }
 *
 *  reset_room()
 *  {
 *      object innkeeper = clone_object("yourinnkeeper");
 *      innkeeper->move(this_object());
 *      set_innkeper(innkeeper);
 *  }
 *
 *  Eowul, March 2015
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <cmdparse.h>
#include <language.h>
#include <files.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>

inherit "/lib/trade";

mapping configured_menu_items = ([ ]);
mapping menu_objects = ([ ]);
mapping group_titles = ([ ]);
object store_room;
object innkeeper;
object bar;

#define MAX_QUANTITY 50

// Prototypes
int query_menu_item_value(object item);
void clone_items_for_target(object item, int quantity, object target);

// Hooks

/*
 * Function name: inn_hook_no_team
 * Description:   Called when a player tried to buy items for a team, but isn't
 *                in one.
 * Arguments:     player - the player performing the purchase
 * Returns:       The command result code (usually 0)
 */
int
inn_hook_no_team(object player)
{
    notify_fail("You are not part of a team.\n");
    return 0;
}

/*
 * Function name: inn_hook_maximum_items
 * Description:   Write an error message when a player tries to buy more
 *                items than the maximum allows
 * Arguments:     player - the player performing the purchase
 *                maxquantity - the maximum quantity they can buy
 */
void
inn_hook_maximum_items(object player, int maxquantity)
{
    write("You can only buy " + LANG_NUM2WORD(maxquantity) + " items at "
        + "a time.\n");
}

/*
 * Function name: inn_hook_unknown_item
 * Description:   Write an error when a player tries to purchase an unknown
 *                item.
 * Arguments:     player - the player performing the purchase
 *                item - the item the player tries to purchase
 */
void
inn_hook_unknown_item(object player, string item)
{
    innkeeper->command("say to " + OB_NAME(player) + " I don't have any "
        + item + " on the menu.");
}

/*
 * Function name: inn_hook_innkeeper_not_present
 * Description:   Write an error when the player tries to purchase something
 *                but the innkeeper is not present in the room.
 */
void
inn_hook_innkeeper_not_present()
{
    write("You look around but are unable to find the innkeeper.\n");
}

/*
 * Function name: inn_hook_cant_see
 * Description:   Write a message when the player can't be seen by the 
 *                innkeeper.
 * Arguments:     player - the player performing the purchase
 */
void
inn_hook_cant_see(object player)
{
    innkeeper->command("say Who is there? I can't see you!");
}

/*
 * Function name: inn_hook_no_targets
 * Description:   Write an error when the indicated receipients of the order
 *                are either not present or not found otherwise.
 * Arguments:     player - the player performing the purchase
 */
void
inn_hook_no_targets(object player)
{
    innkeeper->command("say to " + OB_NAME(player) + " I cannot see the "
        + "persons that you want to order for.");
}

/*
 * Function name: inn_hook_cant_afford
 * Description:   Write a message when the player can't afford the ordered
 *                items
 * Arguments:     player - the player performing the purchase
 *                price - how much the player has to pay (cc)
 */
void
inn_hook_cant_afford(object player, int price)
{
    innkeeper->command("say to " + OB_NAME(player) + " You can't afford that.");
}

/*
 * Function name: inn_hook_order
 * Description:   Write messages when the player orders an item
 * Arguments:     player - the player performing the purchase
 *                quantity - the number of items ordered
 *                item - single copy of the item being ordered
 *                targets - livings receiving the order
 *                payed - [pc, gc, sc, cc] number of coins payed
 *                received - [pc, gc, sc, cc] number of coins received as change
 */
void
inn_hook_order(object player, int quantity, object item, 
    object *targets, int *payed, int *received)
{
    int personal_order = (sizeof(targets) == 1) && (targets[0] == player);
    if (quantity == 1) {
        if (personal_order)
        {
            write("You order yourself " + item->short() + ".\n");
        }
        else
        {
            write("You order " + item->short() + " for " 
                + COMPOSITE_LIVE(targets) + ".\n");
        }
    } 
    else
    {
        if (personal_order)
        {
          write("You order " + LANG_NUM2WORD(quantity) + " " + item->query_plural_short()
                + " for yourself.\n");
        }
        else
        {
            write("You order " + LANG_NUM2WORD(quantity) + " " + item->query_plural_short()
                + " for " + COMPOSITE_LIVE(targets) + ".\n");
        }
    }

    string payed_text = text(payed);
    string received_text = text(received);

    if (stringp(received_text))
    {
        write("You hand " + payed_text + " to " 
            + innkeeper->query_the_name(player) + " and receive "
            + received_text + ".\n");
    }
    else
    {
        write("You hand " + payed_text + " to "
            + innkeeper->query_the_name(player) + ".\n");
    }

    say(QCTNAME(player) + " hands " + QTNAME(innkeeper) + " some money.\n");
}

/*
 * Function name: inn_hook_items_transfered
 * Description:   Write messages confirming items transfered or dropped
 *                for a specific player
 * Arguments:     target - the player receiving the items
 *                moved - items moved to the player
 *                dropped - items the player couldn't carry
 */
void
inn_hook_items_transfered(object target, object *moved, object *dropped)
{
    if (sizeof(dropped)) 
    {
        if (!objectp(bar)) 
        {
            innkeeper->command("say to " + OB_NAME(target) + " As you are "
                + "unable to carry your order, I have placed them on the "
                + "ground.");
        } 
        else
        {
            innkeeper->command("say to " + OB_NAME(target) + " As you are "
                + "unable to carry your order, I have placed them on the "
                + bar->short() + ".");
        }
    }

    if (sizeof(moved))
    {
        target->catch_msg(QCTNAME(innkeeper) + " hands you " 
            + COMPOSITE_DEAD(moved) + ".\n");
        tell_room(this_object(), QCTNAME(innkeeper) + " hands something to "
            + QTNAME(target) + ".\n", ({ target }));
    }
}

/*
 * Function name: configure_inn
 * Description:   Load all menu items, and configure the store room
 *                Should be called from create_room
 */
nomask void
configure_inn()
{
    store_room = clone_object("/std/room");

    foreach(string group, string *filenames : configured_menu_items) 
    {
        menu_objects[group] = ({ });

        foreach(string filename : filenames) 
        {
            object item = clone_object(filename);
            item->move(store_room, 1);
            menu_objects[group] += ({ item });
        }
    }
}

/*
 * Function name: add_menu_item
 * Description:   Add an item to the menu
 * Arguments:     filename - filename of the item to add
 *                group - group to list this item under on the menu
 */
nomask void
add_menu_item(string filename, string group = "default")
{
    if (member_array(group, m_indexes(configured_menu_items)) == -1) 
    {
        configured_menu_items[group] = ({ });
    }

    configured_menu_items[group] += ({ filename });
}

/*
 * Function name: set_menu_group_title
 * Description:   Set group titles for the menu 
 */
nomask void
set_menu_group_title(string group, string title)
{
    group_titles[group] = title;
}

/*
 * Function name: buy_cmd
 * Description:   Command to order/buy items 
 * Arguments:     args - command arguments
 * Returns:       0 on failure, 1 on success
 */
nomask int
buy_cmd(string args)
{
    if (!args || !strlen(args)) 
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    int quantity = 1;
    string what = args;
    object *targets = ({ this_player() });

    string text1;
    string text2;
    if (sscanf(args, "%s for %s", text1, text2) == 2) 
    {
        what = text1;
        if (text2 == "team") 
        {
            if (sizeof(this_player()->query_team_others()) == 0)
            {
                return inn_hook_no_team(this_player());
            }

            targets = ({ this_player() }) + this_player()->query_team_others();
        }
        else
        {
            targets = PARSE_COMMAND(text2, this_object(), "[the] %l");
        }

        if (sizeof(targets) == 0) 
        {
            notify_fail(capitalize(query_verb()) + " " + text1 + " for whom?\n");
            return 0;
        }
    }

/*
    if (sscanf(args, "%d %s", quantity, text1) == 2) 
*/
    if(sscanf(args, "%d %s for %s", quantity, text1, text2)==3)   
    {
        what = text1;
     }

    if ((quantity * sizeof(targets)) > MAX_QUANTITY)
    {
        inn_hook_maximum_items(this_player(), MAX_QUANTITY);
        return 1;
    }

    if (!objectp(innkeeper) || (environment(innkeeper) != this_object()))
    {
        inn_hook_innkeeper_not_present();
        return 1;
    }

    if (!CAN_SEE_IN_ROOM(innkeeper) || !CAN_SEE(innkeeper, this_player()))
    {
        inn_hook_cant_see(this_player());
        return 1;
    }

    object item;
    if (!parse_command(what, store_room, "%o", item)) 
    {
        inn_hook_unknown_item(this_player(), what);
        return 1;
    }

    object *remaining_targets = FILTER_CAN_SEE(targets, innkeeper);
    if (!sizeof(remaining_targets))
    {
        inn_hook_no_targets(this_player());
        return 1;
    }

    int total_price = quantity * sizeof(targets) * query_menu_item_value(item);
    if (!can_pay(total_price, this_player()))
    {
        inn_hook_cant_afford(this_player(), total_price);
        return 1;
    }

    int *coins = pay(total_price, this_player());   
    inn_hook_order(this_player(), quantity, item, targets, 
        coins[0..3], coins[4..]);

    foreach(object target : targets) 
    {
        clone_items_for_target(item, quantity, target);
    }

    return 1;
}

/*
 * Function name: clone_items_for_target
 * Description:   Takes an item from the storeroom and makes a copy for the
 *                target in the specified quantity
 * Arguments:     item - the item to clone
 *                quantity - number of items to clone
 *                target - target to receive the items
 */
nomask void 
clone_items_for_target(object item, int quantity, object target)
{
    object *items = ({ });

    if (IS_HEAP_OBJECT(item)) 
    {
        object newitem = clone_object(MASTER_OB(item));
        newitem->set_heap_size(quantity);
        items = ({ newitem });
    }
    else 
    {
        for(int i = 0; i < quantity; i++)
        {
            items += ({ clone_object(MASTER_OB(item)) });
        }
    }

    object *moved = ({ });
    object *dropped = ({ });

    foreach(object newitem : items)
    {
        if (newitem->move(target)) 
        {
            dropped += ({ newitem });
            if (objectp(bar)) {
                newitem->move(bar, 1);
            } else {
                newitem->move(this_object(), 1);
            }
        } 
        else 
        {
            moved += ({ newitem });
        }
    }

    inn_hook_items_transfered(target, moved, dropped);
}

/*
 * Function name: init_inn
 * Description:   Add the available commands in this inn
 */
nomask void
init_inn()
{
    add_action(buy_cmd, "buy");
    add_action(buy_cmd, "order");
}

/*
 * Function name: remove_inn_object
 * Description:   Cleanup the store room
 */
nomask void
remove_inn_object() 
{
    store_room->remove_object();
}

/*
 * Function name: query_menu_item_value
 * Description:   Determine item value, uses OBJ_I_VALUE by default
 * Argument:      item - store object
 * Returns:       item value in copper coins
 */
int
query_menu_item_value(object item)
{
    return item->query_prop(OBJ_I_VALUE);
}

/*
 * Function name: query_menu_description
 * Description:   Constructs a list of menu items and their pricing
 * Returns:       a list of items
 */
string
query_menu_description()
{
    string menu = "";

    foreach(string group, object *items : menu_objects) 
    {
        if (strlen(menu) > 0) menu += "\n";

        string group_title = group_titles[group];
        if (stringp(group_title))
        {
            menu += group_title + ":\n\n";
        }

        foreach(object item : items) 
        {
            int value = query_menu_item_value(item) * 100 
                            / query_money_greed_sell();
            menu += sprintf("%-40s %5d cc\n",
                capitalize(item->short()), value);
        }
    }

    menu += "\nYou may order for other players in addition to ordering for "
        + "multiple players.\n"
        + "Try using 'order <item> for <players>' similar to how you target "
        + "players with an emotion.\n"
        + "You may also 'order <item> for team' to buy things for your \n"
        + "teammates.\n";

    return menu;
}

/*
 * Function name: set_innkeeper
 * Description:   Configure an NPC to act as an innkeeper for messages
 * Arguments:     npc - set the NPC acting as innkeeper
 */
nomask void
set_innkeeper(object npc)
{
    innkeeper = npc;
}

/*
 * Function name: set_bar
 * Description:   If set, then items that players can't carry are placed in this
 *                container.
 * Arguments:     ob - the container
 */
nomask void
set_bar(object ob)
{
    bar = ob;
}