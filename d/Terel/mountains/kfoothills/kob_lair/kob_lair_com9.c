/*
 * kob_lair_com9.c
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
    
    set_short("Kobold common area");
 
    add_exit(KOB_LAIR_PATH + "kob_lair_com6", "north", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_com8", "west", 0);
    add_exit(KOB_LAIR_PATH + "kob_lair_com5", "northwest", 0);
    
    add_npc(NPC + "kobold_male", 2, 0);
    add_npc(NPC + "kobold_female", 3, 0);
    add_npc(NPC + "kobold_child", 2, 0);
    
    reset_room();
    //add_object(KOB_LAIR_PATH + "obj/strange_meat", 2, 0); 

}

/*
 * Function name: reset_room
 * Description  : Resets the rooms trap and add meat if not present
 * Arguments    : n/a
 * Returns      : n/a
 */
void
reset_room()
{
    if (!present("strange_meat"))
    {
        object meat = clone_object(KOB_LAIR_PATH + "obj/strange_meat");
        meat->set_heap_size(2);
        meat->move(this_object());
    }
}
