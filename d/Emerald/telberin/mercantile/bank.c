/*
 *  /d/Emerald/telberin/mercantile/bank.c
 *
 *  This is the bank of Telberin, where all transactions
 *  of money eventually find their home within the city.
 *
 *  Copyright (c) April 2003, by Cooper Sherry (Gorboth)
 *
 *    Copied from:
 *      /d/Gondor/morgul/city/rooms/bank.c
 *      by Olorin (c) 1993 by Christian Markus
 */
#pragma strict_types

#include "../defs.h";

inherit TELBERIN_BUILDING;
inherit "/lib/bank";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h" /* for Gondor macros */

#define STD_FEE 25


/* prototypes */
string  bank_sign();
void    add_deposit();

/* global variables */
object  deposit;


/*
 * Function name:        create_telberin_building
 * Description  :        set up the building
 */
public void
create_telberin_building()
{
    config_default_trade();

    set_short("within the Bank of Telberin");
    set_em_long("Within the Bank of Telberin."
      + " The hallmarks of security and precision mark every inch"
      + " of this impressive building. Great slabs of stone frame the walls,"
      + " which are adorned with many symbols and emblems. A long marble"
      + " counter runs the length of one end of the hall, behind which"
      + " many elves are busy with ledgers and scrolls, recording the"
      + " ever shifting movement of the city's money market. A few gnomes"
      + " occasionally wander in and out of the action, always ready"
      + " to intervene with corrections. There is a plaque with instructions"
      + " mounted to a nearby wall.\n");

    add_item( ({ "here", "area", "bank", "bank of telberin" }), long());
    add_item( ({ "hallmarks", "security", "hallmarks of security",
                 "precision", "security and precision",
                 "hallmarks of security and precision", "building",
                 "impressive building", "hall", "room" }),
        "The stone which comprises these walls is thick and finely"
      + " cut to a glass-like polish. Guards stand at attention at"
      + " every corner of the room. Business is flowing smoothly and"
      + " chaos is kept to a minimum. This is a well-honed bank,"
      + " indeed.\n");
    add_item( ({ "guards", "guard" }),
        "Guards keep post within these walls at all times to insure"
      + " the security of the city's economy.\n");
    add_item( ({ "stone", "wall", "walls", "polish",
                 "glass-like polish", "slab", "slabs", "great slab",
                 "great slabs", "great slab of stone", "stone slab",
                 "great stone slab", "great stone slabs",
                 "great slabs of stone" }),
        "The walls are comprised of great slabs of stone which have"
      + " been finely cut to a glass-like polish. They are adorned"
      + " at regular intervals with various symbols and emblems.\n");
    add_item( ({ "symbol", "emblem", "symbols", "emblems" }),
        "Most of these emblems are unfamiliar to you. One is of a"
      + " Unicorn head within a laurel wreath. Another is of a"
      + " four-pointed star within a circular field.\n");
    add_item( ({ "unicorn", "unicorn head", "lauren wreath",
                 "wreath", "laurel" }),
        "The image of the Unicorn is prevelant throughout Telberin,"
      + " symbolizing the incarnation of Telan-Ri in ancient times.\n");
    add_item( ({ "star", "four-pointed star", "four pointed star",
                 "circular field", "circle" }),
        "The four-pointed star is the symbol of Telberin itself, and"
      + " has been incorporated into many things, including the"
      + " layout of the main avenues of the city.\n");
    add_item( ({ "counter", "marble counter", "long counter",
                 "long marble counter" }),
        "A long marble counter separates many of the clerks who are"
      + " busy with their ledgers from the main floor of the hall.\n");
    add_item( ({ "clerk", "clerks", "elf", "elves" }),
        "The elves who run the bank appear to be very focused, and yet"
      + " unhurried or burdened by their labor. There is a sense of"
      + " assurance and calm within this building.\n");
    add_item( ({ "ledger", "ledgers", "scroll", "scrolls",
                 "ledgers and scrolls" }),
        "The business of the city is no concern of yours. You would"
      + " probably be ready for a tea break in a matter of moments"
      + " were it to be handed to you.\n");
    add_item( ({ "gnomes" }),
        "Gnomes, the ever-eager bookeepers of Genesis, are not satisfied"
      + " to let the elves do their work without supervision. They dart"
      + " to and fro among the elves, who appear used to their meddling,"
      + " and tolerate it with patience and serenity.\n");
    add_item( ({ "floor", "down", "ground" }),
        "The floor is cut from the same slabs of stone as the walls."
      + " Footfalls can be heard throughout the room against its"
      + " glass-like surface.\n");
    add_item( ({ "up", "ceiling", "roof" }),
        "The ceiling is high and unadorned. It is slightly vaulted so"
      + " that echoes within the hall are dispersed somewhat.\n");


    set_bank_fee(STD_FEE); // To set the exchange fee (% of changed amount)
    config_trade_data();
    // set fee first!
    add_item( ({ "plaque", "instructions" }), bank_sign());
    add_cmd_item( ({ "plaque", "instructions" }), 
                  ({ "read" }), bank_sign());

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
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from inside the bank.");

    add_exit("/d/Emerald/telberin/artisans_way05", "north", 0, 1, 1);

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
    return "You read:\n"
      + " The Bank of Telberin provides a safe and inexpensive way to"
      + " efficiently handle money transactions. Such transactions"
      + " require only a very modest " + bank_fee + "% handling"
      + " fee. Examples of the type of transactions you may complete"
      + " here include the following:\n\n" +
	" - change copper and silver for gold\n" +
	" - test change copper and silver for gold\n" +
	" - change 1 platinum for copper\n" +
	" - change platinum for 100 silver\n" +
	" - minimize coins\n";
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

   switch(this_player()->query_race())
   {
       case "goblin":
           bargain = (bargain *  95) / 100;
           break;
       case "elf":
           bargain = (bargain * 105) / 100;
           break;
       default:
           break;  
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
    /* Bank ID 3201 as defined in /d/Emerald/open/SHOPS. */
    deposit->set_bank_id(3201, "Telberin");
    deposit->move(TO);
}

void
reset_room()
{
    if (!objectp(deposit))
        add_deposit();
}

public mixed
query_location_ids()
{
    return "[the] [large] 'bank' / 'building' [of] [telberin]";
}

public mixed
query_location_closed()
{
    return 0;
}

public mixed
query_location_desc()
{
    return "This is the bank of Telberin.\n";
}

public string
query_entry_desc()
{
    return "into the bank";
}
