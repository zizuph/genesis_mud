/*
 * Path to Rivendell
 * By Finwe, November 1997
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit HOUSE_IN_BASE;
 
void
create_house_room()
{
    set_short("An upstairs corridor");
    set_long("Standing at the top of stairs, you notice corridors goes " +
        "off in different directions. The corridor is wide with off-white " +
        "walls. Some paintings decorate the walls. Above you is the " +
        "belltower which announces the time in the valley and warns " +
        "of danger.\n");

    add_item(({"painting", "paintings"}),
        "The paintings depict scenes of the Great March from Cuivienen " +
        "to the western shores.\n");
    add_item("belltower",
        "The belltower rises majestically from the roof. Within the " +
        "tower is a silver bell.\n");
    add_item(({"bell", "silver bell"}),
        "The bell appears to be made from mithril. It is polished to " +
        "a bright sheen.\n");
    add_item("staircase",
        "The staircase is made of stained oak. It is large " +
        "and leads downstairs.\n");
    add_cmd_item("bell", "ring", "@@ring_bell@@");

    add_exit(VALLEY_DIR + "u_cor02", "north");
    add_exit(VALLEY_DIR + "u_cor06", "south");
    add_exit(VALLEY_DIR + "u_cor04", "west");
    add_exit(VALLEY_DIR + "d_cor05", "down");
}

string ring_bell()
{
    return "There seems to be no way to ring the bell.\n";
}
