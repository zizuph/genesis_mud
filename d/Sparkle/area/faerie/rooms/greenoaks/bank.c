/*
 * Bank of Green Oaks
 * By Finwe, March 2005
 */
 
#pragma strict_types

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit INDOORS_BASE;
inherit "/lib/bank";
static object vefrain;

void add_stuff();
 
void
create_indoor_room()
{
    add_prop(ROOM_S_MAP_FILE, "faerie_map.txt");
    set_short("Bank of Green Oaks");
    set_long("This is the " + short() + ". It is a branch of the Gnomes " +
        "of Genesis, the bankers of the area. The room is large and " +
        "clean. A counter spans the width of the room. Bank ledgers " +
        "can be seen stacked behind the counter, obviously where balances " +
        "are kept of all the accounts taken care of here. There is a " +
        "sign and a plaque attached to the wall.\n");

    set_add_ceiling_flat("The ceiling is white and undecorated.");
    set_add_counter();
    add_item(({"ledgers", "bank ledgers", "ledger", "bank ledger"}),
        "These are records of bank transactions done here. They are " +
        "thick and look well used. They're stacked in piles behind " +
        "the counter.\n");

// sets up bank 
    set_bank_fee(BANK_FEE);
    //config_trade_data();
    config_default_trade();
    config_trade_data();
    room_add_object("/d/Genesis/obj/deposit");
    add_item("plaque","@@standard_bank_sign");
    add_cmd_item("plaque","read", "@@standard_bank_sign");

    add_exit(GO_DIR + "road03", "north");
}

void
init()
{
    ::init();
    bank_init();
}

void reset_room() 
{ 
    add_stuff();
}

void
add_stuff()
{

    if(!vefrain)
        vefrain = clone_object(NPC_DIR + "banker");
        vefrain->move(TO);
}

/*
 * Function name: standard_bank_sign
 * Description:   returns a string with a sign message
 * Arguments:     none
 * Returns:       message string
 */
string
standard_bank_sign()
{
    return "You read:\n\n" + 
    "\t+-----------------------------------------------------------+\n" +
    "\t|                                                           |\n" +
    "\t|   Our bank provides you with a cheap way to relieve you   |\n" +
    "\t|   of the burden of heavy coins.                           |\n" +
    "\t|                                                           |\n" +
    "\t|   For each transaction we ask only a " + bank_fee + "% fee.             |\n" +
    "\t|   This is an example of what you can do:                  |\n" +
    "\t|   - change copper and silver for gold                     |\n" +
    "\t|     This would make you change all your copper and silver |\n" +
    "\t|     coins into as much gold as possible.                  |\n" +
    "\t|   - test change copper and silver for gold                |\n" +
    "\t|     This would show you the outcome of the command behind |\n" +
    "\t|     the 'test' word.                                      |\n" +
    "\t|   - change 1 platinum for copper                          |\n" +
    "\t|     This would change 1 platinum coin to copper coins.    |\n" +
    "\t|   - change platinum for 100 silver                        |\n" +
    "\t|     This would convert a platinum coin to 100 silver      |\n" +
    "\t|     coins, and the change that would be left over from    |\n" +
    "\t|     the platinum coin needed after 100 silver coins has   |\n" +
    "\t|     been given                                            |\n" +
    "\t|   - minimize coins                                        |\n" +
    "\t|     This changes all coins into the most valuable types   |\n" +
    "\t|     possible                                              |\n" +
    "\t|                                                           |\n" +
    "\t|   There is a sign with more information you may read.     |\n" +
    "\t|   You may also <read fine print>, <read usage> and        |\n" +
    "\t|   <read terms>.                                           |\n" +
    "\t|                                                           |\n" +
    "\t+-----------------------------------------------------------+\n\n";
}
