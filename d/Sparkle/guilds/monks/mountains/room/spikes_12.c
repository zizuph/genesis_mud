/*******************************************************************\
| SPIKES_12.C                                                       |
\*******************************************************************/

/*
 * 20/08/06 Lucius      Reset herbs
 * 06/09/17 Arandir     Added herbs
 * 02/09/10 Arandir     Incorporated suggestions by Tijgen
 * 02/07/20 Arandir     First description
 * 01/12/09 Arandir	Created
 *
 */

#include <tasks.h>

#include "../defs.h"

inherit MT_ROOM_BASE;

inherit DG_CLOCK_LIBS;

//-------------------------------------------------------------------

string dg_long ();

//-------------------------------------------------------------------

/*
 * Function name : reset_room
 */

void reset_room ()
{
    set_searched(0);
}

/*
 * Function name : create_room
 *
 */

void create_room ()
{
  ::create_room ();
  set_short ("a foot of a tall spire");
  set_long  (&dg_long ());

  dg_add_herbs (DG_HERBS_CLIFFS);

  add_exit ("spikes_11", "southwest");
  add_exit ("spikes_13", "west");

  dg_add_climb ("spire",
                ({"up", "slope", "spire", "cliff" }), TASK_ROUTINE,
                "You climb up the spire.",
                "climbs up the spire.",
                "arrives climbing up the spire.",
                "You try to climb up the spire but fail.",
                "tries to climb up the spire but fails.");

  dg_item_sky_outside ();

  mt_item_path_trodden ();
  mt_item_spire_near_climbable ();
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "You are making headway along the eastern side of " +
          "a tall spire, temporarily sheltered from the harsh " +
          "winds by its steep side.";

  if (dg_is_night ()) sDesc +=
    " The ground you tread feels more difficult to navigate " +
    "towards the north than towards the south.";
  else sDesc +=
    " More spires, albeit lower, rise to your north.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
