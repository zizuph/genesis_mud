inherit "/d/Kalad/room_std";
#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include "../default.h"

inherit "/lib/bank";

object ob1;

public void reset_room();

public void
create_room()
{
	config_default_trade();
	bank_fee = 10 + random(26);
	set_bank_fee(bank_fee);
	config_trade_data();
	
	set_short("The Plaza Bank");
	set_long("This is the wealthy Plaza Bank. On the wall are a "+
	"sign and a plaque, explaining how to use this bank. For a "+
	"mere fee, all your transactions will be taken care "+
	"of, and your money will be kept secure. The owner of the "+
	"bank, Ahmad, is a scrawny, meanly efficient man, who is "+
	"also very impatient. ");
	set_time_desc("\n", "Keeping him awake at this hour is NOT a good idea!\n");
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
	add_exit("sq_west", "northeast", 0, -1,-1);
	add_prop(ROOM_I_INSIDE,1);
	hear_bell = 2;
	ob1 = clone_object("/d/Kalad/common/central/npc/ahmad");
	ob1->move_living("M", TO);
    
	object deposit = clone_object("/d/Genesis/obj/deposit");
	deposit->set_bank_id(3503, "Plaza in Kabal");
	deposit->move(this_object(), 1);
	set_alarm(1.0,0.0,"reset_room");
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
