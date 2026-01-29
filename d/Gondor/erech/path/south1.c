/*
 * south1.c
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
  set_long("You are inside a tunnel. The air feels very dens here. The " +
	   "tunnel continues northwest deeper into the White Mountains.\n");

  tunnel_items();

  add_prop(ROOM_I_LIGHT, -2);
  add_prop(ROOM_I_INSIDE, 1);
  add_prop(ROOM_S_DARK_LONG, DARK_ROOM_LONG);
  add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_ERECH_TUNNEL);

  nr = 4;
  ghost = allocate(nr);
  reset_room();

  add_exit(E_PATH + "central3.c", "northwest", "@@dis_test", 2, 0);
  add_exit(E_PATH + "south2.c", "south", "@@pass", 2, 0);
}

public void
reset_room()
{
  reset_ghosts(ghost, nr);
}

/*
 * Function name:    dis_test()
 * Description  :    Tests if the players are brave enough to pass the exit.
 * Returns      :    0 = Success.
 *                   1 = Failure.
 */
int
dis_test()
{
    int dis = this_player()->query_stat(5);
    if (dis < 35 )
    {
        write(NO_DIS);
	return 1;
    }
    return 0;
}
