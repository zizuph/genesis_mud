/*********************************************************************
 * - bank.c                                                        - *
 * - Added to port distict, seemed odd not to have one here        - *
 * - This bank fee varies with each reboot.                        - *
 * - Created by Damaris@Genesis 5/2003                             - *
 *********************************************************************/

#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include "default.h"
inherit PORT_ROOM;
inherit "/lib/bank";

public void reset_room();

public void
create_port_room()
{
	config_default_trade();
	bank_fee = 10 + random(20);
	set_bank_fee(bank_fee);
	config_trade_data();
	set_short("The money-changer's shop");
	set_long("You've just walked into the money-changer's shop in "+
	"the Port district. It isn't much to look at but it serves a "+
	"purpose. There is a plaque above the counter.\n");
    add_item(({"plaque"}),
      "          The gold plated plaque reads:\n"+
      "          +----------------------------------------+\n"+
      "          |             Money changers             |\n"+
      "          |        " + bank_fee + "% Fee to change coins         |\n"+
      "          |----------------------------------------|\n"+
      "          | Examples:                              |\n"+
      "          | change copper and silver for gold      |\n"+
      "          | test change copper and silver for gold |\n"+
      "          | change 1 platinum for copper           |\n"+
      "          | change platinum for 100 silver         |\n"+
      "          | minimize coins                         |\n"+
      "          +----------------------------------------+\n");
    add_cmd_item("plaque","read",
      "          The gold plated plaque reads:\n"+
      "          +----------------------------------------+\n"+
      "          |             Money changers             |\n"+
      "          |        " + bank_fee + "% Fee to change coins         |\n"+
      "          |----------------------------------------|\n"+
      "          | Examples:                              |\n"+
      "          | change copper and silver for gold      |\n"+
      "          | test change copper and silver for gold |\n"+
      "          | change 1 platinum for copper           |\n"+
      "          | change platinum for 100 silver         |\n"+
      "          | minimize coins                         |\n"+
      "          +----------------------------------------+\n");

        add_item(({"wall", "walls"}),
        "The walls are dingy and humid from the salt air.\n");
        add_item(({"floor", "flooring", "ground"}),
        "The flooring is made from hardwood and is quite worn "+
        "from use and a bit dingy from the salt air.\n");
        add_item(({"hard wood", "hardwood"}),
        "The hardwood is made into sturdy planks\n");
        add_item(({"plank", "planks"}),
        "The planks are made of hardwood and make up the floor.\n");
        add_item(({"wood"}),
        "There is wood in the walls, ceiling, floor and even the "+
        "counter is made from wood.\n");
        add_item(({"counter"}),
        "The counter is sturdy and there is a bank attendent "+
        "behind it.\n");
        add_item(({"ceiling"}),
        "The ceiling lacks any luster that it could be afforded due "+
        "to the salt air.\n");
        add_item(({"bank attendent", "attendednt"}),
        "The bank attendednt is quietly helping customers with their "+
        "money transactions.\n");
        add_exit(PORT + "s72", "south");
        
        add_prop(ROOM_I_INSIDE, 1);

	object deposit = clone_object("/d/Genesis/obj/deposit");
	deposit->set_bank_id(3501, "Port of Kabal");
	deposit->move(this_object(), 1);
	reset_room();
}

void
reset_room()
{
}

void
init()
{
    ::init();
    bank_init();

}
