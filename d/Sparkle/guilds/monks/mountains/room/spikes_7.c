/*******************************************************************\
| SPIKES_7.C                                                        |
\*******************************************************************/

/*
 * 20/08/06 Lucius      Reset herbs
 * 06/09/17 Arandir     Added herbs
 * 02/07/18 Arandir     First description
 * 01/11/10 Arandir	Created
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
  set_short ("a rocky outcropping");
  set_long  (&dg_long ());

  dg_add_herbs (DG_HERBS_CLIFFS);

  add_exit ("spikes_8", "south");
  add_exit ("spikes_6", "southwest");

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

  sDesc = "A rocky outcropping reaches out from the massive " +
          "crest of the mountains. The crest stretches far " +
          "away into northeast, but the outcropping points " +
          "directly towards north,";

  if (dg_is_night ()) sDesc +=
    " where a reflection of a few of the brightest stars " +
    "flickers on the surface of a mountain lake.";
  else sDesc +=
    " where the blue of sky competes with its reflection " +
    "on the surface of a mountain lake.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
