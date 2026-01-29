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
    add_my_desc("In the distance towards southwest there "+
        "lies a community of fishermen, and to the east "+
        "the docks continue on for quite some time. "+
        "Westward, the road begins to turn into a muddy "+
        " path heading to the southwest. A distance away "+
        "to the south of here, the Empire's warf extends outwards "+
        "into the harbor. The city's more shadowy section "+
        "lies to your north.\n");

    
    add_exit(DOCK_DIR + "dock01", "west");
    add_exit(DOCK_DIR + "dock03", "east");

}