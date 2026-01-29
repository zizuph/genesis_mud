/*
 * Modifaction log:
 * Finwe, April 2019: Added plaque that lists the bank fee
 */

#pragma strict_types
#pragma no_clone

inherit "/std/room";
inherit "/lib/bank";

#include <stdproperties.h>

#define DEPOSIT "/d/Genesis/obj/deposit"

public void
create_room()
{
    object deposit;
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Bank of Gont Port");
    set_long("This is the Gont Port Bank."+
        " Judging from the expensive appearance of the dark"+
        " granite walls and the polished dark marble floors,"+
        " this bank is frequented by prosperous merchants and"+
        " landowners. A large granite vault houses a gnome"+
        " deposit, where you can deposit your money on"+
        " account. There is a plaque on the wall with instructions.\n");
    add_item((({"granite walls", "walls"})),
        "The walls are made of cut granite stone, giving "+
        "the appearance of a very solid building.\n");
    add_item((({"marble floors", "floors"})),
        "The floors are polished to a high sheen.\n");
    add_item((({"vault", "granite vault"})),
        "The deposit is housed in a granite vault, "+
        "making your money very secure here.\n");

    add_item(({"plaque"}),
        "It hangs on the wall, ready to be read.\n");
    add_cmd_item("plaque", "read", "@@read_sign@@");


    config_default_trade();
    set_bank_fee(10);
    config_trade_data();
    // max_pay  copper, silver, gold, platinum
    set_money_give_out(({ 100000, 100000, 100000, 100000 }));
    set_money_give_reduce(({0, 0, 0, 0 })); /* Threshold */
    set_money_give_max(10000000);
    add_exit("city_street/city_road31", "west");

    deposit = clone_object(DEPOSIT);
    deposit->set_bank_id(4701, "Gont Port");
    deposit->move(this_object());
}

public void
init()
{
    ::init();
    bank_init();
}


string read_sign()
{
    return "The plaque reads:\n\n"+
   "          +----------------------------------------+\n"+
   "          |             Money changers             |\n"+
   "          |        10% Fee to change coins         |\n"+
   "          |----------------------------------------|\n"+
   "          | Examples:                              |\n"+
   "          | change copper and silver for gold      |\n"+
   "          | test change copper and silver for gold |\n"+
   "          | change 1 platinum for copper           |\n"+
   "          | change platinum for 100 silver         |\n"+
   "          | minimize coins                         |\n"+
   "          +----------------------------------------+\n";
}