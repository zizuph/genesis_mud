/*
 * kob_lair_a10.c
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

    set_long("The crevasse continues east to west. Faint light streams " 
      + "in from the ends of the crevasse. To the west the crevasse " 
      + "opens up to a large cave intermittently lit by the red glow of "
      + "cooking fires. The crevasse extends to the east.\n");
    
    add_item(({"wall", "walls"}), "tall walls that meet together to form "
      + "the ceiling leading to the surface");
    
    add_item(({"crevasse"}), "The narrow crevasse continues to the west. "
     + "The walls of the crevasse angle up closing to narrow cracks.\n");

    add_item(({"cave", "large cave"}), "To the west a large cave opens " 
     + "up beyond the crevasse walls.  The glow of small piles of red "
     + "coals is faintly reflected off mounds of dirty oily furs.\n");

    add_item(({"fires", "cooking fires", "coals"}), "In the cave to the "
     + "west The glow of small piles of red coals is faintly reflected "
     + "off mounds of dirty oily furs.\n");

    add_item(({"furs", "oily furs", "mounds"}), "The mounds of dirty "
     + "oily furs reflect the reddish glow of the small piles of "
     + "coals.\n");
      
    add_exit(KOB_LAIR_PATH + "kob_lair_a09", "east", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_com6", "west", 0);
}
