/* Xak Tsorath coded by Percy */

#include "xlocal.h"

inherit XAKOUTROOM

#include RND_MEET
#include <ss_types.h>
#include <macros.h>


object monster, room;

void
create_xak_room() 
{
    set_short("On a trail");
    set_long("You are on a small trail. To your northeast " +
	     "you can see the trail lead into a stretch of marshland known " +
	     "locally as 'the cursed lands', while to your west the Plains " +
	     "of Abanasinia stretch out before you.\n");
    
    /*add_exit("/d/Krynn/wild/plains/plains2.c", "west", "@@cross", 3);*/
    add_exit(ABAPLAINS,"west",0,3);
    add_exit(TDIR + "marshend", "northeast", 0);
    OUTSIDE;
    LIGHT;
}

int
cross()
{
    write("You travel far along the trail to the west.\n");
    return 0;
}
