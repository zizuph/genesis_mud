/*******************************************************************\
| SPIKES_1.C                                                        |
\*******************************************************************/

/*
 * 06/09/03 Arandir     Fixed a typo
 * 03/09/14 Arandir     Fixed a direction in the desc
 * 02/07/06 Arandir     First description
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
 * Function name : create_room
 *
 */

void create_room ()
{
  ::create_room ();
  set_short ("a mountain path at a bridge head");
  set_long  (&dg_long ());

  add_exit ("spikes_2", "east");
  add_exit ("claw_spikes_bridge_1", "southwest");

  dg_item_sky_outside ();

  mt_item_bridge ();
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

  sDesc = "The narrow path ends on an inhospitable ledge, buffeted " +
          "by winds that rock the nearby rope bridge. The bridge " +
          "is suspended over the deep gorge to the west, providing " +
          "passage to whomever dares tread its swaying length to the " +
          "other side. The path continues along the cliff to the east.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------

