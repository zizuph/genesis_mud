/**********************************************************************
 * - bank.c                                                         - *
 * -                                                                - *
 * - Created by Khail - March 30/97                                 - *
 * - Modified by Damaris@Genesis 01/2005                            - *
 **********************************************************************/

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/room";
inherit "/lib/bank";

public int *
query_local_coords()
{
    return ({11,2});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}

/*
 * Function name: create_khalakhor_room
 * Description  : Turns this object into a room.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_khalakhor_room()
{
  config_default_trade();
  bank_fee = 5 + random(26);
  set_bank_fee(bank_fee);
  config_trade_data();

    set_short("Bank of Port MacDunn");
    set_long("   A small building that appears to be the "+
        "village bank. A small window in the north "+
        "wall is covered with iron bars, behind which a "+
        "rather scrawny man appears to be awaiting your "+
        "custom. Just below the counter is a wooden plaque. "+
        "A single doorway leads out onto the street "+
        "to the north.\n");
        
  add_item(({"plaque"}),
   "          The wooden plaque reads:\n"+
   "          +----------------------------------------+\n"+
   "          |           Bank of Port MacDunn         |\n"+
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
   "          |           Bank of Port MacDunn         |\n"+
   "          |        " + bank_fee + "% Fee to change coins         |\n"+
   "          |----------------------------------------|\n"+
   "          | Examples:                              |\n"+
   "          | change copper and silver for gold      |\n"+
   "          | test change copper and silver for gold |\n"+
   "          | change 1 platinum for copper           |\n"+
   "          | change platinum for 100 silver         |\n"+
   "          | minimize coins                         |\n"+
   "          +----------------------------------------+\n");

    add_item(({"floor", "ground"}),
        "The floor of the bank is hard-packed dirt, and look " +
        "all you might, there's no loose change lying " +
        "forgotten anywhere in sight.\n");
    add_item(({"walls", "wall"}),
        "The walls of the bank are made from various sized " +
        "pieces of hard grey stone, carefully placed together " +
        "and packed with clay.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling of the bank is a simple thatch and wooden " +
        "rafter construction.\n");
    add_item(({"thatch", "seaweed", "seagrass"}),
        "The thatch looks to be tightly-bundled mats of " +
        "some sort of seagrass or seaweed.\n");
    add_item(({"rafters"}),
        "The thatch of the roof is supported by a handful of " +
        "very thin wooden rafters.\n");
    add_item(({"teller"}),
        "Behind the barred window, and eager teller peers " +
        "out at you expectantly.\n");
    add_item(({"bars", "window"}),
        "A window in the north wall is covered by heavy iron " +
        "bars, making the poor teller behind it look like " +
        "he's in a jail, but quite safe.\n");

    INSIDE;

    add_exit(ROOM + "road_11_1", "north");
	object deposit = clone_object("/d/Genesis/obj/deposit");
	deposit->set_bank_id(4602, "Port MacDunn");
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
