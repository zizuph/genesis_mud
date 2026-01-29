/*
 * Abaddon - 2020 /d/Faerun/underdark/dark_dom2/rooms/
 */

#define NPC "/d/Faerun/underdark/dark_dom2/npc/"
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <terrain.h>
#include "defs.h"

inherit BASE_DOM2_INDOOR;

void
create_dom2_room()
{
    set_long("Somewhere underground.\n"
        +"Silence and darkness fills the tunnel. The weight of the mount"
        +"ain seems heavy in this forbidding place. The dark tunnel is r"
        +"ough and starts to decline deeper into the mountain. The air he"
        +"re looks faintly red, and smells of fresh gore. A path leads to"
        +" the south and northwest.\n");
    
    set_short("Somewhere underground");
    
    //If we want herbs here.
    //add_std_herbs("mere");
    add_std_herbs("underdark");
        
     add_item(({"walls", "wall"}),
        "The walls are jagged and roughed over, with dips and depressions"
        +" encapsulating your view.");

     add_item(({"path", "footsteps"}),
        "You can see slight footsteps leading deeper into the tunnel.\n");

     add_item(({"underground"}),
        "It's hard to say how far undergound you are, but it would be unw"
        +"ise to get lost here.\n");

     add_item(({"darkness"}),
        "No light from the surface could ever hope to reach here.\n");

    add_item(({"tunnel"}),
        "This tunnel looks jagged as if something forced its way into sol"
        +"id rock.\n");

    add_item(({"floor", "ground"}),
        "The floor is full of pebbles, stones, and other debris from brea"
        +"kage that created it. You notice cracks by your feet.\n");

    add_item(({"air", "haze"}),
        "The air here reeks of death. A crimson haze seems to surround al"
        +"l you see.\n");

    add_item(({"cracks", "dips", "depressions", "dip", "depression", "crack"}),
        "Cracks and divots scatter the floor, as if it has been worn down"
        +" over time.\n");

    reset_faerun_room();
        
    add_exit(ROOM_DIR + "5", "out");
    add_npc(NPC + "skeleton", 2);
    add_npc(NPC + "necro", 1);
//    reset_room();

//    reset_faerun_room();

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