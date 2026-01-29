#pragma strict_types

inherit "/std/room";
#include "../bazaar.h"

public void
add_descs()
{
    add_item(({"walls", "wall", "curving walls", "gneiss walls"}),
        "The walls are of gneiss with pale and dark bands. The crystals in "
		+"the stone glitter like jewels.\n");
    add_item(({"ceiling", "dome", "Source", "light", "trefoil"}),
        "The ceilings arc high overhead, three domes in a trefoil "
		+"pattern. The light of the Source pours through the domes "
		+"and sets the marble floor aglow.\n");
    add_item(({"floor", "floors", "marble", "marble floors", "tiles"}),
        "The floors are of mable tiles that have been flawlessly laid "
		+"such that it is impossible to see the seams where the stones "
		+"meet.\n");    		
	add_prop(ROOM_M_NO_ATTACK, "The God Nitikas casts his protection upon "
	    +"this place and the priceless artifacts with in it.");
	add_prop(ROOM_M_NO_MAGIC_ATTACK, "The God Nitikas casts his protection "
	    +"this place and the priceless artifacts within it."); 
	add_prop(ROOM_I_HIDE, -1); // Its a big wide open space. Nowhere to hide.
    IN;	
    IN_IN;	
}

