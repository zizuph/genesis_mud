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
    set_vbfc_extra(dock_desc2);
    add_my_desc("To the east the docks continue on"+
        " for quite some time. Westward, the dock begins"+
        " to turn into a muddy path to the southwest. "+
        "In the distance to the southwest of here, the "+
        "Empire's warf extends outwards into the harbor. "+
        "The city lies in wait to the north.\n");

    
    add_exit(DOCK_DIR + "dock03", "west");
    add_exit(DOCK_DIR + "dock05", "east");

}