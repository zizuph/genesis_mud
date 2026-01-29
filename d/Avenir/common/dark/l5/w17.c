// File name:    /d/Avenir/common/dark/l5/w17.c
// creator(s):   Farlong
// last update:  Cirion, May 1996 - added Ogres, cleaned up the area.
// purpose:      Tunnels in Level 5 of the Utterdark, containing Ogres and
//               other nasties.
inherit "/std/room";
#include <stdproperties.h>
#include "../dark.h"

void reset_crates()
{
    object *obs =  container_objects[DARK + "smis/mixed_crate"][3];
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
    set_short("smooth stone chamber");
    set_long("The smooth-cut stone tunnel ends"
	+" abruptly here.  It appears that the tunnel was headed somewhere"
	+" but the work was never completed.  The only"
	+" exit is back to the southeast.\n");

    add_exit(L5 + "w15", "southeast",0);
    add_prop(ROOM_I_LIGHT,0);
    IN

    add_object(DARK + "smis/mixed_crate");
	add_npc(MON + "phrynos");
}
