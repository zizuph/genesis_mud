/*
 * The bank in the Calathin
 *
 *  Modified: 3 May 2003, by Bleys
 *      - Changed the set_long() to reflect the actual bank fee.
 *      - Set the bank fee as a var that is now used in the desc
 *          instead of a hard value
 *      - Changed the sign add_item to use the standard_bank_sign
 *          routine. "exa sign" and "read sign" should give the
 *          same output.
 *
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/lib/bank";


#include <stdproperties.h>
#define DEPOSIT "/d/Genesis/obj/deposit"

object door, deposit;

int bank_fee = 15;

/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
void
create_room()
{
    config_default_trade();
    set_short("The Bank of Calathin");
    set_long(
        "This is the Bank of Calathin. Here, you can exchange " +
        "your coins for other denominations. This bank charges " +
        "a " + bank_fee + "% interest on all transactions. With " +
        "that " + bank_fee + "%, the " +
        "banker has gotten many valuable things to put in his bank.  " +
        "On one wall, you see several paintings done by the great " +
        "Relistolon of Cam bra eis'. There is also a crystal " +
        "chandelier hanging high from the ceiling. The counters are " +
        "lined with precious metals. If only you could take the " +
        "counter to a local shop, you could be quite wealthy! " +
        "There is a sign and a plaque here that you can look at for " +
        "more instructions.\n");

    add_item("plaque", "@@standard_bank_sign");
//         "It contains instructions on how to exchange your money.\n");
    add_cmd_item("plaque", "read", "@@standard_bank_sign");

    set_bank_fee(bank_fee);
    config_trade_data();

    deposit = clone_object(DEPOSIT);
    deposit->set_bank_id(3001, "Calathin");
    deposit->move(TO, 1);

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
    door = clone_object(CALATHIN_DIR + "obj/bank_door");
    door->move(TO);
}

init()
{
    ::init();
    bank_init();
}

