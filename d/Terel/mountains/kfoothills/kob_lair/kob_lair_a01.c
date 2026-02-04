/*
 * kob_lair_a01.c
 *
 * Britanica 160322
 */
#pragma strict_types

#include "include/cave_defs.h"

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
 
    set_long("Light streaming through the small cave entry lightly " 
      + "illuminates the interior of the cave. A tunnel continues to " 
      + "the south blanketed in darkness. Soft dirt covers most of floor "
      + "with bare rock outcrops dotting the ground. The ceiling of the " 
      + "cave is an single slab of solid rock which angles down to also " 
      + "form the eastern wall. The western wall appears very cracked " 
      + "and rises vertically.\n");
       
    add_item(({"ceiling", "east wall", "slab", "single slab"}), 
      "A single slab of angled stoned which comprises both the east " 
        + "wall and the ceiling.\n");

    add_item(({"dirt", "Soft dirt", "floor"}), "Soft dirt covers most " 
      + "of the floor with bare rock outcrops dotting it.\n");

    add_item(({"rock"}), "You are surrounded by rock as you are in a " 
      + "cave.\n");
      
    add_item(({"rock outcrops", "outcrops", "bare rock"}), 
      "Bulges of bare rock rise from the ground dotting the dirt " 
      + "floor.\n");
    
    add_exit(KOB_LAIR_EXIT, "out", 0);
    add_exit(KOB_LAIR_EXIT, "north", 0, 1, 1);
    add_exit(KOB_LAIR_PATH + "kob_lair_a02", "south", 0);
    
    add_npc(NPC + "kobold_guard", 2, init_kobold);
    add_npc(NPC + "kobold_male", 4, init_kobold);
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
