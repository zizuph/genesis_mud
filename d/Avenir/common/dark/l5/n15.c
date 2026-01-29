// File name:    /d/Avenir/common/dark/l5/n15.c
// creator(s):   Farlong
// last update:  Cirion, May 1996 - added Ogres, cleaned up the area.
// purpose:      Tunnels in Level 5 of the Utterdark, containing Ogres and
//               other nasties.
inherit "/std/room";
#include <stdproperties.h>
#include "../dark.h"

void reset_crates()
{
    object *obs =  container_objects[DARK + "smis/torch_crate"][3];
    obs->reset_placed_functions();
    obs->add_prop(CONT_I_CLOSED, 1);
}

void reset_room()
{
    cleanup_loot();
    reset_crates();
}

void
create_room()
{
    set_short("small chamber");
    set_long("This small side chamber looks as though it was once"
	+" used for storage.  The only way out is back into the"
	+" tunnel.\n");

    add_exit(L5 + "n13","southeast",0);
    add_prop(ROOM_I_LIGHT,0);
    IN

    add_object(DARK + "smis/torch_crate");
	add_npc(MON +"phrynos");
}
