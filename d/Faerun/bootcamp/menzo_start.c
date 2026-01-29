#pragma strict_types

#include "/d/Faerun/defs.h"
 
inherit "std/room";
 
public void
create_room()
{
    
    //0 means outdoors, and 1 means indoors for this prop
    add_prop(ROOM_I_INSIDE, 0);
    
    set_short ("A dusky, gloomy forest.");

    set_long("The forest is quiet, save for the occasional birdcall and " +
         "rustle of leaves. Goosebumps slowly rise on the surface of your " +
         "skin as you realize you are not alone. The trees are tall and " +
         "many, underbrush and undergrowth seem to bar your way.\n");
    
    add_item(({"leaves"}),
        "The leaves are turning, multitudes of different hues surround you " +
        "both in the branches of the grand trees, and coating the forest " +
        "floor. The leaves crunch softly under your feet.\n");
    
    add_item(({"trees"}),
        "The trees are tall and dark. They sway and creak softly in the " +
        "breeze.\n");
    
    add_item(({"underbrush","undergrowth"}),
        "The underbrush is thick and grows closely against the trees. " +
        "It's full of briars and nettles.\n");
        
    add_item(({"briars","nettles"}),
         "The briars and nettles look sharp. They twist in amongst " +
         "themselves, reaching close to halfway up some of the trees. " +
         "The tangleshoot is thick and makes you wonder about hiding " +
         "areas for those who wish to be unobserved.\n");
    
    add_exit("/d/Faerun/bootcamp/sideyard","sideyard");
	add_exit("/d/Faerun/bootcamp/camp1","camp");
}
