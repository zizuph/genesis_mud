/*
 * kob_lair_a05.c
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
 
    set_long("Western end of a large cavern. Soft dirt covers most " 
      + "of the cave with occasional outcrops of bare rock. The walls "
      + "here are uneven with large cracks. Small rocks litter the "
      + "floor. Smaller tunnels lead off to the south and the northwest." 
      + "\n");
      
    add_item(({"dirt", "Soft dirt", "floor"}), "Soft dirt covers most " 
      + "of the floor with bare rock outcrops dotting it.\n");

    add_item(({"rock"}), "You are surrounded by rock as you are in a " 
      + "cave.\n");
      
    add_item(({"rock outcrops", "outcrops", "bare rock"}), 
      "Bulges of bare rock rise from the ground dotting the " 
      + "dirt floor.\n");
 
    add_exit(KOB_LAIR_PATH + "kob_lair_a03", "east", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_a07", "south", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_a06", "northwest", 0);

    add_prop(ROOM_I_LIGHT, 0);
}
