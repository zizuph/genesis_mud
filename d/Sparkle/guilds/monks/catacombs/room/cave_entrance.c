/*******************************************************************\
| CAVE_ENTRANCE.C                                                   |
\*******************************************************************/

/*
/*
 * 03/07/23 Arandir     Created from the original entrance
 *
 */

#include "../defs.h"

inherit CC_ROOM_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("small landing");
  set_long ("This is a narrow landing at the end of a winding " +
            "circular staircase. Light filters down from the " +
            "garden above, enough to outline the opening to " +
            "your north that appears to lead into a large cave.\n");

  add_exit ("perch_0_0", "north");
  add_exit (DG_PATH + "/monastery/room/garden", "up");

  dg_add_entrance ("up", "Your eyes adjust to the darkness as you descend down the circular stairway.");

  add_item (({ "opening", "cave" }),
            "An opening to your north leads to a large, dimly lit " +
            "cave. You cannot see much beyond the entrance from " +
            "here, but what you can discern is a structure of " +
            "stone pillars and arches that obviously fills the "+
            "cave.\n");

  add_item (({ "stairs", "stairway", "staircase" }),
            "A circular staircase leads up to the garden. To all " +
            "appearances, it is quite old but sturdy. The steps " +
            "are level and sound, but the railing sports green " +
            "patches of verdigris.\n");
}

//-------------------------------------------------------------------

