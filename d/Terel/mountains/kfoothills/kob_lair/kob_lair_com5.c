/*
 * kob_lair_com5.c
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
 
    add_exit(KOB_LAIR_PATH + "kob_lair_com2", "north", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_com3", "northeast", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_com6", "east", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_com9", "southeast", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_com8", "south", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_com7", "southwest", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_com4", "west", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_com1", "northwest", 0);
    
    reset_room();

    add_npc(NPC + "kobold_male", 4, 0);
    add_npc(NPC + "kobold_female", 2, 0);
    add_npc(NPC + "kobold_child", 1, 0);
}
