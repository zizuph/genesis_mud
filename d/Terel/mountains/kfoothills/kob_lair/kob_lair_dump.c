/*
 * kob_lair_dump.c
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
 
    set_long("A large dirty natural cave.  The cave is filled with " 
      + "rubbish and leftovers. The smell of rotting food is " 
      + "overbearing. A small tunnel leads back to the cavern to the " 
      + "west.\n"); 
    add_exit(KOB_LAIR_PATH + "kob_lair_a04", "west", 0);

    add_prop(ROOM_I_LIGHT, 0);
    
    add_item(({"rubbish", "rotting food", "food"}), "Rubbish and rotten " 
      + "food cover this cave floor.\n");
    
    add_npc(NPC + "giant_rat", 1, 0);
    add_npc(NPC + "large_rat", 6, 0);

    reset_room();
}

/*
 * Function name: reset_room
 * Description  : Resets the meat in this room if gone
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_room()
{
    if (!present("strange_meat"))
    {
        object meat = clone_object(KOB_LAIR_PATH + "obj/strange_meat");
        meat->set_heap_size(1);
        meat->move(this_object());
    }
}