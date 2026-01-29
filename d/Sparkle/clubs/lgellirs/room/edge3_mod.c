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
 * **** Modified by Vitwitch 2022:
 *  /d/Genesis/start/dwarf/lvl2/edge3mod.c
 *  to include a mysterious trail to the rooms of the Gellirs of Lars
 *     /d/Sparkle/clubs/lgellirs/room/
 */


#pragma save_binary
#pragma strict_types

inherit "/std/room";

#define HARD_TO_FIND 20

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "../defs.h"
#include "/d/Sparkle/clubs/lgellirs/defs.h"


public void
hook_smelled(string str)
{
    write("The scent of earth and sprouting life wafts upon crisp air.\n");
}

int
inside_exit_see()
{
  if ( this_player()->query_wiz_level() > 0 )
      return 0;
  else
      return 1;
}


int
inside_exit_use()
{
  if ( this_player()->query_wiz_level() > 0 )
      return 0;
  else
  {
      this_player()->catch_msg("What?\n");
      return 1;
  }
}


void
create_room()
{

    set_short("A forest edge, near the top of a hill");

    set_long("You are on the edge of a curious grove of trees on "+
             "a spur of a mountain. They are not pines; which seem "+
	     "to grow everywhere else in the North. "+
	     "The view down from here is stunning. Deep below you, "+
	     "you spot a small river flowing through the valleys.\n");

    add_item(({"pines","pine forest","forest","great northern forest"}),
      "The pines of the Great Northern Forest stand in endless " +
      "rows right across the North of Sparkle -- tall and straight "+
      "without let or "+
      "hindrance, save for the thick grove of ash trees here.\n");

    add_item(({"mountain","mountain spur","spur","range"}),
      "The cold clean air of this high mountain spur chills and envigorates. " +
      "The everyday sounds and smells of the lowlands and their settlements "+
      "seem very far away. The grove of ash trees before you blocks the " +
      "way further uphill from this place.\n");

    add_item(({"river","small river","valleys","valley","downhill"}),
      "A small river rushes along the valley floor, " +
      "bringing clear water to the flora and fauna of the " +
      "secluded places of the North.\n");

    add_item(({"grove","curious grove","ash grove","trees",
                  "grove of ash","grove of ash trees","uphill"}),
      "Great ash trees spread their branches and generous foliage wide "+
      "before you, barring the way uphill. " +
      "This ash grove is well established, deep of root and tangled "+
      "growth high and low, densely wooded, ancient and mysterious. Its "+
      "mystery invites the adventurer to wander inside.\n");

    add_exit(LVL2+"hill1","south");
    add_exit(LVL2+"edge2","west");

    // wizard shortcut entrance to the Askelund
    //  ... others have to <wander inside>

    add_exit( LGELLIRROOM + "club_asklnd", "inside",
              inside_exit_use, 0, inside_exit_see );
}


int
wander_it( string str )
{
    if ( !strlen(str) || !wildmatch("inside*",lower_case(str)) )
    {
        write("Wander where? Wander inside the grove?\n");
        return 1;
    }

    object p = this_player();
    string grove = LGELLIRROOM + "club_wandr1";

    if ( !LGELLIR_ACCESS_GRANTED(p) && !p->query_wiz_level() )
    {
	write("Your mortality is holding you back " +
	  "from wandering inside the curious ash grove.\n");
	say(QCTNAME(p) + 
          " seemed about to set foot inside the curious ash grove,"+
          "  but stopped for some reason.\n");
	return 1;
    }

    if ( p->query_skill(SS_LOC_SENSE) < HARD_TO_FIND )
    {
	write("You don't think you are skilled enough to find " +
	  "your way within such a dense and twisted grove of trees.\n");
	say(QCTNAME(p) + 
          " peers quizzically inside the curious grove"+
          " trying to find a way in, but after some time is still"+
          " standing rooted to the spot.\n");
	return 1;
    }

    write("You wander inside the curious grove... \n\n"+
          "twisting between trunks... "+
          "the outside world fades from sight... "+ 
          "the density of growth confuses the mind...\n\n");

    say( QCTNAME(p)+ 
      " wanders into the curious grove, twisting between ancient trunks "+
      "and roots -- soon disappearing from sight.\n" );

    p->move_living( "M", grove, 1, 0 );

    tell_room( grove, QCNAME(p) + " arrives disoriented.\n",p);

    return 1;
}


void
init()
{
    ::init();
    add_action(wander_it,"wander");
}

