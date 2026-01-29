/* s_road3.c			
 * Styles.   3 Mar 1993
 *
 * Updated to put players in the new Actors club in Sparkle domain
 * Lunatari 1 Feb 2006
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "wild.h"

//#define ACTORS_ENTRACE "/d/Genesis/clubs/rpg/theatre"
//#define NEW_ACTORS_ENT "/d/Sparkle/clubs/actors/room/theatre"

void
create_room()
{
    set_short("Bright road");
    set_long("\n"+
             "Bright road.\n"+
             "To the north you can see the road leading away towards a village \n"+
             "while to the south, where the forest grow thicker, you seem to make \n"+
		     "out a bridge in the distance. On both sides of the road you can see \n"+
		     "the forest closing in, allthough much of it has been cleared away \n"+
		     "to the east.\n"+ 
		
/*			 "You realize that if you choose to go south to where the road vanishes\n"+
			 "over the crest of a hill at the horizon, then you're in for quite a\n"+
			 "long walk.\n"+
 */

             "");

    add_exit(THIS_DIR + "s_road2","north");
	add_exit(THIS_DIR + "s_road4","south");


   // add_exit(NEW_ACTORS_ENT, "west");

    add_item(({"road" }),
             "");

	add_item(({"village" }),
             "");

	add_item(({"terrain" }),
             "");

	add_item(({"crest" }),
             "");

	add_item(({"horizon" }),
             "");

	add_item(({"hill" }),
             "");

	add_item(({"road","village","terrain","crest","horizon","hill" }),
             "");


    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
