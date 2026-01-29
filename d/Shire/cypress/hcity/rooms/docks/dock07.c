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
    add_my_desc("The old pier stands in atrophy to the south"+
        "east. The city looms omniously to the north. To the "+
        "west the harbor area extends for some distance before"+
        " turning into a muddy path heading "+
        " to the southwest. Off to the east the vaguely outline"+
        " of another pier extends into the shallows of the "+
        "harbor.\n");

    
    add_exit(DOCK_DIR + "dock06", "west");
    add_exit(DOCK_DIR + "dock08", "east");

}