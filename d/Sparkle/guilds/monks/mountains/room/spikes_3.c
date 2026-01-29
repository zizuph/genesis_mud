/*******************************************************************\
| SPIKES_3.C                                                        |
\*******************************************************************/

/*
 * 01/12/09 Arandir	Created
 * 02/07/17 Arandir     First description
 * 02/09/10 Arandir     Incorporated suggestions by Tijgen
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
  set_short ("a mountain path on a narrow ledge");
  set_long  (&dg_long ());

  add_exit ("spikes_2", "north");
  add_exit ("spikes_4", "south");

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

  sDesc = "The mountain ledge you are standing on provides you with " +
          "a few precarious footholds.";

  if (dg_is_winter ()) sDesc +=
    " Not really reassuring in the icy winter weather, which " +
    "covers everything with a thin sheet of ice.";
  else
  {
    if (dg_is_night ()) sDesc +=
      " The depth of the valley below you is enshrouded " +
      "in the darkness of night.";
    else sDesc +=
      " At the edge of the path starts a drop to the depths of the " +
      "valley below, causing your stomach to reel and forcing you " +
      "to look away.";
  };

  sDesc += " The path rises upwards as it nears the crest of the " +
           "mountain that towers above you to the east.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
