#pragma strict_types
#include <stdproperties.h>
#include <macros.h>

#include "/d/Kalad/defs.h"
inherit "/d/Kalad/room_std";
inherit "/lib/bank";

public void reset_room();
object ob1;

public void
create_room()
{
	::create_room();
	INSIDE;
	add_prop(ROOM_M_NO_TELEPORT,1);
	config_default_trade();
	bank_fee = 10 + random(20);
	set_bank_fee(bank_fee);
	config_trade_data();
	set_short("The Bank of Undraeth");
	set_long("You are within a room constructed from the dark rock so "+
      "common here within the Dark Dominion. The smooth stone interior of "+
      "this place is completely covered with a thin layer of gold foil, "+
      "which magnifies the light of the small glowing orb hanging from the "+
      "ceiling. A stone desk lies on the opposite side of the room, from "+
      "which a plaque is visible.\n");
   add_item(({"room"}),
      "It is where you are, have a look around.\n");
   add_item(({"dark rock","smooth stone","stone","rock"}),
      "It seems unnaturally dark, however, only a few glimpses of it can be seen "+
      "here because of the encovering gold foil.\n");
   add_item(({"encovering gold foil","encovering foil","gold foil","foil"}),
      "Shining in all its glory, it seems oddly out of place here deep "+
      "beneath the lands of light.\n");
   add_item(({"small glowing orb","small orb","glowing orb","orb"}),
      "The sole source of light for this room, its otherwise minimal light has "+
      "been enhanced by the reflective qualities of the gold foil prevalent "+
      "here.\n");
   add_item(({"stone desk","desk"}),
      "A desk made completely of dark, unyielding stone.\n");
    add_item(({"plaque"}),
      "          The gold plated plaque reads:\n"+
      "          +----------------------------------------+\n"+
      "          |            Bank of Undraeth            |\n"+
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
      "          |            Bank of Undraeth            |\n"+
      "          |        " + bank_fee + "% Fee to change coins         |\n"+
      "          |----------------------------------------|\n"+
      "          | Examples:                              |\n"+
      "          | change copper and silver for gold      |\n"+
      "          | test change copper and silver for gold |\n"+
      "          | change 1 platinum for copper           |\n"+
      "          | change platinum for 100 silver         |\n"+
      "          | minimize coins                         |\n"+
      "          +----------------------------------------+\n");
   add_exit(CPASS(drow/d20),"east","@@msg",-1,-1);
   ob1 = clone_object(CPASS(drow/npc/bank_owner));
   ob1 -> move_living("X",TO);
	object deposit = clone_object("/d/Genesis/obj/deposit");
        deposit->set_bank_id(3506, "Undraeth");
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
