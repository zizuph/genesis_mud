/*
 * Bank of Telberin
 * By Finwe 
 * January 1997
 */
 
inherit "/std/room";
inherit "/lib/bank";
#include "default.h" 
#include "/d/Emerald/defs.h"
 
void
create_room()
{
    set_short("Bank of Telberin");
    set_long( "   You're in a brightly lit office with several "+
        "busy gnomes. This is odd since elves so rarely have " +
        "contact with gnomes. It appears, though, that a friendly " +
        "understanding must exist between the elves and the " +
        "gnomes. A sign sits on the counter. The deposit room is " +
        "upstairs.\n\n");
 
    add_item( ({ "gnomes", "gnome" }), "They happily count " +
        "their money, unaware of your presence.\n");
    add_item("counter", "It is polished to a bright sheen. You " +
        "see your face in it. There is is a sign standing on the " +
        "counter.\n");
    add_item( ({ "sign", "instructions" }), "There is writing on it.\n");
    add_cmd_item( ({ "sign", "instructions" }), 
        "read", "@@standard_bank_sign");
 
    add_exit(AVENUE_DIR + "road11", "out");
    add_exit(THIS_DIR + "deposit_room", "up");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    config_default_trade();
    set_bank_fee(17);
    config_trade_data();
}
 
void
init()
{
    ::init();
    bank_init();
}
