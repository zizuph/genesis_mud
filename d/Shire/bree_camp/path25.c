/*
 * Path in Bree orc camp
 * By Finwe, July 2000
 */

#pragma strict_types

#include "local.h"

inherit CAMP_BASE;

void
create_camp_room()
{
    set_extraline("On a well trodden path. Signs of war are " +
        "scattered everywhere. Slashed trees and mark this as " +
        "a dangerous place.");

    add_item(({"slashed trees", "trees", "broken trees"}),
        "They have been smashed and stand as deadly reminders " +
        "of what lies north of here. There are claw marks on " +
        "some trunks, deep gouges made by some strong creatures.\n");
    add_item(({"signs of war", "debris"}),
        "Standards, broken trees, trampled dirt, all point to " +
        "an army that has been this way recently.\n");

    add_exit(CAMP_DIR + "path24", "northwest");
    add_exit(CAMP_DIR + "path26", "southwest");

    reset_shire_room();
}


void reset_shire_room()
{
    clone_camp_orcs();
}
