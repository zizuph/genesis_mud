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
    add_my_desc(" These docks have seen better days. "+
        "Everywhere are signs of weathering and age are "+
        "apparent. There are few merchant ships here, and "+
        "many small fishing vessels. The old pier to the "+
        "south lies in disuse and to the north lies a teaming "+
        "city. Westward the harbor area extends for some "+
        "distance and to the east are small boats "+
        "unloading fish at a small pier that extendes into "+
        "the shallows of the harbor.\n");

    
    add_exit(DOCK_DIR + "dock07", "west");
    add_exit(DOCK_DIR + "dock09", "east");

}