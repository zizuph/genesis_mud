/*
 * Downstairs corridor
 * By Finwe, February 1998
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit HOUSE_IN_BASE;
 
void
create_house_room()
{
    set_short("A downstairs corridor outside the kitchen");
    set_long("The corridor takes a sharp turn here. One end " +
        "heads north and the other end heads east. South of " +
        "you is the famous kitchen of Imladris. Wonderful smells " +
        "of delicious foods waft past you, making your " +
        "mouth water.\n");
 
    add_item(({"pillars", "square pillars", "square wooden pillars"}),
        "The pillars are carved from thick trees. They are squared " +
        "and are set into the walls. The pillars are expertly " +
        "decorated with carved leaves.\n");
 
    add_exit(VALLEY_DIR + "d_cor04", "north");
    add_exit(VALLEY_DIR + "kitchen", "south");
    add_exit(VALLEY_DIR + "d_cor08", "east");
}
