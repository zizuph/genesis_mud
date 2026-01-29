/**
 * Room in the Archer Guild
 *
 * Navarre November 23th 2007.
 *
 * Updated by Vitwitch Nov 2020.  
 */
    
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"
#include "../guild.h"

inherit "/d/Krynn/guilds/elven_archers/rooms2/baseroom_fort";


#define GUILDROOMS "/d/Krynn/guilds/elven_archers/rooms2/"
#define VIEWDEST "/d/Krynn/qualinesti/elf_camp/ambush2"


void
reset_krynn_room()
{
}

void
create_krynn_room()
{

    set_short("A dormitory in a treetop fortress");

    set_long(gBlurbPfx + 
             " This room serves as a restful dormitory among the swaying trees. "+
             "Dozens of woody nooks, worn smooth by elven bodies down through "+
             "the ages, serve as comfortable places to curl up and sleep. "+
             gBlurbSfx +
             " An opening to the west leads towards a gleaming "+
             "set of racks. To the northwest lies the very centre of the fortress, "+
             "while to the east a far-off antechamber can be seen.\n");

    add_item(({"bunks", "bunk", "nook", "nooks"}), "The wood of each nook is smooth " +
               "and pleasant to the touch; long tangled strands of grey moss resembling "+
               "a huge warm beard can be arranged about an elven form for added comfort. "+ 
               "You are welcome to choose a nook for yourself to <start here> forever "+
               "after, for when you wake from the Nether.\n");

    gViewFallDest = VIEWDEST;

    add_item(({"fort","fortress","treetop fortress"}),"@@fort_purpose");
    add_item(({"treetops","whispering treetops","branches"}),"@@fort_description");
    add_item(({"walls","wall"}),"@@fort_walls");
    add_item(({"stakes","stakes","strands","strand"}),"@@fort_stakes");
    add_item(({"loopholes","loophole","window","windows","ground","ground below"}),"@@fort_vantage");
    add_item(({"foliage"}),"@@fort_foliage");

    add_cmd_item("here", "start", "@@do_start");
    add_cmd_item(({"down", "ground", "loophole", "window"}), "view", "@@view_down");
    set_tell_time(250);
    add_tell("The basso creaking of branches and hissing of leaves in the wind lulls the senses.\n");


    INSIDE
    
    add_exit( GUILDROOMS + "fort_eastentr", "east", 0);
    add_exit( GUILDROOMS + "fort_rack1", "west", 0);
    add_exit( GUILDROOMS + "fort_nexus", "northwest", 0);

    reset_room();
}

int
do_start()
{
    if (TP->query_guild_name_occ() == "Ansalon Elvish Archers" ||
        TP->query_guild_name_lay() == "Ansalon Elvish Archers")
    {	
        if( TP->query_alignment() > -100 )
        {
            TP->set_default_start_location(START_ROOM);
            write("As a good archer, you will start here now when you wake.\n");
	    return 1;
        }
    }
    write("Only good archers can sleep and wake here.\n");
    return 1;
}

