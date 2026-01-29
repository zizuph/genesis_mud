#pragma save_binary

inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "guild.h"
#include "/d/Rhovanion/defs.h"

void
create_room()
{
  set_short("Corridor");
  set_long("You stand in a corridor in the quarters of the Army of " +
    "Angmar. It continues north further into the guard quarters, " +
    "while the great fortress gates lie to the south. " +
    "A new archway leads off to the east.\n");
   
  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

  add_item(({"gates","gate"}), "These massive wooden gates are opened "+
                "almost all the time. Probably because "+
                "noone dares to attack this place.\n");
  
  add_item(({ "walls", "wall", "east wall", "eastern wall" }),
    "A new archway has been set into it!\n" +
    "There is a large sign above it.\n");
  add_item(({ "large sign", "sign" }), "The sign reads:\n\n" +
	"Soldiers' mess hall.\n");

  add_exit(THIS_DIR+"c2", "north");
  add_exit(THIS_DIR+"gates", "south");
  add_exit(THIS_DIR+"mess_hall", "east", "@@my_guild_member@@");
}

public int
my_guild_member()
{
    if (!TP->query_guild_member(GUILD_NAME))
    {
	write("You are not allowed in. You are not a soldier of the " +
	    "Army!\n");
	return 1;
    }
    return 0;
}