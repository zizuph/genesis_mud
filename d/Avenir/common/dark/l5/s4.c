// File name:    /d/Avenir/common/dark/l5/s4.c
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
    set_short("rough-cut tunnel");
    set_long("You stand in a rough-cut tunnel which continues to"
	+" the east and west.  To the south is a small chamber.\n");

    add_exit(L5 + "s3","west",0);
    add_exit(L5 + "s5","east",0);
    add_exit(L5 + "s15","south",0);
    add_prop(ROOM_I_LIGHT,0);
    IN
}
