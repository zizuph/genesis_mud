/*
 * kob_lair_a06.c
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
    
    set_long("Light trickles in through occasional cracks in the ceiling "
      + "leading to the surface. You are at the eastern end of a narrow "
      + "crevasse that continues to the west. A small dark tunnel leads " 
      + "off to the southwest.\n");
    
    add_exit(KOB_LAIR_PATH + "kob_lair_a05", "southeast", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_a08", "west", 0);

    add_item(({"cracks", "light"}), "Light trickles in through small "
      + "cracks in the ceiling high above you.\n");

    add_item(({"crevasse"}), "The narrow crevasse continues to the west. "
      + "The walls of the crevasse angle up closing to narrow cracks.\n");
      
    add_item(({"walls"}), "The walls of the crevasse angle up closing to "
      + "narrow cracks.\n");
}
