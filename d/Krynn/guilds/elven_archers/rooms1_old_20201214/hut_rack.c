/**
 * Room in the Archer Guild
 *
 * Navarre November 23th 2007.
 */
    
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../guild.h"
inherit "/d/Krynn/std/room";

/**
 * This function helps decide whether the player can go north.
 * The elite racks are to the north, and it is meant for only
 * the OCC members to have access to those racks.
 *
 * @return 0 if he can enter, 1 otherwise.
 */
int
elite_check()
{

    if(this_player()->query_guild_name_occ() == "Ansalon Elvish Archers")
    {
        return 0;
    }

    write("Strong elven magic prevents you from going in that direction! " +
          "That room is only for the elite archers.\n");
    return 1;
}
        
void
reset_krynn_room()
{
}

void
create_krynn_room()
{

    set_long("You are standing inside of a gigantic tree trunk. It appears that it has " +
             "been magically formed into a large round room. The area is well lit, well " +
             "protected, and dry.  This makes it the perfect place to store equipment. " +
             "There are racks here in which you could store any equipment that may be " +
             "useful to the other elves. Straight ahead from here is a room exclusively " +
             "for the elite archers, where they may store delicate that requires great skills to master.\n");
    
    set_short("You are standing in the common rack room");    

    add_item(({"hut", "camouflaged hut", "tree", "tree trunk", "gigantic tree trunk"}),
               "The hut is build around the large tree trunk, " +
               "which has a large opening into it. This opening is used as a storage facility.\n");
    add_item(({"room", "area"}), long());
    add_item("equipment", "Equipment can be stored in the racks infront of you.\n");
    
    INSIDE;
    add_exit(ROOMS + "hut_rack2", "north", elite_check);
    add_exit(ROOMS + "hut_postoffice", "south", 0);

    // Clone the racks
    room_add_object(GUILD_OBJ + "rack_herb", 1, 0); 
    room_add_object(GUILD_OBJ + "rack_misc", 1, 0);
    room_add_object(GUILD_OBJ + "rack_armour", 1, 0);
    room_add_object(GUILD_OBJ + "rack_bow", 1, 0); 
    reset_room();
}

