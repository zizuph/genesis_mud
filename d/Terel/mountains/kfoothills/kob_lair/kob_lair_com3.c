/*
 * kob_lair_com3.c
 *
 * Britanica 160322
 */
#pragma strict_types

#include "include/cave_defs.h"

inherit KOB_LAIR_PATH + "default_kob_common";

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
 
    add_exit(KOB_LAIR_PATH + "kob_lair_com6", "south", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_com5", "southwest", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_com2", "west", 0);
    
    add_npc(NPC + "kobold_male", 4, 0);
    add_npc(NPC + "kobold_female", 2, 0);
    add_npc(NPC + "kobold_child", 1, 0);
}
