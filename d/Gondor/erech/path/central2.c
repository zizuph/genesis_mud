/*
 * central2.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit E_STD + "path.c";

#include <stdproperties.h>

#include TERRAIN_TYPES

/* Prototypes */
public void      create_gondor();
public void      reset_room();

/* Global variables */
object ob;
object *ghost;
int    nr;

/*
 * Function name:    create_gondor()
 * Definition   :    Creates the room.
 */
public void
create_gondor()
{
  set_short("Inside a tunnel.");
  set_long("You are inside a tunnel. The air feels very dense here. You " +
	   "are in the heart of the White Mountains.\n");

  tunnel_items();

  add_prop(ROOM_I_LIGHT, -2);
  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_S_DARK_LONG, DARK_ROOM_LONG);
  add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_TUNNEL);

  nr = 3;
  ghost = allocate(nr);
  reset_room();

  add_exit(E_PATH + "central1.c", "northwest", "@@pass", 2, 0);
  add_exit(E_PATH + "central3.c", "east", "@@pass", 2, 0);

}

public void
reset_room()
{
    reset_ghosts(ghost, nr);
}
