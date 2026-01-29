/*
 * north1.c
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
  set_long("You are inside a tunnel. To the north the air feels lighter " +
	   "and to the southeast it continues deeper into the White " +
	   "Mountains.\n");

  tunnel_items();

  add_prop(ROOM_I_LIGHT, -2);
  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_S_DARK_LONG, DARK_ROOM_LONG);
  add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_TUNNEL);

  nr = 2;
  ghost = allocate(nr);
  reset_room();

  add_exit(E_PATH + "by_gate.c", "north", "@@pass", 2, 0);
  add_exit(E_PATH + "north2.c", "southeast", "@@pass", 2, 0);
}

public void
reset_room()
{
    reset_ghosts(ghost, nr);
}



