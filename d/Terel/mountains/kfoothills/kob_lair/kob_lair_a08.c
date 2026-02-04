/*
 * kob_lair_a08.c
 *
 * Britanica 160322
 */
#pragma strict_types

#include "include/cave_defs.h"
#include "stdproperties.h"

inherit KOB_LAIR_PATH + "default_kob_lair";

/*
 * Function name: create_room
 * Description  : constructor.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void 
create_room()
{
    ::create_room();
    
    set_long("The crevasse continues east to west. Soft light trickles " 
      + "in through occasional cracks in the ceiling. Along the southern "
      + "wall a solid granite rock floor gives way to dirt along the " 
      + "northern wall.\n");

    add_item(({"wall", "walls"}), "tall walls that come together in " 
      + "small cracks leading to the surface");
    
    add_item(({"cracks", "light"}), "Light trickles in through small "
      + "cracks in the ceiling high above you.\n");

    add_item(({"crevasse"}), "The narrow crevasse continues to the west. "
      + "The walls of the crevasse angle up closing to narrow cracks.\n");

    add_item(({"dirt", "floor", "granite"}), "The floor is bare granite "
      + "rock on the south side of the passage and a soft dirt on the " 
      + "northern side.\n");
 
    add_exit(KOB_LAIR_PATH + "kob_lair_a06", "east", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_a09", "west", 0);
}
