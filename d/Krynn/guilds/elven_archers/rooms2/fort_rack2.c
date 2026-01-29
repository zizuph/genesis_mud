/**
 * Room in the Archer Guild
 *
 * Navarre November 23th 2007.
 *
 * Updated by Vitwitch, Nov 2020.
 */
    
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

#include "/d/Krynn/common/defs.h"
#include "../guild.h"

inherit "/d/Krynn/guilds/elven_archers/rooms2/baseroom_fort";

#define GUILDROOMS "/d/Krynn/guilds/elven_archers/rooms2/"
#define VIEWDEST "/d/Krynn/qualinesti/elf_camp/camp9"

void
reset_krynn_room()
{
}

void
create_krynn_room()
{

    set_short("An elite rack room in a treetop fortress");

    set_long(gBlurbPfx +
             " A golden gleaming rack fills this room entirely. "+
             "This room is well protected, well lit, warm and dry; " +
             "making it the perfect place in which to store equipment for use "+
             "in the defence of the living forest and its inhabitants. "+
             "These racks are reserved for elite archers, where they may store "+
             "delicate items that require great skill to master and maintain. "+
             gBlurbSfx +
             " An opening to the northeast leads to the heart "+
             "of the fortress, while to the east another rack room can be seen.\n");

    add_item(({"fort","fortress","treetop fortress"}),"@@fort_purpose");
    add_item(({"treetops","whispering treetops","branches"}),"@@fort_description");
    add_item(({"walls","wall"}),"@@fort_walls");
    add_item(({"stakes","stakes","strands","strand"}),"@@fort_stakes");
    add_item(({"loopholes","loophole","window","windows","ground","ground below"}),"@@fort_vantage");
    add_item(({"foliage"}),"@@fort_foliage");

    add_cmd_item(({"down", "ground", "loophole", "window"}), "view", "@@view_down");
    set_tell_time(250);
    add_tell("Branches creak and leaves flutter in the gently shifting treetops.\n");


    gViewFallDest = VIEWDEST;

    INSIDE

    add_exit(GUILDROOMS + "fort_rack1", "east", 0);
    add_exit(GUILDROOMS + "fort_nexus", "northeast", 0);

    // Clone the racks
    room_add_object(GUILD_OBJ + "rack_herb2", 1, 0); 
    room_add_object(GUILD_OBJ + "rack_misc2", 1, 0);
    room_add_object(GUILD_OBJ + "rack_armour2", 1, 0);
    room_add_object(GUILD_OBJ + "rack_bow2", 1, 0); 
    room_add_object(GUILD_OBJ + "rack_arrow2", 1, 0); 
    reset_room();
}

