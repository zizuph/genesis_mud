// File name:    /d/Avenir/common/dark/l5/e11.c
// creator(s):   Farlong
// last update:  Cirion, May 1996 - added Ogres, cleaned up the area.
// purpose:      Tunnels in Level 5 of the Utterdark, containing Ogres and
//               other nasties.
// note:         
// bug(s):       
// to-do:        
// revision:     
inherit "/std/room";

#include <stdproperties.h>
#include "../dark.h"

void reset_room()
{
    cleanup_loot();
}

void
create_room()
{
    set_short("rickety tunnel");
    set_long("The rickety tunnel forks here, with branches"
	+" heading off to the north and southeast.  To the south,"
        +" it joins a large, rough-cut tunnel.\n");

    add_exit(L5 + "e10","north",0,DUST);
    add_exit(L5 + "e12","southeast",0,DUST);
    add_exit(L5 + "n3","south",0,DUST);
    add_prop(ROOM_I_LIGHT,0);
    IN
}
