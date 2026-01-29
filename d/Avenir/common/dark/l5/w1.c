// File name:    /d/Avenir/common/dark/l5/w1.c
// creator(s):   Farlong
// last update:  Cirion, May 1996 - added Ogres, cleaned up the area.
// purpose:      Tunnels in Level 5 of the Utterdark, containing Ogres and
//               other nasties.
inherit "/std/room";
#include <stdproperties.h>
#include "../dark.h"

void reset_crates()
{
    object *obs =  container_objects[DARK + "smis/tools_crate"][3];
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
    set_short("smooth stone passage");
    set_long("This smooth-cut stone passage looks like it was"
	+" made with a purpose.  It extends for as far as you can see"
	+" without side passages or other exits."
	+" East of here is a large circular chamber.\n");

    add_exit(L5 + "center","east",0);
    add_exit(L5 + "w2","southwest",0);
    add_prop(ROOM_I_LIGHT,0);
    IN

    add_object(DARK + "smis/tools_crate");
}
