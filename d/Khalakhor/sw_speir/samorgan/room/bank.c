/**********************************************************************
 * - bank.c                                                         - *
 * - A bank in SaMorgan                                             - *
 * - Created by Damaris@Genesis 12/2000                             - *
 * - Modified by Damaris@Genesis 02/2005                            - *
 **********************************************************************/

#pragma strict_types
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h";
inherit "/d/Khalakhor/std/room";
inherit "/lib/bank";

/*********************************************************************
 * - This adds the gks to the room so NPC's know where they are.   - *
 *********************************************************************/
public int *
query_local_coords()
{
	return ({7, 5});
}
public int *
query_global_coords()
{
	return SAMORGAN_COORDS;
}
void
create_khalakhor_room()
{
	config_default_trade();
	bank_fee = 10 + random(16);
	set_bank_fee(bank_fee);
	config_trade_data();
	set_short("The Bank of SaMorgan");
	set_long("   A counter that spans the width of this small "+
	"building catches the eye as it is long but it also shows "+
	"no indication of a break or separation that would allow "+
	"passage from one side to the other. An attendant is sitting "+
	"on a stool of some kind waiting to assist those with "+
	"banking needs. At the far end of the counter is a wooden "+
	"plaque.\n");
	
	add_item(({"plaque"}),
	"          The wooden plaque reads:\n"+
	"          +----------------------------------------+\n"+
	"          |             Bank of SaMorgan           |\n"+
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
	"          |             Bank of SaMorgan           |\n"+
	"          |        " + bank_fee + "% Fee to change coins         |\n"+
	"          |----------------------------------------|\n"+
	"          | Examples:                              |\n"+
	"          | change copper and silver for gold      |\n"+
	"          | test change copper and silver for gold |\n"+
	"          | change 1 platinum for copper           |\n"+
	"          | change platinum for 100 silver         |\n"+
	"          | minimize coins                         |\n"+
	"          +----------------------------------------+\n");
	
	add_item(({"room", "area", "bank"}), query_long);
	add_item(({"north", "east", "northeast", "northwest", "southeast", "southwest"}),
	"There is a wall in that direction.\n");
	add_item(({"south", "west"}),
	"That direction leads back out into the village street.\n");
	add_item(({"walls","wall"}),
	"There are lanterns fixed on two walls of the bank. "+
	"The walls are warm, but damp to touch.\n");
	add_item(({"floor","ground"}),
	"The floor on which you are standing seems very firm, and is "+
	"made of darkened wood.\n");
	add_item(({"wood"}),
	"The wood is sturdy and dark. Perfect for flooring.\n");
	add_item(({"lantern","lanterns"}),
	"The lanterns are fixed firmly to the wall, and cannot be taken.\n");
	add_item(({"counter", "long counter", "wooden counter"}),
	"The long counter is made from a soft pine which has been "+
	"polished to a beautiful shine.\n");
	add_item(({"attendent"}),
	"The attendent is ready to serve your needs.\n");
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 1);
	
	add_exit("vil0606", "west");	
	add_exit("vil0707", "south");
	add_fail("auto", "A wall stops you.\n");
	object deposit = clone_object("/d/Genesis/obj/deposit");
	deposit->set_bank_id(4601, "SaMorgan");
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
