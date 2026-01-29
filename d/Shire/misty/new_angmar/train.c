/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */

inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"

void
create_shire_room()
{

    set_short("training room");
/*
    set_long("This is the once proud training room for Angmar's army. " +
        "Many warriors use to practice their skills over and over " +
        "again here trying to achieve perfection. Now, it is an empty " +
        "room collecting dust and cobwebs.\n");
*/
    set_long("Gouges in the walls, floor, and ceiling are witness that " +
        "this training room once echoed with the sounds of mock battles " +
        "as soldiers practiced their skills before going out on campaigns. " +
        "Little remains of the training sessions that took place here, " +
        "other than broken training equipment, dummies, broken weapons " +
        "and armours that lie scattered around the room. Somehow, " +
        "though, a feeling of serene peace still permeates the room.\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_exit(NEW_ANGMAR + "chapel", "north");
    add_exit(NEW_ANGMAR + "start", "west");
    add_exit(NEW_ANGMAR + "c1", "south");
    add_exit(NEW_ANGMAR + "priv", "east");

}
