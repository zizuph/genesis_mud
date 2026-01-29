/*
 * Path in the Mere of Dead Men
 * -- Finwe, July 20064
 * Modified and created by Nerull 2018 for Warlocks.
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_MERE;

#define WARLOCK_ROOMS_DIR "/d/Faerun/guilds/warlocks/rooms/"


public int
into_shaft(string str)
{
    if (str == "hole" || str == "shaft")
    {   
        write("\n\nYou enter the dark shaft in the mossy mound!\n\n");
        
        tell_room(ROOM_DIR + "metrail4", QCNAME(this_player())
        + " climbs down into something!\n", this_player());
        
        tell_room(WARLOCK_ROOMS_DIR + "shaft1", QCNAME(this_player())
        + " climbs in from above!\n", this_player());
        
        this_player()->move_living("M", WARLOCK_ROOMS_DIR + "shaft1", 1);
        return 1;
    }
 
    return 0;
}


void
create_mere()
{
    set_short("Somewhere deep in the Mere of Dead Men");
    
    set_extraline("You are standing on a mossy mound that is slightly "
    +"elevated above the swamp water. A huge tree occupies most of the "
    +"hill with leafless branches stretching out like creepy talons "
    +"in every direction above your head. The trunk of the tree is "
    +"rather large, probably measuring about six feet in diameter. The "
    +"large roots spread out like a cobweb, digging deep into "
    +"the mossy mound.\n");
    
    add_item(({"patch", "patch of fabric", "blue patch",
    "blue patch of fabric"}),
    "The blue patch of fabric definitely belongs to a "
    +"dress. It seems to have been torn off by force and "
    +"placed here.\n");
    
    add_item(({"hole"}),
    "The hole in the mound is almost covered entirely with "
    +"moss, and is barely, if at all visible for the "
    +"absent minded. It seems to lead down into some sort of "
    +"a dark moldy shaft.\n");
    
    add_item(({"dark moldy shaft", "moldy shaft", "shaft"}),
    "It's too dark to see anything except that the shaft seems "
    +"to continue downwards into the darkness. You may "
    +"enter it though, if you dare.\n");
    
    add_item(({"mossy hill", "hill", "mound", "mossy mound"}),
    "The hill merges from the swamp water like a greenish mound, "
    +"effectively creating a tiny island. It's completely covered "
    +"in moss, and primarily features a huge tree in its dead center. "
    +"You notice two "
    +"items of interest when you examine it closer; A blue patch of fabric "
    +"and an almost invisible hole leading down into the darkness...\n");
    
    add_item(({"large roots", "roots"}),
    "The roots are rather large and spread out like a cobweb from the "
    +"large trunk of the tree. Many of them seem to dig deep into the "
    +"mossy mound.\n");
    
    add_item(({"large trunk", "trunk"}),
    "Judging by the six feet in diameter large trunk, this tree is "
    +"probably very old. You see large roots spread out from the "
    +"base of the trunk like a cobweb.\n");
    
    add_item(({"huge tree", "tree", "oak"}),
    "You are not sure, but you believe this is a weird variant "
    +"of an oak. The trunk is rather large, and the leafless branches "
    +"reach out far above your head in every direction. The roots "
    +"dig deep into the mossy mound here.\n");
    
    add_item(({"leafless branches", "branches", "talons", "creepy talons"}),
    "The branches are many, some large and some rather small. They reach "
    +"in every direction above your head, creating a leafless canopy. They "
    +"are also sort of twisted and looks like skeletal talons. What is "
    +"weirder is that they look very much alive as with the rest of the "
    +"tree, even if there are no leaves to be found anywhere.\n");
    
    
    add_std_herbs("mere");

    reset_faerun_room();
    
    add_exit(ROOM_DIR + "metrail3", "southeast");
}


void
init()
{
    ::init();

    add_action(into_shaft, "enter");
}


void
reset_faerun_room()
{
    set_searched(0);

    setuid();
    seteuid(getuid());
}
