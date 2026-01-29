/*******************************************************************\
| CLAW_5.C                                                          |
\*******************************************************************/

/*
 * 01/12/09 Arandir	Created
 * 02/07/04 Arandir     First decription
 * 02/09/09 Arandir     Incorporated suggestions from Tijgen
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

void create_room ()
{
  ::create_room ();
  set_short ("a mountain path");
  set_long  (&dg_long ());

  dg_add_movement (({ "spikes_4" }),
                   "You notice a movement on the winding path across the valley.");

  add_exit ("claw_6", "north");
  add_exit ("claw_4", "south");

  dg_item_sky_outside ();

  mt_item_forest_medium ();
  mt_item_path_trodden ();
  mt_item_stream_deep ();
  mt_item_valley_near_east ();

  add_item (({ "cliff", "cliff face" }),
    "A steep cliff face towers to your west. It is bare of any " +
    "holds, be it for human hands, animal feet or plant roots.\n");
}


/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "A large cliff face rises to the west, blocking all " +
          "progress but up a narrow path,";

  if (dg_is_winter ()) sDesc +=
    " slippery in the cold winter weather.";
  else sDesc +=
    " treacherous with bits and pieces of weathered stone.";

  sDesc += " As it winds along the mountainside, the path brings you " +
           "rather high on the steep walls of the gorge hollowed " +
           "by a noisy stream below.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------

