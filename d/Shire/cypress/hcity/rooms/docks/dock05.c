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
    set_vbfc_extra(dock_desc1);
    add_my_desc("To your east the docks continue on"+
        " for quite some time. To your west, the dock continues"+
        " on into the distance. Southeast of here, there appears"+
        " to be an old pier of some sort which "+
        "extends outwards into the harbor. The city"+
        " sprawls to your north.\n");

    
    add_exit(DOCK_DIR + "dock04", "west");
    add_exit(DOCK_DIR + "dock06", "east");

}