/*
    A nursery. Mortricia 920912
 */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Terel/common/terel_defs.h"

#define BS(message)    break_string(message, 70)
#define TP             this_player()
#define TO             this_object()

void
create_room()
{
    set_short("Nursery");
    set_long(BS("It's a very basic room as you can see.\n"));

    add_prop(ROOM_I_INSIDE, 1);
}
