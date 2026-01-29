/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */

inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"

void
create_room()
{
    set_short("Store room");
    set_long("This is the main armory room of the Army. Only privileged " +
        "members were allowed here. Those permitted here were given " +
        "access to the best armours and weapons the Army had to offer. " +
        "The collapsed ceiling now fills the room with rubble, covering " +
        "everything in a thick film of dust.\n");
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_exit(NEW_ANGMAR + "priv", "west");
}
 
