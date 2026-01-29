/* File         : /d/Khalakhor/se_speir/rannoch/village/bank.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-29      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/room";
inherit "/lib/bank";

void
create_add_items()
{
    add_item(({"floor","ground"}),
               "The floor of the bank is hard-packed dirt, and kept "
             + "very clean.\n");
    add_item(({"walls","wall"}),
               "The walls are wooden, with only one small window in "
             + "the south wall.\n");
    add_item(({"roof","ceiling"}),
               "The ceiling of the bank is a simple thatch and "
             + "wooden rafter construction.\n");
    add_item(({"thatch"}),
               "Made of thick reeds and straw along with bark and "
             + "grass the thatch looks strong enough to keep rain "
             + "out and warmth in.\n");
    add_item(({"rafters"}),
               "The thatch of the roof is supported by a handful "
             + "of very thin wooden rafters.\n");
    add_item(({"teller","woman","old woman","banker"}),
               "A decrepit old woman sits behind the desk. Being "
             + "a banker in these parts where people hardly use "
             + "money can not be a very profitable business.\n");
    add_item(({"window","south wall"}),
               "You look out the dirty window and see the lake "
             + "outside, and a walkway just outside this building.\n"); 
    add_item(({"desk","counter","table"}),
               "A polished wooden desk, with no visible drawers.\n");
    add_item(({"doorway","door"}),
               "The doorway is rather low, and the door is in great "
             + "need of repair.\n");

    add_exit(ROOM + "road_15_7.c", "out",0,1,0);
}
void
create_room_tells()
{
    add_tell(({"The old woman behind the desk hums to herself.\n",
               "The old woman behind the desk sighs deeply.\n",
               "The old woman behind the desk smiles at you.\n",
               "The old woman behind the desk eats a turnip.\n",
               "The old woman behind the desk counts a few coins.\n",}));

}
public void
create_khalakhor_room()
{

    set_short("Inside a small building");
    set_long("After a quick look around, you see that this " +
             "appears to be the village bank. Behind a desk by " +
             "the west wall sits an old woman, counting coins. " +
             "The low doorway to the north takes you back to the " +
             "street.\n");

    create_add_items();

    set_tell_time(400);
    create_room_tells();

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_I_INSIDE, 1);

    config_default_trade();

    set_bank_fee(20); /* To set the exchange fee (% of changed amount) */

    config_trade_data();

    clone_object("/d/Genesis/obj/deposit")->move(TO);
}
public void
bank_hook_pay(string text)
{
    tell_object(TP, "You hand " + text + " to the old woman " +
        "behind the desk.\n");
}
public void
bank_hook_change(string text)
{
    tell_object(TP, "The old woman gives you " + text + " change " +
        "back.\n");
}
public void
bank_hook_other_see(int test)
{
    if (!test)
        say("The old woman changes some of " + QTNAME(TP) + "'s " +
            "for " + HIM + ".\n");
    else
        say(QCTNAME(TP) + " stares thoughtfully at a handful " +
            "of change.\n");
}
public void
init()
{
    ::init();
    bank_init();
}



