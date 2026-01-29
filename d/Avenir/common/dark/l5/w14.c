// File name:    /d/Avenir/common/dark/l5/w14.c
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
	+" made with a purpose.  There is a side-passage to the northwest"
	+" and other than that the tunnel extends to the east into"
	+"darkness and stench.\n");

    add_exit(L5 + "w13","west",0);
    add_exit(L5 + "w15","east",0);
    add_exit(L5 + "w16","northwest",0);

    add_prop(ROOM_I_LIGHT,0);
    IN
}
