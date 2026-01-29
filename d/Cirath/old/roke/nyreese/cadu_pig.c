/*
 * cadu_pig.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/trade";

#include "defs.h"
#include <stdproperties.h>
#include <money.h>
#include <macros.h>

#define PIGEON_VALUE 10
#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

void
create_room()
{
    set_short("Burned-down pigeon-house");
    set_long("Someone has burned down the old pigeon house. However, " +
             "it might still be possible to hire a pigeon here, because " +
             "the owner has built small cages to keep them in instead. " +
             "A small sign is attached to a gnome that is standing " +
             "in the middle of the ruin.\n");

   add_exit("cadu_pos", "east");
   add_exit("cadu_a4" , "south");

   add_item("sign", "Carrier pigeon:  10 copper\n");
   add_cmd_item("sign", "read", "Carrier pigeon:  10 copper\n");

   add_item(({"gnome", "small gnome"}),
      "The small gnome makes sure that the pigeons that return stay in a " +
      "good shape, so they can deliver their messages with great speed. " +
      "He is also in charge of hiring the carrier pigeons.\n");

   config_default_trade();  /* Set up the trading system */
                         /* Copper Silver Gold Platinum  */
   set_money_give_out(   ({ 10000,    32,   2,    1 })); /* Max_pay   */
   set_money_give_reduce(({     0,     4,   2,    1 })); /* Threshold */
}



int
do_hire(string str)
{
    object pigeon, tp;
    string item_name, pay_type, get_type, str1, coin_pay_text, coin_get_text;
    int *money_arr;

    tp = this_player();

    /*  
     * Check if the player defines what she wants to pay with
     * and what you would like in return.
     */

    if (!str)
    {
        notify_fail("Hire what?\n");
        return 0;
    }

    if (sscanf(str, "%s for %s and get %s", item_name, pay_type, get_type)!= 3)
    {
        get_type = "";
        /* Hmmm... Maybe she only wishes to pay with a certain type */
        if (sscanf(str, "%s for %s", item_name, pay_type) != 2)
        {
            pay_type = "";
            item_name = str;
        }
    }

    if (!(item_name == "pigeon" || item_name == "carrier pigeon"))
    {
        notify_fail("Hire what?\n");
        return 0;
    }
    if (sizeof(money_arr = pay(PIGEON_VALUE, tp, pay_type, 0, 0, get_type))==1)
    {
        if (money_arr[0] == 1)
        {
            tell_room(this_object(),
                      "The gnome says: I fear you cannot afford a carrier " +
                      "pigeon with only those coins, " +
                      tp->query_nonmet_name() + ".\n");
            return 1;
        }
        if (money_arr[0] == 2)
        {
            tell_room(this_object(),
                      "The gnome says: You have no " + 
                      pay_type + " coins on you, " +
                      tp->query_nonmet_name() + ".\n");
            return 1;
        }
        else
        {
            tell_room(this_object(),
                      "The gnome says: I fear you cannot afford a carrier " +
                      "pigeon, " + tp->query_nonmet_name() + ".\n");
            return 1;
        }
    }

    /* Okay, the pigeon is paid for, now give it to the player */
    pigeon = clone_object(ROKEDIR + "npc/pigeon");
    if (pigeon->move(tp))
    {
        write("You cannot carry that much!\n");
        pigeon->remove_object();
        return 1;
    }

    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

    write("You pay " + coin_pay_text + " and hire yourself a pigeon.\n");
    if (coin_get_text)
        write("You get " + coin_get_text + " back from the small gnome.\n");
    say(QCTNAME(tp) + " hires " + tp->query_objective() +
        "self a carrier pigeon.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_hire, "hire");
}
