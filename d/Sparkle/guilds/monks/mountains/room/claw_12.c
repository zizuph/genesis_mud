/*******************************************************************\
| CLAW_12.C                                                         |
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
  set_short ("mountain path at a crack");
  set_long  ("The narrow path follows a cliff face towards north, full " +
             "of weathered stone. The way back disappears in a sharp " +
             "bend to the east, where a construction of wood and ropes " +
             "also stands. A crack in the cliff face was worn down by " +
             "the incessant dribble of rain water and melting snow to " +
             "a width that also permits passage to the west.\n");

  add_exit ("claw_15", "north");
  add_exit ("claw_6", "east");
  add_exit ("claw_13", "west");

  dg_item_sky_outside ();
  mt_item_path_barely ();

  add_item (({ "cliff", "face", "cliff face" }),
            "A cliff face rises to the south and west, replacing " +
            "half of your view with a relief of weathered stone " +
            "and jagged cracks. One of the cracks is large " +
            "enough for a man to comfortably pass through.\n");

  add_item (({ "crack", "cracks" }),
            "A wide crack was etched into the side of the cliff by " +
            "the harsh attacks of the winter weather. The crack " +
            "opens a way to the west.\n");

  add_item (({ "bend" }),
            "The path disappears in a bend to the east, where a " +
            "bridge head stands.\n");

  add_item (({ "construction", "bridge", "head", "bridge head" }),
            "A narrow but sturdy bridge of wood and ropes is visible " +
            "just where the path disappears to your east. The " +
            "construction rocks in the wind with a vehemence " +
            "that belies its purpose.\n");
}

//-------------------------------------------------------------------

