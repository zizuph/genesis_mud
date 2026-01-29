/*
 * The Northern end of the High Road
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit BASE_ROAD;


void
create_road()
{
    set_short("A wide open road");
    set_extraline("This road looks like any old road, "
    +"aside from the ground being covered by a sooty residue. "
    +"Some kind of fire seems to have scorched this place "
    +"thoroughly. The vegetation, every grass, bush or tree "
    +"appears blackened and covered in soot. The road continues "
    +"north towards what looks like a circular building. "
    +"You can also turn southwest back to the main road.");
    
    add_item(({"vegetation", "grass", "bush", "bushes"}),
        "The closer you look the more damaged the vegetation "
        +"appears to be. The damage obviously looks like a "
        +"result of a pretty recent, and no doubt large, fire.\n");
        
    add_item(({"road", "ground"}),
        "The road is wide and covered with large cobble stones "
        +"which themselves look darker than what they did farther "
        +"south. The vegetation, albeit cleared from the "
        +"road, looks damaged and sooty.\n");
        
    add_item(({"building", "circular building"}),
        "The building before you is very large and impossibly "
        +"white given the surroundings. From this distance you "
        +"see a couple of banners and what appears to be two guards "
        +"standing outside the door leading into, but you "
        +"can’t make out much detail.\n");
        
    add_item(({"banners", "banner"}),
        "You see two banners with the symbol of a twisting flame "
        +"barely visible from this distance. Perhaps if you move "
        +"closer you will be able to examine them more closely.\n");

    reset_faerun_room();

    add_exit(HR_DIR + "temproad02", "north");
    add_exit(HR_DIR + "nrd04", "southwest");
}

public void
init()
{
    ::init();
}

void
reset_faerun_room()
{
    set_searched(0);
}
