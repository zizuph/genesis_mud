/*******************************************************************\
| CLAW_15.C                                                         |
\*******************************************************************/

/*
 * 03/10/21 Arandir	Created
 * 04/03/13 Arandir     Polished a bit
 *
 */

#include <tasks.h>
#include <ss_types.h>

#include "../defs.h"

inherit MT_ROOM_BASE;

inherit DG_CLOCK_LIBS;

//-------------------------------------------------------------------

/*
 * Function name : create_room
 *
 */

void create_room ()
{
  ::create_room ();
  set_short ("narrow mountain path");
  set_long  ("The path you follow is getting narrower with every step, " +
             "in places so much that you grope for a hold in the cliff " +
             "face to your west to navigate over the most difficult spots. " +
             "The cliff is not as steep here as it was in the lower parts " +
             "of the path though, providing a few holds for the vegetation.\n");

  add_exit ("claw_12", "south");
  add_exit ("claw_16", "northwest");

  dg_item_sky_outside ();
  mt_item_path_barely ();

  add_item (({ "cliff", "face", "cliff face", "support" }),
            "The cliff face to your west is rough and cold, rising to " +
            "obscure your view in that direction but providing you " +
            "with support at the same time.\n");

  add_item (({ "vegetation", "greenery", "flowers", "patch", "patches" }),
            "More moss than grass, the few patches of vegetation are " +
            "a welcome if scarce sight.\n");
}

//-------------------------------------------------------------------

