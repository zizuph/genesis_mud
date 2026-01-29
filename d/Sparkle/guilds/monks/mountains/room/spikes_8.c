/*******************************************************************\
| SPIKES_8.C                                                        |
\*******************************************************************/

/*
 * 20/08/06 Lucius      Reset herbs
 * 06/09/17 Arandir     Added herbs
 * 02/07/18 Arandir     First description
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
  set_short ("a wide mountain crest");
  set_long  (&dg_long ());

  dg_add_herbs (DG_HERBS_CLIFFS);

  add_exit ("spikes_7", "north");
  add_exit ("spikes_9", "northeast");

  dg_item_sky_outside ();

  mt_item_crest_flat ();
  mt_item_path_trodden ();
  mt_item_stream_deep ();
  mt_item_valley_far ();
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "A wide mountain crest provides an excellent vantage " +
          "point, from which most of the forest that covers the " +
          "valley below can be seen. Further away to the southeast, " +
          "you can make out";

  if (dg_is_night ()) sDesc +=
    " dim lights of a village.";
  else sDesc +=
    " a scattering of buildings. Thin wisps of smoke rise " +
    "from some of the roofs, marking what can be cooking " +
    "fires or forges of the village smithy.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
