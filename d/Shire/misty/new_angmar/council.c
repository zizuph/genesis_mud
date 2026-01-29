/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */

inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <stdproperties.h>

void create_room()
{
    
    set_short("Council room of Army of Angmar");

    set_long("This is the council room of Army of Angmar. It is dusty " +
        "and a collapsed chamber where the Council handed out its " +
        "judgements and punishments to the soldiers. It is a large " +
        "room and was once ornate. Overturned chairs and desks litter " +
        "the room. Buried under the rubble is a broken bulletin board.\n");

    add_item(({"board", "bulletin board"}),
        "The board is twisted and broken. It is buried and unreadable. " +
        "Presumablely, it once contained notes council posted for " +
        "its own uses.\n");
    
    add_exit(NEW_ANGMAR + "vote","south");
    

    
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */


    
}

