/*
 * cadu_bank.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/bank";

#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
	config_default_trade();
	bank_fee = 10 + random(16);
	set_bank_fee(bank_fee);
	config_trade_data();
	
	set_short("The Cadu Bank");
	set_long("This is a dark, damp circular room with walls "+
	"covered with gold and platinum in rectangular patterns. "+
	"This is the famous and well-known bank of Cadu.  It is "+
	"run by wizards, who decided that setting up a bank would "+
	"be a lot of fun.  Behind an iron-barred counter is a "+
	"mage who looks like he wouldn't mind taking some of your "+
	"money. A plaque is attached to the counter.\n");
	add_exit("cadu_a1", "north");
	
	add_item(({"mage", "clerk"}),
        "The human tries to estimate how much money you carry with "+
        "you.\n");
	add_item(({"plaque"}),
	"          The wooden plaque reads:\n"+
	"          +----------------------------------------+\n"+
	"          |               Bank of Cadu             |\n"+
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
	"          The wooden plaque reads:\n"+
	"          +----------------------------------------+\n"+
	"          |               Bank of Cadu             |\n"+
	"          |        " + bank_fee + "% Fee to change coins         |\n"+
	"          |----------------------------------------|\n"+
	"          | Examples:                              |\n"+
	"          | change copper and silver for gold      |\n"+
	"          | test change copper and silver for gold |\n"+
	"          | change 1 platinum for copper           |\n"+
	"          | change platinum for 100 silver         |\n"+
	"          | minimize coins                         |\n"+
	"          +----------------------------------------+\n");
	
	add_item(({"counter", "iron-barred counter"}),
	"You see no way to get behind the counter, since it is "+
	"totally enclosed by thick iron bars.  You wonder how "+
	"they get the money out of there.\n");
	
	add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
	object deposit = clone_object("/d/Genesis/obj/deposit");
	deposit->set_bank_id(4603, "Cadu");
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
