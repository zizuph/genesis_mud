/**
 * Room in the Archer Guild
 *
 * Navarre November 23th 2007.
 */
    
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../guild.h"
inherit "/d/Krynn/std/room";

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
             "useful to the other elves. This room is exclusively " +
             "for the elite archers, where they may store delicate items that requires great skills to master.\n");
    
    set_short("You are standing in the rack room of the elite archers");    

    add_item(({"hut", "camouflaged hut", "tree", "tree trunk", "gigantic tree trunk"}),
               "The hut is build around the large tree trunk, " +
               "which has a large opening into it. This opening is used as a storage facility.\n");
    add_item(({"room", "area"}), long());
    add_item("equipment", "Equipment can be stored in the racks infront of you.\n");
    
    INSIDE;
    add_exit(ROOMS + "hut_rack", "south", 0);

    // Clone the racks
    room_add_object(GUILD_OBJ + "rack_herb2", 1, 0); 
    room_add_object(GUILD_OBJ + "rack_misc2", 1, 0);
    room_add_object(GUILD_OBJ + "rack_armour2", 1, 0);
    room_add_object(GUILD_OBJ + "rack_bow2", 1, 0); 
    reset_room();
}

