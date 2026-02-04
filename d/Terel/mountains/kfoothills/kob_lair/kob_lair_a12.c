/*
 * kob_lair_a12.c
 *
 * Britanica 160322
 */
#pragma strict_types

#include "include/cave_defs.h"
#include "stdproperties.h"

inherit KOB_LAIR_PATH + "default_kob_lair";

void init_kobold(object kobold);

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
 
    add_exit(KOB_LAIR_PATH + "kob_lair_a11", "east", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_a13", "southwest", 
      "@@check_guarded");

    add_prop(ROOM_I_LIGHT, 0);
    
    add_npc(NPC + "kobold_guard", 4, init_kobold);
}

/*
 * Function name: init_kobold
 * Description  : initialize kobolds to not move
 * Arguments    : n/a
 * Returns      : n/a
 */
void
init_kobold(object kobold)
{
    kobold->set_random_move(0);
}

/*
 * Function name: check_guard
 * Description  : check if exit can be used.
 * Arguments    : n/a
 * Returns      : 1 for block, 0 for less pass
 */
public int
check_guarded()
{
    if (present("kobold_guard") &&
         !this_player()->query_wiz_level())
    {
        write("The kobold guard blocks your way.\n");
        return 1;
    }
    return 0;
}