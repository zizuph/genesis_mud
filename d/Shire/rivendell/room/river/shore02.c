/*
 * Shore of river Bruinen
 * By Finwe, August 1998
 */
 
#pragma strict_types
 
#include "local.h"
 
inherit SHORE_BASE;
 
void
create_shore_room()
{
    set_vbfc_extra(shore_desc);

    add_exit(RIVER_DIR +   "shore03", "north",0,4);
    add_exit(RIVER_DIR +   "shore01", "south",0,4);
    add_exit(TROLLSH_DIR + "mpath1",  "west",0,4);
}

