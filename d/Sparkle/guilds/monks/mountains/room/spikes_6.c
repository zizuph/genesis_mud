/*******************************************************************\
| SPIKES_6.C                                                        |
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
  set_short ("a mountain path at the mountain crest");
  set_long  (&dg_long ());

  add_exit ("spikes_5", "north");
  add_exit ("spikes_7", "northeast");

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

  sDesc = "In a sharp bend, the path crawls over the edge " +
          "of the mountain crest here. This seems to be the " +
          "only place where it is possible to descend into the " +
          "valley, even though the path looks treacherous enough " +
          "to make you doubt even that.";

  if (!dg_is_night ()) sDesc +=
    dg_normalize_room ("claw_3")->dg_get_livings (
      " As the valley opens up to the south, you notice ",
      " in the thinning forest on its side.",
      " The sides of the valley are well visible from here.");

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
