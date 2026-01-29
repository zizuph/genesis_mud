/*******************************************************************\
| SPIKES_5.C                                                        |
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
  set_short ("a mountain path near the mountain crest");
  set_long  (&dg_long ());

  add_exit ("spikes_4", "north");
  add_exit ("spikes_6", "south");

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

  sDesc = "A mountain path brings you high on the steep eastern " +
          "side of the valley, close to the mountain crest above.";

  if (dg_is_winter ()) sDesc +=
    " The mountain peaks to your north are shrouded in clouds, " +
    "characteristic for the harsh weather of the winter season.";
  else if (dg_is_spring ()) sDesc +=
    " The sound of the water rushing eagerly down the valley " +
    "below you is unusually loud. It is probably the shy " +
    "but persistent warmth of spring that melts the " +
    "ice and snow up in the mountains.";
  else sDesc +=
    " An occasional cry of a bird echoes off the sides of the " +
    "valley.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
