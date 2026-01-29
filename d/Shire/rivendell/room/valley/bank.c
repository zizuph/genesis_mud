/*
 *  The Imladris Bank
 *
 *  Updated bank to handle gems, bank num is 1203
 * -- Finwe January 6 2008
 */

#pragma save_binary


#include "local.h"
 
inherit HOUSE_IN_BASE;
inherit "/lib/bank";

#define NUM sizeof(MONEY_TYPES) /* How many types of money do we use? */

void
create_house_room()
{
    object deposit = clone_object("/d/Genesis/obj/deposit");
    
    deposit->set_bank_id(1203, "Imladris");
    deposit->move(this_object(), 1);

    set_short("The Imladris Bank");
    set_long("This bright room is the bank of Imladris. Here " +
        "citizens of the valley deposit their money for safe " +
        "keeping. A large window is set into the north wall. " +
        "A plaque is attached to the counter.\n");

   add_exit(VALLEY_DIR + "n_path02", "west", 0);

   add_item("plaque","@@standard_bank_sign");
   add_cmd_item("plaque","read","@@standard_bank_sign");

    add_item(({"north window", "northern window"}), 
        "@@north_down@@\n");
    set_extra_window("@@window_position@@ set into the " +
        "north wall.");

    num_of_windows=1;

   config_default_trade();
   set_bank_fee(15);
   config_trade_data();
}

init() {
   ::init();
   bank_init();
}
