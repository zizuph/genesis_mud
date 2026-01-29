/*
 * The bank in Edoras
 *
 * Rewritten using /lib/bank.c by Olorin, February 1995
 */
inherit "/d/Gondor/common/room";
inherit "/lib/bank";

#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

#define STD_FEE        25

string  bank_poster();
void    add_deposit();

object  deposit;

/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
void
create_room()
{
    set_short("The Bank of Edoras");
    set_long(BSN(
        "This is the Bank of Edoras. Here you can exchange money. "
      + "Instructions are written on a large poster behind a wooden "
      + "counter. "
      + "A doorway leads back out into the street to the east."));
    add_exit(EDORAS_DIR + "stairs2","east",0,0);
    add_prop(ROOM_I_INSIDE,1);

    config_default_trade();
    set_bank_fee(STD_FEE);
    config_trade_data();

    set_money_greed_buy("@@discriminate");
    set_money_greed_change("@@discriminate");

                     /* Copper Silver Gold  Platinum  */
    set_money_give_out(({40000, 4000, 2000, 200}));
    set_money_give_max(40000);
    set_money_give_reduce(({0, 0, 0, 0}));

    money_num = sizeof(query_money_types());

    add_item(({"poster","instructions"}), bank_poster());
    add_cmd_item(({"poster","instructions"}), "read", bank_poster());

    add_deposit();
}

void
init()
{
    ::init();
    bank_init(); /* Add the bank commands */
}

int
set_my_fee(string race)
{
    mixed fee;
    switch(race)
    {
        case "human":  fee =  80; break;
        case "hobbit": fee =  95; break;
        case "dwarf": 
        case "gnome":  fee = 100; break;
        case "elf":    fee = 105; break;
        case "goblin": fee = 120; break;
        default:       fee = 100; break;
    }
    fee = (fee * STD_FEE) / 100;
    return fee;
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
bank_hook_change(string text)
{
    write("You get " + text + " back.\n");
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
        + "Your coins are now minimized.\n");
    say(QCTNAME(this_player()) + " minimized " +
	this_player()->query_possessive() + " coins.\n");
}

/*
 * Function name: bank_poster
 * Description:   returns a string with a poster message
 * Arguments:     none
 * Returns:       message string
 */
string
bank_poster()
{
    return "You read:\n" + BSN(
	"The Bank of Edoras provides you with a cheap way to relieve "
      + "you of the burden of heavy coins. "
      + "For each transaction we ask only a fee of about "+bank_fee+"%. "
      + "These are examples of what you can do:") +
	" - Change copper and silver for gold.\n" +
	" - Test change copper and silver for gold.\n" +
	" - Change 1 platinum for copper.\n" +
	" - Change platinum for 100 silver.\n" +
	" - Minimize coins.\n";
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
   int     bargain = TP->query_skill(SS_TRADING);

   if (bargain > 30)
       bargain = 30;
   bargain = 103 - bargain/5;

   return bargain + set_my_fee(TP->query_race());
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
    deposit->move(TO);
}

void
reset_room()
{
    if (!objectp(deposit))
        add_deposit();
}

