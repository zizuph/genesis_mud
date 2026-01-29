/* Created 29/9/98 by Bishop, of Calia. This is a room in the
gnome village that doesn't have a name, yet;) */

inherit "/std/room";

#include <defs.h>
#include <stdproperties.h>

create_room()
{
    set_short("Armoury in gnome village");
    set_long("Insert long descrip of the room here.\n");
    add_prop(ROOM_I_HIDE, 70);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(VILLAGE+"village_path11","north",0,1);
}
