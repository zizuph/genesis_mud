/* Udated this so it actually works correctly.
 * Damaris 2/2002
 */
#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include "../default.h"

inherit CVAN_ROOM;
inherit "/lib/bank";

object ob1;

public void reset_room();

public void
create_cvan_room()
{
	config_default_trade();
	bank_fee = 10 + random(26);
	set_bank_fee(bank_fee);
	config_trade_data();
	set_short("The money-changer's shop");
	set_long("You've just walked into the money-changer's shop in "+
	"the Caravan district. Clearly Turale, the money-changer, is a "+
	"wealthy man. Gazing at your surroundings you note the polished, "+
	"mirror-like marble floor and the gold-lined mahagony counter, "+
	"behind which sits the owner himself. There is a plaque above "+
	"the counter.\n");
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
    add_exit(CVAN + "wayfar/s3", "south");

    add_prop(ROOM_I_INSIDE, 1);

    set_hear_bell(1);

    ob1 = clone_object(NPC + "mcowner");
    ob1->move_living("M", TO);
    object deposit = clone_object("/d/Genesis/obj/deposit");
    deposit->set_bank_id(3502, "Caravan District");
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
