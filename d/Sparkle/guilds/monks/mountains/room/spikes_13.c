/*******************************************************************\
| SPIKES_13.C                                                       |
\*******************************************************************/

/*
 * 20/08/06 Lucius      Reset herbs
 * 06/09/17 Arandir     Added herbs
 * 02/09/10 Arandir     Incorporated suggestions by Tijgen
 * 02/07/20 Arandir	First description
 * 01/12/09 Arandir	Created
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
  set_short ("a foot of a tall spire");
  set_long  (&dg_long ());

  dg_add_herbs (DG_HERBS_CLIFFS);

  add_exit ("spikes_15", "north", &mt_blocked_exit ());
  add_exit ("spikes_14", "northeast", &mt_blocked_exit ());
  add_exit ("spikes_12", "east");
  add_exit ("spikes_11", "south");

  dg_item_sky_outside ();

  mt_item_path_trodden ();
  mt_item_spire_near_unclimbable ();
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "You are progressing along the western side of a tall " +
          "spire, wickedly whipped against its steep side by " +
          "harsh winds.";

  if (dg_is_night ()) sDesc +=
    " The ground you tread feels more difficult to navigate " +
    "towards the north than towards the south.";
  else sDesc +=
    " More spires, albeit lower, rise to your north.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
