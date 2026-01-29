/*
 * Bank of Telseron
 * Updated by Finwe September 1996
 */
inherit "/std/room";
inherit "/lib/bank";
 
#include "/d/Emerald/defs.h"
 
void
create_room()
{
    set_short("Bank of Telseron");
    set_long( "   You're in a small, quiet office. At various places "+
        "around the office, clerks are sitting at small tables, " +
        "counting and recounting their money. There is a counter " +
        "here, and on the counter someone placed a sign with " +
        "instructions. Upstairs is the main deposit room.\n\n");
 
    add_item( ({ "clerk", "clerks" }), "They greedily count " +
        "their money, unaware of your presence.\n");
    add_item("counter", "It is polished to a bright sheen. You " +
        "see your face in it. There is is a sign standing on the " +
        "counter.\n");
    add_item( ({ "sign", "instructions" }), "There is writing on it.\n");
    add_cmd_item( ({ "sign", "instructions" }), 
        "read", "@@standard_bank_sign");
 
    add_exit(TOWNSHIP_DIR + "rd23", "out");
    add_exit(TOWNSHIP_DIR + "deposit_room", "up");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    config_default_trade();
    set_bank_fee(12);
    config_trade_data();
}
 
void
init()
{
    ::init();
    bank_init();
}
