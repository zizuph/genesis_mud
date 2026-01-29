/*
 *  /d/Emerald/common/guild/aod/rooms/sph_officer.c
 *
 *  This is the Officers Quarters for the guild member who has the
 *  highest rate of skulls collected per hour. It mostly inherits
 *  the functionality from its sister room. See the code at:
 *
 *      /d/Emerald/common/guild/aod/rooms/num_officer.c
 *
 *  Created January 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit AOD_ROOM_DIR + "num_officer";

/* prototypes */
public void        create_cave_room();
public void        init();

/* definitions */
#define    CHAIR_NAME      "bone pile"


/*
 * Function name:        create_cave_room
 * Description  :        set up the room
 */
public void
create_cave_room()
{
    add_name("_sph_chamber");
    add_chair(CHAIR_NAME, "[down] [on] [the] [cozy]"
      + " [looking] [bone] [love] 'pile' / 'nest' / 'bed'", 2);

    set_officer(SPH_OFFICER);
    set_officer_short(SPH_OFFICER_SHORT);

    set_up_officer_room();
    add_spike("sph_officer");
    add_exit("magma", "east", check_sitting, 1, 0);

    setuid();
    seteuid(getuid());
} /* create_cave_room */


/*
 * Function name:        init
 * Description  :        init the room chairs
 */
public void
init()
{
    ::init();

    init_room_chairs();
} /* init */