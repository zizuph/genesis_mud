#pragma strict_types
#include <stdproperties.h>
#include <macros.h>

#include "/d/Kalad/defs.h"
inherit "/d/Kalad/room_std";
inherit "/lib/bank";

public void reset_room();

public void
create_room()
{
	config_default_trade();
	bank_fee = 10 + random(20);
	set_bank_fee(bank_fee);
	config_trade_data();
	
	set_short("The Bank of the Nobles");
	set_long("You are greeted with a cool breeze as you enter the "+
	"great bank of the Noble District. All along the walls, you see "+
	"many tellers standing by and serving customers. They sit behind "+
	"barred windows. A plaque is bolted on the wall for you to "+
	"read.\n");
	add_item("tellers","They stand ready to assist you with a smile "+
	"on their faces.\n");
	add_item("windows","They have bars on them, so no funny "+
	"buisness.\n");
	add_item("plaque","@@standard_bank_sign");
	add_cmd_item("plaque","read","@@standard_bank_sign");
	add_exit(NOBLE(road/r8),"southwest",0,-1,-1);
	add_prop(ROOM_I_INSIDE,1);
    add_item(({"plaque"}),
      "          The gold plated plaque reads:\n"+
      "          +----------------------------------------+\n"+
      "          |           Bank of the Nobles           |\n"+
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
      "          |           Bank of the Nobles           |\n"+
      "          |        " + bank_fee + "% Fee to change coins         |\n"+
      "          |----------------------------------------|\n"+
      "          | Examples:                              |\n"+
      "          | change copper and silver for gold      |\n"+
      "          | test change copper and silver for gold |\n"+
      "          | change 1 platinum for copper           |\n"+
      "          | change platinum for 100 silver         |\n"+
      "          | minimize coins                         |\n"+
      "          +----------------------------------------+\n");
	
	object deposit = clone_object("/d/Genesis/obj/deposit");
	deposit->set_bank_id(3505, "Nobles District");
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
