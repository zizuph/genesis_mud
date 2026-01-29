/*******************************************************************\
| SPIKES_11.C                                                       |
\*******************************************************************/

/*
 * 20/08/06 Lucius      Reset herbs
 * 06/09/17 Arandir     Added herbs
 * 02/09/10 Arandir     Incorporated suggestions by Tijgen
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
  set_short ("a rising mountain crest");
  set_long  (&dg_long ());

  dg_add_herbs (DG_HERBS_CLIFFS);

  add_exit ("spikes_13", "north");
  add_exit ("spikes_12", "northeast");
  add_exit ("spikes_10", "south");

  dg_item_sky_outside ();

  mt_item_crest_ridged ();
  mt_item_lake_far ();
  mt_item_path_trodden ();
  mt_item_spires_far ();
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "A wide mountain crest stretches from south to north. While " +
          "the southern expanse is almost flat, descending slowly " +
          "towards a mountain lake, the area to the north " +
          "is ridged with tall spires.";

  if (dg_is_night ()) sDesc +=
    " The thinning mountain air makes you remember how far up " +
    "in the mountains this place really is.";
  else sDesc +=
    " The tallest of the spires towers right in front of you, " +
    "partially shrouded in clouds.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
