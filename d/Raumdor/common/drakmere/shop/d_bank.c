#pragma strict_types
#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

inherit STD_ROOM;
inherit "/lib/bank";

public void reset_room();

public void
create_room()
{
	add_prop(ROOM_I_INSIDE,1);
    ::create_room();
	config_default_trade();
	bank_fee = 10 + random(26);
	set_bank_fee(bank_fee);
	config_trade_data();
	
	set_short("The Bank of Drakmere");
	set_long("You are standing in the Bank of Drakmere. "+
	"This large stone building has one long south wall, "+
	"where barred windows are placed. Behind each, there "+
	"is a teller, waiting to assist you. A plaque hangs "+
	"over the south wall.\n");
	add_item("teller","They stand ready to assist you "+
	"with a smile on their faces.\n");
	add_item("windows","They have bars on them, so no funny business.\n");
  add_item(({"plaque"}),
   "          The gold plated plaque reads:\n"+
   "          +----------------------------------------+\n"+
   "          |           Bank of Drakmere             |\n"+
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
   "          |           Bank of Drakmere             |\n"+
   "          |        " + bank_fee + "% Fee to change coins         |\n"+
   "          |----------------------------------------|\n"+
   "          | Examples:                              |\n"+
   "          | change copper and silver for gold      |\n"+
   "          | test change copper and silver for gold |\n"+
   "          | change 1 platinum for copper           |\n"+
   "          | change platinum for 100 silver         |\n"+
   "          | minimize coins                         |\n"+
   "          +----------------------------------------+\n");

	add_exit(DRAKMERE_DIR + "road15","north");
	add_exit(DRAKMERE_DIR + "road16","northeast");


	object deposit = clone_object("/d/Genesis/obj/deposit");
	deposit->set_bank_id(3504, "Drakmere");
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

int *
query_coordinates()
{
    return ({64, 1, 0});
}

