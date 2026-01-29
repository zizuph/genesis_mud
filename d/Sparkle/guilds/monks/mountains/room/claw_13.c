/*******************************************************************\
| CLAW_13.C                                                         |
\*******************************************************************/

/*
 * 03/10/21 Arandir	Created
 * 03/12/25 Arandir     Polished the description
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
  set_short ("mouth of a crack");
  set_long  ("A mouth of a crack, hollowed out in the cliff face by " +
             "the water and snow, opens up to your east. The rest of " +
             "the cliff is a block of weathered stone that marks a " +
             "drop to a valley far below. To the west, a barely " +
             "visible trail winds through rocks of various sizes " +
             "towards what appears to be a patch of greenery.\n");

  add_exit ("claw_12", "east");
  add_exit ("claw_14", "west");

  dg_item_sky_outside ();
  mt_item_path_barely ();
  mt_item_valley_heart_north ();

  add_item (({ "cliff", "face", "cliff face", "block" }),
            "A cliff face falls down to your east, a bulwark of stone " +
            "that guards access to the western part of the mountains. " +
            "The weather has breached the cliff in a wide crack though.\n");

  add_item (({ "mouth", "crack" }),
            "A wide crack opens agape in the ground east of you, " +
            "providing a way down the cliff you stand on.\n");

  add_item (({ "rock", "rocks", "small rocks", "huge rocks" }),
            "Many rocks, sizes from small to huge, are scattered around " +
            "you. While the small rocks look like they flaked away from " +
            "the huge ones, the huge rocks rise from the ground in a way " +
            "that suggests it was the ground that receded rather than the " +
            "rocks that grew here.\n");

  add_item (({ "patch", "greenery" }),
            "A patch of small trees, or rather, several patches that " +
            "melt together, are visible some way to the west. A marvel " +
            "that anything green could grow here.\n");
}

//-------------------------------------------------------------------

