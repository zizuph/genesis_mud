/*
 * dock in Sanctuary
 * By Tijgen 03OCT01
*/
 
#pragma strict_types
 
#include "local.h"

inherit DOCK_BASE;
 
void
create_dock_room()
{
    set_area("in southern");
    set_vbfc_extra(dock_desc1);
    add_my_desc(" Atrophying southwardly into the bay"+
		" a dock that has seen better times has begun its"+
		" slow fall towards the shallow water.  Northward"+
		" the city extends beyond the edges of sight. "+
		"Extending further to the east the housing gets"+
		" steadily better..\n");

    
    add_exit(DOCK_DIR + "dock08", "west");
    add_exit(DOCK_DIR + "dock14", "east");
	add_exit(DOCK_DIR + "dock10", "south");
}