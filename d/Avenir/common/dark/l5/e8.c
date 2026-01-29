// File name:    /d/Avenir/common/dark/l5/e8.c
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
    set_long("The roof of this rickety tunnel is held up by wooden beams."
	+" it appears that the construction here was never fully finished."
	+"  The tunnel leads from here to the east and west.\n");

    add_exit(L5 + "e7","east",0,DUST);
    add_exit(L5 + "e9","west",0,DUST);
    add_prop(ROOM_I_LIGHT,0);
    IN
}
