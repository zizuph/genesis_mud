// File name:    /d/Avenir/common/dark/l5/w9.c
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
    set_short("smooth stone passage");
    set_long("This smooth-cut stone passage looks like it was"
	+ " made with a purpose. It continues running east and west"
    +"into deep darkness and the ovewhelming stench of ogres.\n");

    add_exit(L5 + "w8", "west", 0);
	add_exit(L5 + "s14", "east", 0);
    add_prop(ROOM_I_LIGHT, 0);
    IN
}
