/*
 * mouth.c
 * By Skippern
 */
#pragma strict_types

#include "../erech.h"

inherit E_STD + "path.c";
inherit "/lib/unique";

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
  set_long("You are inside a tunnel. The air feels very dens here. The " +
	   "tunnel continues northwards into the White Mountains. To the " +
	   "south you can see the faint light from the mouth of the " +
	   "tunnel.\n");

  tunnel_items();

  add_prop(ROOM_I_LIGHT, -2);
  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_S_DARK_LONG, DARK_ROOM_LONG);
  add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_TUNNEL);
  add_prop(ROOM_I_NO_ALLOW_STEED, 1);

  nr = 2;
  ghost = allocate(nr);
  reset_room();

  add_exit(E_PATH + "by_mouth.c", "north", 0, 2, 0);
  add_exit(E_VALE + "D1.c", "south", 0, 2, 0);
}

public void
reset_room()
{
    reset_ghosts(ghost, nr);

    ob = clone_unique(E_NPC + "ghost2");
    ob->move(this_object());
}

