
/* Copied over from Quetzl's Esgaroth Bank */

#pragma save_binary

inherit "/d/Rhovanion/lib/room";
inherit "/lib/bank";

#include <stdproperties.h>
#include "/d/Rhovanion/farlong.h"

add_depositor();

void
create_room()
{
    config_default_trade();

	set_short("Town bank");
	set_long("This is the town bank, where the people "+
        "come to store their money and trade it in for coins more to " +
        "their liking.  There is a sign here which you can read if " +
        "you are new to the area and need help.\n");

    add_item( ({ "sign", "instructions" }),
		"Perhaps you should read it?\n");

    add_cmd_item( ({ "sign", "instructions" }), "read", "@@standard_bank_sign");

	AE(RHUN+"ltown_sw/streets/st11","north",0);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1);

    set_bank_fee(17);

    config_trade_data();
    add_depositor();
}

init()
{
    ::init();

    bank_init();
}

add_depositor()
{
    seteuid(getuid(this_object()));
    clone_object("/d/Genesis/obj/deposit")->move(TO, 1);
}

enter_inv(object ob, object from)
{
    if ((ob->query_prop("_live_i_esg_ques")) == -1)
        ob->add_prop("_live_i_esg_ques", 1);
    ::enter_inv(ob, from);
}