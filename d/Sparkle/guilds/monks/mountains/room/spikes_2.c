/*******************************************************************\
| SPIKES_2.C                                                        |
\*******************************************************************/

/*
 * 01/12/09 Arandir	Created
 * 02/07/17 Arandir     First description
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

void create_room ()
{
  ::create_room ();
  set_short ("a mountain path in a narrow chimney");
  set_long  (&dg_long ());

  add_exit ("spikes_1", "west");
  add_exit ("spikes_3", "south");

  dg_item_sky_outside ();

  mt_item_cliffs_valley ();
  mt_item_path_trodden ();
  mt_item_stream_deep ();
  mt_item_valley_near_west ();
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "You are wedged in a narrow chimney where the mountain " +
          "path takes a sharp turn as it lines the mountain side.";

  if (dg_is_night ()) sDesc +=
    " The cold night air drifts up from the valley, carrying with " +
    "it the sound of running water.";
  else sDesc +=
    " The silvery line of the mountain stream is visible way " +
    "below you in the valley. Lifting your gaze, you can also " +
    "see the narrow rope bridge, a lifeline connecting this part " +
    "of the mountains with the lowlands to the south.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
