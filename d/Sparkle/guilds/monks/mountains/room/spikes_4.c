/*******************************************************************\
| SPIKES_4.C                                                        |
\*******************************************************************/

/*
 * 01/12/09 Arandir	Created
 * 02/07/17 Arandir     First description
 * 03/09/14 Arandir     Added a missing item
 *
 */

#include "../defs.h"

inherit MT_ROOM_BASE;

inherit DG_CLOCK_LIBS;
inherit DG_PLAYER_LIBS;

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
  set_short ("a small level area on a mountain path");
  set_long  (&dg_long ());

  add_exit ("spikes_3", "north");
  add_exit ("spikes_5", "south");

  dg_item_sky_outside ();

  mt_item_cliffs_valley ();
  mt_item_path_trodden ();
  mt_item_stream_deep ();
  mt_item_valley_near_west ();

  add_item (({ "tree", "pine tree", "lonely tree", "solitary tree" }),
            "A solitary pine tree clings to life nearby, twisted " +
            "by the harsh conditions to a shape that is both " +
            "sorrowful and beautiful.\n");
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "Yet another twist of the mountain path brings you " +
          "to a small level spot, formed by bits of soil caught " +
          "on a rocky outcropping.";

  if (sizeof (dg_get_present_livings ()) == 1) sDesc +=
    " A solitary pine tree is your only companion, underscoring " +
    "the atmosphere of loneliness that radiates from everything " +
    "around you.";
  else
  {
    if (dg_is_night ()) sDesc +=
      " Silent whispers of wind in the branches of a nearby " +
      "tree give this place an atmosphere of loneliness.";
    else sDesc +=
      " A solitary pine tree manages to survive nearby.";
  };

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------

