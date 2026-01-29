/* 
*
*  Created by Clyptas August 2017
*
* Jarlaxle's camp entrance
*
*/
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>

 
inherit "std/room";
 
public void
create_room()
{
    
    //0 means outdoors, and 1 means indoors for this prop
    add_prop(ROOM_I_INSIDE, 0);
    
	
    set_short ("A dusky, gloomy forest.");

    set_long("The forest is quiet, save for the occasional bird call and " +
         "rustle of leaves. Goosebumps slowly rise on the surface of your " +
         "skin and you feel as if you are being watched. The trees are tall " +
         "and many, underbrush and undergrowth seem to bar your way.\n");
    
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
    
    add_exit(HIGH_RD_DIR + "rooms/nrd23","west");
	add_exit(CAMP_DIR + "camp1","east");
	
}
public void
hook_smelled(string str)
{
    switch(str)
    {
    case "leaves":
	write("Closing your eyes, you lean your face back letting the" +
	"warm sunlight fall against your skin. Your nose is assailed " +
	"with the smell of petrichor, strong and sweet.\n");
	break;
	
	default:
	write("As your feet crunch on the leaves the soft scent, "+
	    "of petrichor wafts from the ground.\n");
	break;
}
}
