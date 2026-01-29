/* Ashlar, 18 May 97 - a moneychanger */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit OUTER_IN;
inherit "/lib/bank";

void
create_neraka_room()
{
	set_short("in a small, dark building");
    set_long("You are standing within a small and dark building. The only " +
        "features within the room are a low table and a sign on one wall. " +
        "There is also a door leading out.\n");
    add_item("sign","The sign is really just painted on the wall.\n");
    add_cmd_item(({"sign"}),({"read"}),
        ({"@@standard_bank_sign"}));
    add_item(({"table","low table"}),
        "The table is scratched and worn.\n");
    add_item("door","The door leads out.\n");
    add_item_inside();
    remove_item("walls");
    add_item("walls","There is a sign on the east wall, but other than " +
        "that the walls are unremarkable.\n");
    remove_item("east wall");
    add_item("east wall","There is a sign painted on the east wall.\n");

    add_exit(NOUTER+"blue/b12","out","@@msg_out");

    config_default_trade();
    set_bank_fee(40);
    config_trade_data();

}

void
init()
{
	::init();
    bank_init();
}

int
msg_out()
{
	write("You step out of the dark building into the market square.\n");
    return 0;
}

