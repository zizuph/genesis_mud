/*
 * kob_lair_a04.c
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
    
    set_long("Eastern end of a large cavern. Soft dirt covers most " 
      + "of the cave with occasional outcrops of bare rock. The walls "
      + "here are uneven with large cracks. Small rocks litter the "
      + "floor. A small tunnel leads deeper into the cave system to "
      + "the east.\n");
 
    add_exit(KOB_LAIR_PATH + "kob_lair_dump", "east", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_a03", "west", 0);

    add_prop(ROOM_I_LIGHT, 0);
}
