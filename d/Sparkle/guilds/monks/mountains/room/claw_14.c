/*******************************************************************\
| CLAW_14.C                                                         |
\*******************************************************************/

/*
 * 03/10/21 Arandir	Created
 * 03/12/28 Arandir     Polished up
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
  set_short ("patches of greenery");
  set_long  ("Small patches of dwarf pine cover the rocky soil at " +
             "your feet in a stark contrast to the bare ground " +
             "visible off east. To the south, the greenery becomes " +
             "even more frequent, with a few trees appearing where " +
             "larger rocks create shelter from the cold wind. The " +
             "trail you follow seems to head to the west though, " +
             "rising steadily along a slope that rises towards " +
             "southwest.\n");

  add_exit ("claw_13", "east");
  add_exit ("claw_11", "south", &mt_blocked_exit ());
  add_exit ("tail_1", "west", &mt_blocked_exit ());

  dg_item_sky_outside ();
  mt_item_path_barely ();

  add_item (({ "patch", "patches", "pine", "pines", "tree", "trees", "greenery" }),
            "The green color of the dwarf pines contrasts with the bleak " +
            "brown and grey of the rocky soil, yet another manifestation " +
            "of the struggle all living things have to go through here. The " +
            "trees are small as befits their name, twisted in bizarre shapes " +
            "sculpted by the wind.\n");

  add_item (({ "ground", "soil" }),
            "The ground is hard and barren except for the few dwarf pines. " +
            "Who knows how the trees manage to find a hold here.\n");

  add_item (({ "rock", "rocks", "shelter" }),
            "A few larger rocks are visible off to the south, but there " +
            "is nothing particularly interesting about them being here.\n");

  add_item (({ "slope" }),
            "Yet another slope rises to the southwest, disappearing in " +
            "a distant haze with a promise of more heights.\n");
}

//-------------------------------------------------------------------

