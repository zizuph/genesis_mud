/*
 * Angmar guild rooms
 * opened as nothing but a shell for old times
 * Finwe, October 2002
 */
inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"

create_room()
{
  set_short("The post office");
/*
  set_long("This is the once proud post office of Angmar's Army. Here " +
    "they would collect the letters from all over the world. Now, it " +
    "has fallen into disrepair and no mail comes or is sent out from here.\n");
*/
    set_long("Once the post office of the Army, this room is ruined " +
        "almost beyond recognition. Soldiers were able to communicate " +
        "with their allies and others here. Now, broken coops where " +
        "pigeons were once kept litter the ground as well as shredded " +
        "messages. A layer of dust covers everything, and cobwebs " +
        "stretch across the debris.\n");
    
  add_prop(ROOM_I_INSIDE, 1);

  add_exit(NEW_ANGMAR + "c1", "east");
}
