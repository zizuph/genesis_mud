/*
 * kob_lair_chief.c
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
 
    clone_object(DOORS + "chief_out")->move(this_object());

    add_prop(ROOM_I_LIGHT, 0);
    
    add_npc(NPC + "kobold_chieftain", 1, init_kobold);
    add_npc(NPC + "kobold_female", 5, init_kobold);
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
