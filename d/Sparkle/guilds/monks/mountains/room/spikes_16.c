/*******************************************************************\
| SPIKES_16.C                                                       |
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

  add_exit ("spikes_15", "south");
  add_exit ("spikes_17", "west");

  dg_item_sky_outside ();
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "At this altitude, you find moving challenging.";

  if (dg_is_night ()) sDesc +=
    " The cold silence of the night amplifies the feeling of emptiness that surrounds you.";
  else sDesc +=
    " Even the awe inspiring view of the spires all around reminds you of how high up you really are.";

  sDesc += " Your breath comes in short gasps. The large spires behind you give fair warning of a rough climb still ahead.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
