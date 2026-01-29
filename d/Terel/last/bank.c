/*
 * /d/Terel/last/bank.c
 *
 * This is a branch of the Gnomes of Genesis in Last.
 *
 * Modified from a combination of the banks in:
 *      /d/Genesis/start/human/town/bank.c
 *      /d/Shire/bree/rooms/town/bank.c
 *      /d/Terel/calathin/bank.c
 *
 * Created by Shanoga, November 29 2018
 */

#pragma strict_types

inherit "/std/room";

inherit "/lib/commands";
inherit "/lib/trade";
inherit "/lib/bank";

//inherit "/d/Genesis/obj/deposit";

#include <cmdparse.h>                        
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Genesis/sys/deposit.h"

#define TP  this_player()

/* 
 * Function Name: exchange_fee
 * Description:   Determines the exchange fee as a % based on the player's
 *                average stats. For players below 10 average stat it is only
 *                a 10% exchange rate. The rate goes up multiplicatively with
 *                the player's query_average_stats. The max exchange is at
 *                50% which is reached at legend size. Some examples:
 *                <10  avg =  6%    [novice]
 *                 30  avg = 12%    [beginner]
 *                 50  avg = 17%    [wanderer]
 *                 90  avg = 27%    [great adventurer]
 *                160  avg = 45%    [titan]
 *                180+ avg = 50%    [legend]
 *                The reason for this is that the bank was added for newbies
 *                to use when farming the nearby kobolds, but otherwise should
 *                be something that larger players have no interest in.
 * Arguments:     object player - the player whose stats are checked
 * Returns:       int - the percentage amount of the exchange fee, max 50
 */
int
exchange_fee(object player)
{
    int size_penalty;
    size_penalty = (ftoi(itof(player->query_average_stat())*2.5) / 10);
    return min(5 + size_penalty, 50);
}

string
personal_long()
{
    return "This is the Bank of Last. Here, you can place your coins in " +
        "the care of the Gnomes of Genesis and also exchange your coins " +
        "for other denominations. This bank charges a " + exchange_fee(TP) +
        "% transaction fee on all changing of coins. The counter where you " +
        "can access your account is heavily secured and along either side " +
        "of it you see a sign and a plaque that you can look at for more " +
        "instructions. The wall opposite the counter has an advertisement " +
        "for the Bounty Hunter's Office on the north side of town.\n";
}

void
create_room ()
{
    object bank;

    set_short("bank of Last");
    set_long("@@personal_long@@");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
    
    add_item(({"counter", "window"}), "The only window where you can " +
        "access your account has sturdy iron bars to protect the gnome on " +
        "the other side. There is a small gap between the flat counter top " +
        "and the bottom of the iron bars where you can exchange your " +
        "coins. Along either side of the bars are a poster and a sign that " +
        "you can look at for more instructions.\n");
    add_item("gap", "There is a small gap between the flat counter top and " +
        "the bottom of the iron bars where you can exchange your coins.\n");
    add_item("bars", "These strong iron bars were installed to keep all " +
        "manner of account holders from harrassing the gnome accountant or " +
        "the coffers on the other side.");
    add_item("accountant", "A small, greedy-looking gnome with a large " +
        "nose.\n");
    add_item("wall", "On the wall you see an advertisement encouraging you " +
        "to visit the Bounty Hunters Office on the north side of town.\n");
    add_item(({"ad", "advertisement", "paper", "piece of paper"}),
        "A simple piece of paper encouraging you to visit the Bounty " +
        "Hunters Office on the north side of town.\n");

    add_exit("/d/Terel/last/lroad2", "north");
    add_exit("/d/Terel/last/lroad5", "east");

    /* Add the Gnome Deposit to the room, but don't let it be visible. */
    bank = clone_object(GOG_DEPOSIT);
    bank->set_no_show_composite(1);
    bank->set_sign_text("The sign reads:\n\n" +
        "GNoMeS oF GeNeSiS\n" +
        "- aBSoLuTeLy SaFe\n" +
        "- FRieNDLy SeRViCe\n" +
        "- aVaiLaBLe eVeRyWHeRe\n" +
        "- aLL iMPoRTaNT PLaCeS aNyWay\n" +
        "- LoW FeeS\n\n" +
        "After that there is a lot of fine print regulating the terms " +
        "of deposit and giving instructions on using the GoG deposit.\n");
    bank->set_bank_id(3002, "the Bank of Last");
    bank->move(this_object(), 1);
    remove_my_desc(bank);
    config_default_trade();
    set_bank_fee(50);
    config_trade_data();
}

//-------------------------------------------------------------------

void init()
{
    ::init();
    bank_init(); /* Add the bank commands */
}

//-------------------------------------------------------------------



/*
 * Function name: bank_hook_minimized
 * Description:   Player minimized his coins
 */
void
bank_hook_minimized(string pay_text, string got_text)
{
    write("You pay " + pay_text + " and get " + got_text + " in return.\n" +
        "Your coins are now minimized.\n");
    say(QCTNAME(this_player()) + " minimized " +
        this_player()->query_possessive() + " coins.\n");
}


/*
 * Function name: minimize
 * Description:   changes all coins into the most expensive type, minus a fee
 *                BUGS - This function still not supports unstandard coins
 * Arguments:     str: predicate
 * Returns:       success
 */
int
minimize(string str)
{
    int *money_arr, *money_arr2, value, i, new_sum, total_sum;
    int my_fee;
    string change;
    
    set_bank_fee(exchange_fee(TP));

    money_arr = what_coins(this_player());

    money_arr2 = split_values(total_sum = money_merge(money_arr));
    for (i = 0; i < money_num; i++)
    {
        money_arr2[i] -= money_arr[i];
        if (money_arr2[i] < 0)
            money_arr2[i] = 0;
    }
    value = money_merge(money_arr2);
    if (!value)
    {
        bank_hook_already_minimized();
        return 1;
    }
    new_sum = total_sum - bank_fee * value / 100;
    money_arr2 = split_values(new_sum);
    for (i = 0; i < money_num; i++)
    {
        money_arr2[i] -= money_arr[i];
        if (money_arr2[i] < 0)
            money_arr2[i] = 0;
    }
    value = money_merge(money_arr2);
    if (!value)
    {
        bank_hook_no_idea();
        return 1;
    }

    MONEY_ADD(this_player(), new_sum);
    MONEY_ADD(this_player(), -total_sum);

    money_arr2 = what_coins(this_player());

    bank_hook_minimized(text(money_arr),text(money_arr2));
    
    return 1;
}
