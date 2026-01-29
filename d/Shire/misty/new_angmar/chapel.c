/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */

inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <stdproperties.h>

void
create_shire_room()
{
    object board;

    set_short("Sacred room");
/*
    set_long("This is the once sacred room of the Angmar Army. Many " +
        "trophies from the old wars gathered by these warriors who " +
        "once walked these halls line the walls. Though most of the " +
        "things here look cruel, the room still emits an aura. Here, " +
        "new soldiers would join or leave the Army.\n");
*/
    set_long("This room is at the end of the hall. A thick layer of " +
        "dust covers everything. Dark trophies line the walls, and " +
        "some lie fallen to the ground. An old leather book miraculously " +
        "survived the wanton destruction. It sits in a corner of the " +
        "room; a ripped cover and torn pages are all that remain of it. " +
        "However, it looks like it can still be read if care is used.\n");

    room_add_object(NEW_ANGMAR + "book");
    
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_exit(NEW_ANGMAR + "train", "south");

}

