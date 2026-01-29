/*
 * Room in the Archer Guild
 *
 * Navarre November 23th 2007.
 *
 * Updated by Vitwitch, Nov 2020
 */
    
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

#include "/d/Krynn/common/defs.h"
#include "../guild.h"

inherit "/d/Krynn/guilds/elven_archers/rooms2/baseroom_fort";

#define GUILDROOMS "/d/Krynn/guilds/elven_archers/rooms2/"
#define VIEWDEST "/d/Krynn/qualinesti/elf_camp/camp4"

/* prototype */
public int gather_it;

void
reset_krynn_room()
{
}

void
create_krynn_room()
{

    set_short("a reservoir of honeydew in a treetop fortress");

    set_long(gBlurbPfx +
      " The foliage of an immense ash tree dominates this room. Tiny ants"+
      " swarm over its peculiar surface, carefully tending a leafy"+
      " reservoir, rebinding any loose leaf-edges so that it remains intact."+
      " There is a strong sweet scent pervading this space. Drops of honeydew"+
      " have collected at the very base of the reservoir, at a leaf tip. "+
      gBlurbSfx + " Many openings lead in "+
      "all directions to other parts of the fortress.\n");

    add_item(({"fort","fortress","treetop fortress"}),"@@fort_purpose");
    add_item(({"treetops","whispering treetops","branches"}),
                     "@@fort_description");
    add_item(({"walls","wall"}),"@@fort_walls");
    add_item(({"stakes","stakes","strands","strand"}),"@@fort_stakes");
    add_item(({"loopholes","loophole","window","windows","ground",
                 "ground below"}),"@@fort_vantage");
    add_item(({"foliage"}),"@@fort_foliage");

    add_item(({"reservoir","dew","honeydew","sweet scent","ants",
                 "scent","leaf tip","tip"}),
     "Ants are drawn away from tending the integrity of the leafy "+
     "reservoir, drawn by the scent of the golden honeydew collecting "+
     "at its downward pointing tip. A ring of tiny ants fringe the sweet "+
     "liquid as it ebbs and drips. A line of dew steadily drains into a "+
     "glimmering bowl below the reservoir -- a bowl that invites "+
     "elven fingers to <gather> honeydew as a sweet means of sustenance.\n"); 

    add_cmd_item(({"down", "ground", "loophole", "window"}), "view",
                    "@@view_down");

    set_tell_time(250);
    add_tell("The ponderous bulk of the reservoir shifts with the "+
                "movement of the forest.\n");

    gViewFallDest = VIEWDEST;

    INSIDE
    
    add_exit(GUILDROOMS + "fort_westentr", "northwest", 0);
    add_exit(GUILDROOMS + "fort_nexus", "south", 0);
    add_exit(GUILDROOMS + "fort_library", "west", 0);
    add_exit(GUILDROOMS + "fort_postoffice", "east", 0);

    reset_room();
}


int
gather_it(string str)
{
    object obj;

    if(!strlen(str))
    {
        write("Gather what?\n");
        return 1;
    }

    if((str == "dew") || (str == "honeydew"))
    {
        write("Tracing a finger around the edge of "+
            "the bowl below the reservoir... coats it in clean fresh honeydew.\n");

        say(QCTNAME(this_player()) +" traces a finger around the edge of "+
            "the bowl below the reservoir... coating it in honeydew.\n");

        setuid();
        seteuid(getuid());
        obj = clone_object(GUILD_OBJ + "honeydew");
        obj->move(this_player(),1);
        return 1;
    }

}

void
init()
{
    ::init();
    add_action("gather_it", "gather");
}

