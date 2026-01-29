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
    set_area("in southern");
    set_vbfc_extra(dock_desc2);
    add_my_desc("To the east the docks continue on"+
        " for quite some time. Towards the west, the dock continues"+
        " on into the distance. Southeast of here, there appears"+
        " to be a decaying pier of some sort which "+
        "extends outwards into the harbor. The city"+
        " extends to the north.\n");

    
    add_exit(DOCK_DIR + "dock05", "west");
    add_exit(DOCK_DIR + "dock07", "east");

}