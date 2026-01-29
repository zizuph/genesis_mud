inherit "/std/room";
inherit "/lib/bank";

#include "/d/Emerald/defs.h"

void
create_room()
{
    set_short("Bank office of Leah");
    set_long("   You enter a tidy, small bank.  You can "+
      "hear some rustling behind the counter and feel relieved "+
      "that there is someone here who can and will help you and "+
      "serve all your banking needs. There is a "+
      "sign with instructions on the counter.\n\n");

    add_item( ({ "sign", "instructions" }), "There is writing on it.\n");
    add_cmd_item( ({ "sign", "instructions" }), "read", "@@standard_bank_sign");

    add_exit(VILLAGE_DIR + "tower", "east");

    clone_object("/d/Genesis/obj/deposit")->move(this_object());

    add_prop(ROOM_I_INSIDE, 1);

    config_default_trade();
    set_bank_fee(15);
    config_trade_data();
}

void
init()
{
    ::init();
    bank_init();
}
