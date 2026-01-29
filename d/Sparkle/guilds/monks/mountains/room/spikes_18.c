/*******************************************************************\
| SPIKES_18.C                                                       |
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

  add_exit ("spikes_17", "south");
  add_exit ("spikes_19", "west");

  dg_item_sky_outside ();
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "The path is starting to slowly descend from the height of the spires into a less rugged area.";

  if (dg_is_winter ()) sDesc +=
    " You see frozen stalks of grass jutting up between rocks.";
  else sDesc +=
    " You see stalks of hardy grass and the odd mountain flower pushing its way up between the shale and shattered granite of the rocks.";

  sDesc += " The wind is still fierce, but further down the trail you see the odd tree that has managed to find purchase.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
