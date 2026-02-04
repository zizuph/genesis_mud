/*
 * kob_lair_a13.c
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
    set_long("The natural cave tunnel ends with a door leading to the " 
      + "west, the walls being tool cut leading to the door. The other "
      + "time smoothed walls have several cracks and ledges in them. "
      + "A soft dirt covers the floor."
      + "\n");
 
    add_exit(KOB_LAIR_PATH + "kob_lair_a12", "northeast", 0);
    
    clone_object(DOORS + "chief_in")->move(this_object());

    add_prop(ROOM_I_LIGHT, 0);
    
    reset_room();
}

