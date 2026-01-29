/*******************************************************************\
| SPIKES_15.C                                                       |
\*******************************************************************/

/*
 * 20/08/06 Lucius      Reset herbs
 * 07/06/24 Arandir     Created from description by Sionell
 *
 */

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
  set_short ("");
  set_long  (&dg_long ());

  dg_add_herbs (DG_HERBS_CLIFFS);

  add_exit ("spikes_16", "north");
  add_exit ("spikes_14", "east");
  add_exit ("spikes_13", "south");

  dg_item_sky_outside ();
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "Squeezing between the craggy rocks, you come out on the western " +
          "side of the spires. The path here is a bit more sheltered from " +
          "the wind and elements.";

  if (dg_is_night ()) sDesc +=
    " A vague shape of a landslide is visible in the darkness towards north.";
  else sDesc +=
    " You see that recent volcanic activity has caused a small landslide further north.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
