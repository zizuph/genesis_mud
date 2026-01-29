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
create_room()
{
  set_short("Corridor");
  set_long("You stand in a deserted corridor in the quarters of the " +
        "Army of Angmar. It continues north further into the guard " +
        "quarters, while the great fortress gates are to the south. " +
        "An archway leads off to the east. Dust and cobwebs cover " +
        "everything present.\n");
   
  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

  add_item(({"gates","gate"}), "These massive wooden gates are opened "+
                "almost all the time. Probably because "+
                "no one dares to attack this place.\n");
  
  add_item(({ "walls", "wall", "east wall", "eastern wall" }),
    "An archway has been set into it!\n" +
    "A large sign hangs above it, lopsided and swinging in the breeze..\n");
  add_item(({ "large sign", "sign" }), "The sign reads:\n\n" +
	"Soldiers' mess hall.\n");

  add_exit(NEW_ANGMAR + "c2", "north");
  add_exit(NEW_ANGMAR + "gates", "south");
  add_exit(NEW_ANGMAR + "mess_hall", "east");
}
