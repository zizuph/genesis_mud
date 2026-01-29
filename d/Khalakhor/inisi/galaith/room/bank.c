/**********************************************************************
 * - bank.c                                                         - *
 * - Bank within the tree on Galaith isle                           - *
 * - Created by Damaris 03/2001                                     - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Updated by Valen   2/2002                                      - *
 **********************************************************************/

#pragma strict_types

#include "defs.h"

#include <stdproperties.h>
#include <macros.h>

inherit "/d/Khalakhor/std/room";
inherit "/lib/bank";

public void reset_room();

string
show_sign(void)
{
    return(
"          The gold plated plaque reads:\n"+
"          +----------------------------------------+\n"+
"          |              Bank of Galaith           |\n"+
"          |        " + sprintf("%2d", bank_fee) +
                     "% fee to change coins         |\n"+
"          |----------------------------------------|\n"+
"          | Examples:                              |\n"+
"          | change copper and silver for gold      |\n"+
"          | test change copper and silver for gold |\n"+
"          | change 1 platinum for copper           |\n"+
"          | change platinum for 100 silver         |\n"+
"          | minimize coins                         |\n"+
"          +----------------------------------------+\n");
}

public void
create_khalakhor_room()
{
	config_default_trade();
	bank_fee = 5 + random(20);
	set_bank_fee(bank_fee);
	config_trade_data();
	set_short("A small money changers");
	set_long("   This is the money changers. There is an odd "+
	"looking counter in the corner with a bank teller sitting "+
	"quietly counting coins.\nThere is a plaque on the wall.\n");
	
	add_item(({"bank teller", "teller", "elven wood nymph", "nymph"}),
	"The bank teller is quietly counting some coins.\n" +
	"Her hair is hip length, soft brown and windswept.\n" +
	"She has soft brown skin.\n" +
	"She has lustrous deep brown eyes.\n" +
	"She has the pointed ears and the aura of an elven wood nymph.\n");
	
	add_item(({"ceiling"}),
	"The ceiling is made from intertwining limbs.\n");
	add_item(({"walls","wall"}),
	"The walls are simply made from bark and there is a mysterious "+
	"light emanating from it.\n");
	add_item(({"floor","ground"}),
	"The floor on which you are standing seems very firm, and is "+
	"made from the tree. It appears the tree has grown limbs "+
	"intertwine just to create the floor.\n");
	add_item(({"counter", "small counter", "wooden counter"}),
	"The small counter is made from the tree itself. It had grown "+
	"into a perfect counter with a few leaves growing out of it "+
	"in certain spots.\n");
	
	add_item(({"plaque"}), show_sign);
	
	add_cmd_item("plaque","read", show_sign);
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
	add_exit("tree", "south");
	add_fail("auto", "You walked into a wall!\n" +
	"Ouch! That's gotta hurt!\n");
	
	object deposit = clone_object("/d/Genesis/obj/deposit");
	deposit->set_bank_id(4604, "Galaith");
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
