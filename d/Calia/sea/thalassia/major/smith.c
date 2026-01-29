
/* Smithy of Thalassia
 * 
 * coder(s):   Jaacar
 *
 * history:    17.7.03    room coded                      Jaacar
 *
 *   2021-06-12 - Cotillion
 *   - Made smith respawn
 *
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";
inherit "/d/Calia/sea/std/blacksmith_tools";

string
do_read_sign()
{
    return "\nWelcome to the Thalassian Smithy.\n"+
        "Here you may do the following:\n"+
        "cost <weapon/armour> to get an estimate,\n"+
        "sharpen <weapon> to fix the dull,\n"+
        "wax <weapon> to fix the rust,\n"+
        "mend <armour> to fix the dents\n\n";
}

void
create_water_room()
{
    object smithy;
    set_short("Thalassian Smithy");
    set_long("You have entered the Smithy of Thalassia. In "+
        "one corner you see an anvil while in another corner "+
        "you see what appears to be a forge of some sort. "+
        "There is a white marble counter in the middle of the "+
        "room. On the counter is a sign. There is a door leading "+
        "back out into the Major Zone to the east.\n");

    add_item(({"counter","marble counter","white marble counter",
        "white counter"}),"This white marble counter appears to "+
        "have been carved out of one single piece of marble. It "+
        "must have been quite a large sized block as the counter "+
        "is nearly ten feet long, four feet high and four feet "+
        "across. There is a sign on the counter which you can read.\n");
    add_item("anvil","There is an anvil sitting in one corner of "+
        "the shop. You assume this is used by the blacksmith to repair "+
        "weapons and armours.\n");
    add_item("forge","Now you have seen everything. This forge is "+
        "used by the blacksmith to repair weapons and armours. Inside "+
        "the forge you see a bright orange flame burning. It must be "+
        "some type of magical forge to have a flame burning underwater.\n");
    add_item("door","The door is open and it leads back out to the Major "+
        "Zone of the city.\n");
    add_item("sign",do_read_sign());
    add_cmd_item("sign","read",do_read_sign());

    add_npc(SEA_CREATURES+"smithy", 1, set_smith);
    add_swim_exit(THALM+"major16","east",0,1);
}

void
init()
{
    ::init();
    init_smith();
}

