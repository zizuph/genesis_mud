/*******************************************************************\
| CLAW_SPIKES_BRIDGE.C                                              |
\*******************************************************************/

/*
 * 01/12/09 Arandir	Created
 * 02/07/20 Arandir	First description
 * 02/09/10 Arandir     Incorporated suggestions by Tijgen
 * 02/11/09 Arandir     Added items
 *
 */

#include "../defs.h"

inherit MT_ROOM_BRIDGE_BASE;

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
  set_short ("a rope bridge");
  set_long  (&dg_long ());

  add_exit ("spikes_1", "northeast");
  add_exit ("claw_6", "southwest");

  dg_item_sky_outside ();

  mt_item_bridge ();
  mt_item_stream_deep ();
  mt_item_valley_below ();
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "A narrow rope bridge slowly sways in the wind that " +
          "whistles through the canyon below.";

  if (dg_is_night ()) sDesc +=
    " The motion is made worse by the fact that you cannot see " +
    "beyond few meters in any direction, and can only imagine the " +
    "true depth below you.";
  else
  {
    if (dg_is_winter ()) sDesc +=
      " Some of the ropes are covered with a thin sheet of ice, " +
      "making the bridge slippery. Icicles have formed even " +
      "underneath some of the planks below you.";
    else sDesc +=
      " Through the planks, you can see the stream whose incessant " +
      "passage gave rise to this whole valley.";
  };

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
