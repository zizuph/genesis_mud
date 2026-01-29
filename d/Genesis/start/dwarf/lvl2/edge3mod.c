/*
 * Copyright notice, please read.
 *
 * Copyright Chalmers Datorf|rening, 1992
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 *  original:
 *  /d/Genesis/start/dwarf/lvl2/edge3.c
 *
 * **** Modified by Vitwitch 08/2021:
 *  /d/Genesis/start/dwarf/lvl2/edge3mod.c
 *  to include a cave opening in the cliff for the Illuminated of Lars rooms
 *     /d/Sparkle/clubs/illuminated/room/
 */


#pragma save_binary
#pragma strict_types

inherit "/std/room";

#define HARD_TO_CLIMB 20

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "../defs.h"


int
climb_inside()
{
    object p = this_player();
    string cave_path = ILLUMINROOM + "cave_ent0";

    if ( !ILLUMINATED_ACCESS_GRANTED(p) )
    {
	write("Your mortality is holding you back " +
	  "from climbing inside the star-shaped hole.\n");
	say(QCTNAME(p) + 
          " was about to climb inside a hole in the cliff but stopped.\n");
	return 1;
    }

    if ( p->query_skill(SS_CLIMB) < HARD_TO_CLIMB )
    {
	write("You don't think you are skilled enough to try " +
	  "and climb inside the hole in the small cliff.\n");
	say(QCTNAME(p) + 
          " attempts to climb inside a hole in the cliff but fails.\n");
	return 1;
    }

    write("You climb inside the star-shaped hole by way of the "+
         "surrounding cracks in the cliff face.\n");
    say( QCTNAME(p)+ 
      " climbs down the cliff and disappears from sight into a hole.\n" );

    p->move_living( "M", cave_path, 1, 0 );

    tell_room( cave_path, QCNAME(p) + 
      " arrives climbing inside " +
      "from the cliff face outside.\n", p);
    return 1;
}


void
create_room()
{
    set_short("An edge, near the top of a hill");
    set_long("You are on the edge of a high mountain, just north of a small "+
             "cliff. The view is stunning from here, and deep below you, you "+
             "spot a small river flowing through the valleys.\n");

    add_item(({"cliff","small cliff"}),
      "From the edge, you can see that the small cliff is "+
      "covered in cracks and fissures. They all seem to radiate outwards "+
      "from a star-shaped hole, part way down the rock face.\n"); 

    add_item(({"cracks","fissures"}), "The rocky face of the small cliff "+
     "seems shattered by cracks and fissures radiating out from a "+
     "star-shaped hole. The cracks seem to provide a way down from the "+
     "edge to <climb> inside the star-shaped hole");

    add_item(({"hole","star-shaped hole","star shaped hole"}),
      "Part way down the cliff face, is a curious star-shaped hole. It "+
      "looks like its jagged edges of stone have been punched outwards "+
      "into the open air... like the exit wound of an arrow. The cracks "+
      "on the cliff face may provide a route to access the hole and "+
      "<climb> inside.\n");

    add_item(({"river","small river"}),
      "A small river snakes its way along the valley floor, " +
      "bringing clear water to the flora and fauna of this " +
      "secluded place.\n");

    add_cmd_item( ({"inside","inside hole",
             "inside the star-shaped hole","inside the hole"}),
                  "climb","@@climb_inside");

    add_exit(LVL2+"hill1","south");
    add_exit(LVL2+"edge2","west");
}

