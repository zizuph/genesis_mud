// File name:    /d/Avenir/common/dark/l5/n18.c
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
    set_short("small chamber");
    set_long("This small side chamber looks as though it was once"
	+" used for storage.  The only way out is back into the"
	+" tunnel.\n");

    add_exit(L5 + "n17","southwest",0);
    add_prop(ROOM_I_LIGHT,0);
    IN
	add_npc(MON +"phrynos", 2);
}
