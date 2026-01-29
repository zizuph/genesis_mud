/*
** This is a version of the Gnomes of Genesis Deposit.
** It is customized for greedy, suspicious dwarves.
** A bit is different, but it all primarily works the same.
** Created By Leia
** February 15, 2006
*/


#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/d/Shire/greymount/dwarf_area/dwarf_deposit_lib";

#include <money.h>
#include <files.h>

#define ACCOUNTS ("/secure/accounts")
#define DAY_FEE  (6)
#define TERMS                                                                                                                           \
" 1. To open an account with the Dwarves of Genesis Bank, simply deposit money.\n" +                                                    \
" 2. You may withdraw your money at any Dwarves of Genesis institution, or any\n    other Gnomes of Genesis affiliated Bank.\n" +            \
" 3. Only official copper, silver, gold, or platinum coins will be accepted at\n    the Dwarves of Genesis Bank.\n" +                        \
" 4. The service charge for an account is six copper coins per day. The minimum\n    fee time is one day, two days for dwarf customers.\n" + \
" 5. Fees are deducted from the account at every withdrawal and recalculated at\n    every deposit.\n" +                                     \
" 6. The clerk will tell you how much money you have deposited free of charge.\n    You may request this service by typing 'account'.\n" +   \
" 7. Accounts are personal and secure. The clerk may only turn money over to\n    people, orcs, or goblins he can see and recognize. Invisible people and\n    people in disguise may have problems with withdrawals.\n" + \
" 8. You may make several transactions within a few minutes for only one fee.\n" +                                                      \
" 9. If an account has not been accessed for 90 days, the owner is considered\n    missing and all funds in the account become the property of the Dwarves\n    of Genesis Bank.\n" + \
"10. The Dwarves of Genesis Bank is not responsible for loss of funds due to\n    dragons, robbery, goblin or orcish raids, the clerk's ex-wife, or any\n    other unstoppable force.\n"

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
    set_usage(
        "Dwarves of Genesis Bank Deposit Usage:\n\n" +
        "- account\n" +
        "\tFind out how much you have in your account.\n\n" +
        "- deposit <coins> [except for <coins>]\n" +
        "\tDeposit coins into your account. You can specify not to deposit\n" +
        "\ta certain number of coins by adding the \"except for\" phrase\n\n" +
        "- withdraw <coins> [except for <coins>]\n" +
        "\tWithdraw coins from your account. You can specify not to withdraw\n"
+
        "\ta certain number of coins by adding the \"except for\" phrase\n\n" +
        "Example usage:\n" +
        "\taccount\n" +
        "\tdeposit 10 gold coins\n" +
        "\tdeposit silver, gold, and copper coins except for 20 silver coins\n"
+
        "\tdeposit coins\n" +
        "\twithdraw 10 silver and copper\n" +
        "\twithdraw coins except copper coins\n");
    set_fee(DAY_FEE);
    set_coin_file(COINS_OBJECT);
}