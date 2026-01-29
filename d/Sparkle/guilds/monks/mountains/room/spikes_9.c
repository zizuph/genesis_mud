/*******************************************************************\
| SPIKES_9.C                                                        |
\*******************************************************************/

/*
 * 20/08/06 Lucius      Reset herbs
 * 06/09/17 Arandir     Added herbs
 * 02/07/20 Arandir     First description
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
  set_short ("a rising mountain crest");
  set_long  (&dg_long ());

  dg_add_herbs (DG_HERBS_CLIFFS);

  add_exit ("spikes_10", "north");
  add_exit ("spikes_8", "southwest");

  dg_item_sky_outside ();

  mt_item_crest_flat ();
  mt_item_lake_near ();
  mt_item_path_trodden ();
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "A wide mountain crest is rising slowly towards the north. " +
          "To your west is a rocky outcropping, leaning over a tarn,";

  if (dg_is_night ()) sDesc +=
    " whose still surface reflects the light of the stars above.";
  else sDesc +=
    " whose deep blue surface is almost apt to leave the sky wanting.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
