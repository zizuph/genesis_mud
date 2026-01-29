/* /d/Raumdor/common/beach/bountiful/bounty_gangway.c
 *
 * Room at the ship Bountiful.
 *
 * Nerull, 2021.
 *
 */

#include <stdproperties.h>
#include "defs.h";
inherit BEACH_ROOM;


/*
 * Function name: block_player
 * Description  : If a crew member is present, blocks entrance.
 */
public int
block_player()
{
    int avgsize;
    
    avgsize = this_player()->query_average();
    
    if (present("_gangway_ghast"))
    {       
        write("A crewman blocks you from "
        +"entering the deck of the Bountiful!\n");

        return 1;
    }
     
    if (avgsize < 190)
    {
        write("A powerful ward prevents all but the most "
        +"mythical of heroes from boarding its deck.\n");
        
        return 1;
    }
    
    if(this_player()->test_bit("Raumdor", 3, 7))
    {
        return 0;
    }
    
    
    write("A powerful ward prevents prevents you from boarding its deck.\n");
        

    return 1;
}


/*
 * Function name: create_mar_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_room()
{
    ::create_room();
    set_short("On the gangway of Bountiful");
    
    set_long("This gangway is made of planks securely nailed "
    +"together with a rope hold on the right side. Though "
    +"wide enough for several persons, "
    +"this gangway is not the most sturdy and creeks underfoot.\n");

    seteuid(getuid());
    
    add_prop(ROOM_I_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_TELEPORT_FROM, 1);


    add_item( ({"planks", "gangway"}), "rotting planks make "
    +"up this gangway. Nailed together and wrapped in rope to "
    +"secure them to one another. While they seem as though "
    +"they should have collapsed long ago, they are incredibly "
    +"sturdy as if some unnatural entity or force maintains "
    +"their strength.\n");
    
    remove_item("carvings");
    remove_item("blocks");
    remove_item("stone blocks");

    add_exit(BEACH_DIR + "bountiful/bounty_deck",   "up", block_player);
    add_exit(BEACH_DIR + "beach2",   "leave");
    
    //add_npc("/d/Raumdor/common/beach/bountiful/npc/bount_gangway_ghast", 1);
    
    reset_room();
}


/*
 * Function name: reset_room()
 * Description  : Resets the room.
 */
void
reset_room()
{
}

