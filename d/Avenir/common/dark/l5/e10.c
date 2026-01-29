// File name:    /d/Avenir/common/dark/l5/e10.c
// creator(s):   Farlong
// last update:  Cirion, May 1996 - added Ogres, cleaned up the area.
//               Lilith Nov 1996 - made compatible with SMIS
// purpose:      Tunnels in Level 5 of the Utterdark, containing Ogres and
//               other nasties.
inherit "/std/room";

#include <stdproperties.h>
#include "../dark.h"

void reset_crates()
{
    object *obs = filter(all_inventory(this_object()), &->id("coffer"));
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
    set_short("rickety tunnel");
    set_long("The roof of this rickety tunnel is held up by wooden beams."
	+" it appears that the construction here was never fully finished."
	+"  The tunnel leads from here to the northeast and south.\n");

    add_exit(L5 +"e9","northeast",0,DUST);
    add_exit(L5 +"e11","south",0,DUST);

    add_prop(ROOM_I_LIGHT,0);
    IN

    add_object(DARK + "smis/torch_crate");
}
