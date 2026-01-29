/*
 * /d/Cirath/tyr/obj/deposit.c, copied from /d/Genesis/obj/deposit.c
 * and modified to fit within theme.
 *    Decius, November 1997
 *
 *
 * /d/Genesis/obj/deposit.c
 *
 * This is the deposit of the Gnomes of Genesis, Genesis branch. If you
 * want to offer the services of the Gnomes of Genesis in your bank,
 * just clone this object into your bank room.
 *
 * /Mercade, August 5 1995
 */

#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/d/Cirath/tyr/obj/deposit_lib";

#include <money.h>

#define ACCOUNTS ("/d/Genesis/obj/accounts")
#define DAY_FEE  (6)
#define TERMS                                                                 \
" 1. To open an account you must deposit money.\n" +\
" 2. You may withdraw your money at any deposit branch.\n" +\
" 3. Only official copper, silver, gold and platinum coins are accepted.\n"+\
" 4. THe fee for safekeeping is six copper coins per day. Minimum fee\n"+\
"    time is one day.\n" +                 \
" 5. Fees are deducted from the account at every withdrawal anf\n" +\
"    recalculated at every deposit.\n" +\
" 6. The clerk will tell you how much money you have deposited for free.\n"+\
"    You ask him to do this by typing 'account'.\n" +                 \
" 7. Accounts are personal and the clerk may only turn money over to\n" +\
"    people he can see and recognize. Invisible people and people in\n" +\
"    disguise may have problems With withdrawals.\n" +\
" 8. You may make several transactions within a few minutes and just pay\n"+\
"    one fee.\n" +\
" 9. If the account has not been touched for 90 days, the owner is\n" +\
"    considered missing and all funds on the account become the property\n"+\
"    of the bank.\n" +\
"10. The bank not responsible for loss of funds due to earthquakes,\n"+\
"    robbery, powerfuL menacing magicians, the manager's mother in law or\n"+\
"    any other form of force majeure.\n"

/*
 * Function name: create_deposit
 * Description  : This function is called to create the deposit. Use it
 *                to set some variables.
 */
void
create_deposit()
{
    set_accounts(ACCOUNTS);
    set_money_types(MONEY_TYPES);
    set_terms(TERMS);
    set_fee(DAY_FEE);
    set_coin_file("/std/coins");

}
