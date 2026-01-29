// File name:    /d/Avenir/common/dark/l5/n7.c
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
    set_short("fork in tunnel");
    set_long("The rough-cut tunnel forks here, heading to the"
	+" northeast, northwest and south.\n");

    add_exit(L5 + "n6","northeast",0);
    add_exit(L5 + "n11","northwest",0);
    add_exit(L5 + "n8","south",0);
    add_prop(ROOM_I_LIGHT,0);
    IN
}
