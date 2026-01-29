/*
 * dock in Sanctuary
 * By Tijgen 01JUL01 
 */
 
#pragma strict_types
 
#include "local.h"

inherit DOCK_BASE;
 
void
create_dock_room()
{
    set_area("in southwestern");
    set_vbfc_extra(dock_desc1);
    add_my_desc("To the southwest there lies a community of"+
        " fishermen, and eastward the docks continue on"+
        " for quite some time. The Street of Smells leads into"+
        " the city to the north. The empires wharf lie to the south.\n");

    add_exit(DOCK_DIR + "ew01", "south");
    add_exit(DOCK_DIR + "dock02", "east");
    add_exit(FISHROW_DIR + "fr01", "southwest");
    add_exit(WEST_DIR + "SOS01", "north");
}