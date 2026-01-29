/*
 *	/d/Gondor/morgul/city/rooms/bank
 *
 *	the money changer in Minas Morgul
 *
 *	Using the example made by Nick: 
 *	/d/Genesis/doc/examples/trade/bank.c
 *
 *	Copyright (c) 1993 by Christian Markus
 *
 *	Olorin, July 1993
 *
 *
 *  Modification log:
 *
 *     2008-01-09, Toby: Fixed for new bank support.
 */
#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
inherit "/lib/bank";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define STD_FEE 25

string  bank_sign();
void    add_deposit();

object  deposit;

public void
create_morgul_room()
{
    config_default_trade();

    set_extraline("It looks rather run-down and sleazy. "
        + "Here you can change money or minimize your coins for only a modest " 
        + "fee. Further instructions are written on a poster. Dark Street is " 
        + "to the west.");
    set_road(9);
    set_short_desc("in the money changer's office in Minas Morgul");

    add_item(({"street","dark street"}), BSN(
        "Outside the office, you can see narrow Dark Street running north. "));
    
    add_exit(MORGUL_DIR + "city/darkstr1", "west","@@check_exit");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_ALLOW_STEED, 1);

    set_bank_fee(STD_FEE); // To set the exchange fee (% of changed amount)
    config_trade_data();
    // set fee first!
    add_item(({"poster","instructions"}), bank_sign());
    add_cmd_item(({"poster","instructions"}), "read", bank_sign());

    /* You have to set these two to the same number in order to get the
     * right calculations.
     */
    set_money_greed_buy("@@discriminate");
    set_money_greed_change("@@discriminate");

    /* A bank is rich. And if you can't give out the max with each type
     * of money you'll have to use another formula than I have below,
     * I think.
     */
                      /* Copper Silver Gold  Platinum  */
    set_money_give_out( ({ 40000, 4000, 2000, 200, }) );
    set_money_give_max( 40000);
    set_money_give_reduce( ({  0,    0,    0,   0, }) );

    money_num = sizeof(query_money_types());
    
    add_deposit();
}

void
init()
{
    ::init();
    bank_init(); /* Add the bank commands */
}

/*
 * A few hooks to get your own messages.
 */
void
bank_hook_pay(string text)
{
    TP->reveal_me(1);
    write("You pay " + text + ".\n");
}

void
bank_hook_other_see(int test)
{
    TP->reveal_me(1);
    if (!test)
        say(QCTNAME(TP) + " changes some money.\n");
    else
        say(QCTNAME(TP) + " seems to calculate something.\n");
}

/*
 * Function name: bank_hook_minimized
 * Description:   Player minimized his coins
 */
void
bank_hook_minimized(string pay_text, string got_text)
{
    write("You pay "+pay_text+" and get "+got_text+" in return.\n"
       +  "Your coins are now minimized.\n");
    say(QCTNAME(TP) + " minimized " +
        TP->query_possessive() + " coins.\n");
}

/*
 * Function name: bank_sign
 * Description:   returns a string with a sign message
 * Arguments:     none
 * Returns:       message string
 */
string
bank_sign()
{
    return "You read:\n" + 
	"I provide you with a cheap way to relieve you of the burden " +
	"of heavy coins. " +
	"For each transaction I ask only a fee of about "+bank_fee+"%. " +
	"These are examples of what you can do: \n\n" +
	"\t- change copper and silver for gold\n" +
	"\t- test change copper and silver for gold\n" +
	"\t- change 1 platinum for copper\n" +
	"\t- change platinum for 100 silver\n" +
	"\t- minimize coins\n\n";
}

/*
 * Function name:   discriminate
 * Description:     Don't treat all players equal by giving different prices.
 * Returns:         A percentage.   100   pay normal price.
 *                                 >100   annoy player
 *                                 <100   help player
 */
int
discriminate()
{
   string race;
   int bargain;

   bargain = TP->query_skill(SS_TRADING);
   if(bargain > 30) bargain = 30;
   bargain = 103 - bargain/5;

   switch(query_feeling(TP))
   {
     case -1: bargain = (bargain *  95) / 100; break;
     case  0: break;
     case  1: bargain = (bargain * 105) / 100; break;
   }
   return bargain + STD_FEE;
}

/*
 * Function name: minimize
 * Description:   changes all coins into the most expensive type, minus a fee
 *		  BUGS - This function still not supports unstandard coins
 * Arguments:     str: predicate
 * Returns:       success
 */
int
minimize(string str)
{
    int *money_arr, *money_arr2, value, i, new_sum, total_sum;
    int my_fee;
    string change;

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
    new_sum = total_sum - (check_call("@@discriminate") - 100) * value / 100;
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

void
add_deposit()
{
    if (objectp(deposit))
        return;

    deposit = clone_object("/d/Genesis/obj/deposit");
    deposit->set_bank_id(1801, "Minas Morgul");
    deposit->move(TO);
}

void
reset_room()
{
    if (!objectp(deposit))
        add_deposit();
}

