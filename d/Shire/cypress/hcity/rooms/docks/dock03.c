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
    add_my_desc("To the east the docks continue on"+
        " for quite some time. To the west, the dock begins"+
        " to turn into a muddy path heading towards the "+
        "southwest. A fair distance away to the south by "+
        "southwest of here, the Empire's warf "+
        "extends outwards into the harbor. The city's most"+
        " notorious section lies in wait to the north.\n");

    
    add_exit(DOCK_DIR + "dock02", "west");
    add_exit(DOCK_DIR + "dock04", "east");

}