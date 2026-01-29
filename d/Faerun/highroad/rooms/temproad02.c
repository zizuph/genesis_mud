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
    set_short("Outside the Temple of Kossuth");
    set_extraline("The Temple of Kossuth stands before you with "
    +"all its magnificence, the precision with which it’s been "
    +"erected seems too good to be simple mortal masonry work. "
    +"The vegetation around the temple appears blackened, covered "
    +"with soot and ashes. The temple itself is circular in shape, "
    +"and the white stones from which it’s built seem carved to "
    +"fit each other without any binding or fasteners. The open door "
    +"set in an arch that seems carved out of rock is guarded by "
    +"two hooded shapes with flame enveloped hands. A banner "
    +"is hung up high on each side of the door.");
    
    add_item(({"door", "open door"}),
        "The door is made of what can only be ironwood, "
        +"considering how sooty and blackened the entire "
        +"thing looks. It is open.\n");
        
    add_item(({"road", "ground"}),
        "The road is wide and covered with large cobble stones "
        +"which themselves look darker than what they did farther "
        +"south. The vegetation, albeit cleared from the "
        +"road, looks damaged and sooty.\n");
        
    add_item(({"vegetation"}),
        "The closer you look the more damaged the vegetation "
        +"appears to be. The damage obviously looks like a result "
        +"of a pretty recent, and no doubt large, fire.\n");
        
    add_item(({"building", "temple", "walls", "stones"}),
        "The white stones making up the temple seem perfectly cut "
        +"and placed together. Aside from the exquisite workmanship "
        +"and how impossibly white it is in contrast to the surrounding "
        +"landscape, there is nothing notable about it.\n");
        
    add_item(({"guard", "guards"}),
        "The guards are most likely human, but dark hoods prevent you "
        +"from seeing any facial features. The most interesting aspect "
        +"is still the black flame covering their wielded swords.\n");
        
    add_item(({"banner", "banners"}),
        "The workmanship on these banners is exquisite. A twisting "
        +"flame is embroidered upon them using a mixture of threads, "
        +"including what looks to be gold thread. As they move in the "
        +"wind, the flames ripple and almost look real.\n");

    reset_faerun_room();

    add_exit("/d/Faerun/guilds/black_flame/rooms/bf_entrance", "north");
    add_exit(HR_DIR + "temproad01", "south");
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
