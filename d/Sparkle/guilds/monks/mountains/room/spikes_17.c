/*******************************************************************\
| SPIKES_17.C                                                       |
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

  add_exit ("spikes_18", "north");
  add_exit ("spikes_16", "east");
  add_exit ("spikes_15", "southeast");

  dg_item_sky_outside ();
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "You are now firmly on the path beyond the spires. Behind you, " +
          "their jagged forms speak of a tremendous struggle between earth " +
          "and sky, and of a difficult path surmounted. The wind, while still " +
          "strong, is less fierce here, probably blocked by the spires at your " +
          "back. To the southeast, you could scramble down the loose gravel " +
          "and to the west, you hear the wind whistling on the outer edge " +
          "of the spires.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
