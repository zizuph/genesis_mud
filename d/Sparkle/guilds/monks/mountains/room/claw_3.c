/*******************************************************************\
| CLAW_3.C                                                          |
\*******************************************************************/

/*
 * 01/12/09 Arandir	Created
 * 02/06/27 Arandir     First decription
 * 02/09/09 Arandir     Incorporated suggestions from Tijgen
 * 02/09/29 Arandir     Added items
 * 02/11/09 Arandir     Added items
 *
 */

#include "../defs.h"

inherit MT_ROOM_BASE;

inherit DG_CLOCK_LIBS;

//-------------------------------------------------------------------

string dg_long ();

//-------------------------------------------------------------------

/*
 * Function name : create_room
 *
 */

create_room ()
{
  ::create_room ();
  set_short ("a thinning forest");
  set_long  (&dg_long ());

  add_exit ("claw_1", "southeast");
  add_exit ("claw_2", "south");
  add_exit ("claw_4", "northwest");

  dg_item_sky_outside ();

  mt_item_forest_low ();
  mt_item_mountains_low ();
  mt_item_path_trodden ();
  mt_item_stream_deep ();
  mt_item_valley_far ();

  add_item (({ "slope", "surface", "rocky surface" }),
    "The slope is covered with a forest, rather dense low in the " +
    "south but thinning as the slope rises towards north.\n");
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "A dense evergreen forest covers the slope that descends " +
          "slowly towards the south. Up to the north, the trees " +
          "are gradually replaced by rocks, with only a few pines " +
          "relentlessly clinging to the rocky surface.";

  if (dg_is_winter ()) sDesc +=
    " The murmur of the cold wind passing through the treetops " +
    "mixes with the sound of cascading water, coming from the " +
    "valley to the east.";
  else
  {
    if (dg_is_night ()) sDesc +=
      " In the quiet of night, you can clearly hear the gentle " +
      "gurgle of water echoing from the valley to the east.";
    else sDesc +=
      " Occasionally, the wind carries the sound of gurgling water " +
      "and crying birds to your ears.";
  };

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
