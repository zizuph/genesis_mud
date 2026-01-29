/*******************************************************************\
| SPIKES_10.C                                                       |
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

  add_exit ("spikes_11", "north");
  add_exit ("spikes_9", "south");

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

  sDesc = "The thin mountain air is making breathing difficult here, " +
          "but that does not take anything from the strength of the " +
          "wind that buffets you in occasional gusts. Standing on " +
          "the wide mountain crest,";

  if (dg_is_night ()) sDesc +=
    " you feel the gaping depth below you, but the darkness " +
    "masks its threatening proximity in a gesture that " +
    "is both treacherous and merciful.";
  else
  {
    if (dg_is_winter ()) sDesc +=
      " you catch a glimpse off the surface of the tarn further " +
      "to your west, but the icy tears welling up in your eyes " +
      "from the cold wind teach you better than to stare.";
    else sDesc +=
      " you feel tempted to admire the view of the tarn further " +
      "to your west.";
  };

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
