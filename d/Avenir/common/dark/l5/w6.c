// File name:    /d/Avenir/common/dark/l5/w6.c
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
    set_short("smooth stone chamber");
    set_long("This chamber looks like it was made with a purpose."
	+" Three tunnels extend away from it, into deep darkness. It"
    +"stinks of ogres here.\n");

    add_exit(L5 + "w5","northwest",0);
    add_exit(L5 + "w7","northeast", 0);
    add_exit(L5 + "w15","west",0);
    add_prop(ROOM_I_LIGHT,0);
    IN
}
