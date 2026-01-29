/*******************************************************************\
| CLAW_1.C                                                          |
\*******************************************************************/

/*
 * 01/12/09 Arandir	Created
 * 02/06/27 Arandir     First decription
 * 02/09/29 Arandir     Added items
 *
 */

#include <tasks.h>

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
  set_short ("an edge of a cliff");
  set_long  (&dg_long ());

  add_exit ("claw_3", "northwest");

  dg_add_climb (DG_PATH + "/meadows/room/meadows_2",
                ({"down", "slope"}), TASK_ROUTINE,
                "You climb down the slope.",
                "climbs down the slope.",
                "arrives climbing down the slope.",
                "You try to climb down the slope but fail.",
                "tries to climb down the slope but fails.");

  dg_item_sky_outside ();

  mt_item_cliffs_meadows ();
  mt_item_forest_low ();
  mt_item_mountains_low ();
  mt_item_path_trodden ();
  mt_item_serpent_tail_west ();
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "You are standing near an edge of a cliff, which rises " +
          "steeply out of the forest below. The forest continues " +
          "a bit further away from the edge, the deciduous trees " +
          "of the lowlands giving way to sturdier evergreens. In " +
          "the distance, gurgling of a mountain brook can be heard.";

  if (dg_is_winter ()) sDesc +=
    " Even though still low in the mountains, you can feel the seeping " +
    "cold of the winter season coming upon you.";
  else sDesc +=
    " The weather is still mild this low in the mountains, but the look " +
    "of the peaks north of you tells of harsh conditions further on.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------

