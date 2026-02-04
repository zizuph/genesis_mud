/*
 * kob_lair_a07.c
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
 
    set_long("A small cave cul-de-sac with its opening to the north. A " 
      +  "few seats surround a small table in the middle of the cave.\n");
 
    add_exit(KOB_LAIR_PATH + "kob_lair_a05", "north", 0);

    add_prop(ROOM_I_LIGHT, 0);
    
    add_item(({"table"}), "A small table with tripodal legs.\n");
    
    add_item(({"seat", "seats", "stool", "stools"}), 
        "Three seats surround the table.\n");
    
    add_npc(NPC + "kobold_guard", 4, 0);
}