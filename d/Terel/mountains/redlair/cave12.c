/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * cave12.c
 *
 * Red Dragon Lair
 * Tomas  -- Dec. 1999
 */

#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "redlair/cave_room";


object reddragon;

reset_room()
{
    if (!reddragon) 
    {
        reddragon=clone_object(MOUNTAIN_DIR + "redlair/monster/dragon");
        reddragon->move(this_object());
    }

}


/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    FIX_EUID;
    return ({MOUNTAIN_DIR + "redlair/monster/dragon"});
}


/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
        ::create_room();
    set_long("You are standing on a landbridge within a giant cavern. " +
       "A stream of molten lava pours from the ground draining into " +
       "a large pool below. The natural landbridge " +
       "leads over the pool to the middle of the cavern.\n");

    add_item(({"cavern"}),"The dome shaped cavern is enormous. A large " +
       "hole in the center of the ceiling allows fresh air to mix with the lava " +
       "bed causing steam pockets to rise.\n");
    
    add_item(({"molten lava","large pool","pool","lava"}),
       "The molten lava appears to be spewing from a fissure located " +
       "against the far wall. The lava slowly follows its way down " +
       "to a large collecting pool where it mixes with the cold air " +
       "from above hardening into slag. The lava keeps the room " +
       "just below boiling temperature. You seriously doubt you could " +
       "remain here for too much longer.\n");

    add_item(({"landbridge","bridge"}),"You are standing on what appears " +
       "to be a bridge formed by molten rock deposits or slag. It looks " +
       "quite sturdy.\n");

    
    add_exit(MOUNTAIN_DIR + "redlair/cave11", "west");

    reset_room();
}

/*
 * Function name: smell_desc
 * Description:   What does the air smell like here?
 * Returns:       The description of the smell
 */ 
public string
smell_desc()
{
    return "It smells like a sulfur furnace from hell in here!\n";
}


public string
touch_desc()
{
    return "You reach out to touch the walls of the cavern " +
       "but pull back your hand due to the extreme heat radiating " +
       "from the walls.\n";
}
