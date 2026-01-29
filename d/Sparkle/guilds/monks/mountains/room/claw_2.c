/*******************************************************************\
| CLAW_2.C                                                          |
\*******************************************************************/

/*
 * 01/12/09 Arandir	Created
 * 02/06/27 Arandir     First decription
 * 02/09/09 Arandir     Incorporated suggestions from Tijgen
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

  add_exit ("claw_3", "north");

  dg_add_climb (DG_PATH + "/meadows/room/meadows_1",
                ({"down", "slope"}), TASK_ROUTINE,
                "You climb down the steep slope.",
                "climbs down the steep slope.",
                "arrives climbing down the steep slope.",
                "You try to climb down the steep slope but fail.",
                "tries to climb down the steep slope but fails.");

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

  sDesc = "You are next to the edge of a low cliff, slowly rising " +
          "from the forest below. The forest continues to grow " +
          "wherever a bit of soil lodges in the cracks between " +
          "rocks.";

 if (dg_is_night ()) sDesc +=
   " In the quiet of night, sounds of animals both near and far " +
   "echo off the cliff faces.";
 else if (dg_is_evening ()) sDesc +=
   " Squinting against the rays of the setting sun, you can see " +
   "an outline of a tall mountain peak.";
 else
 {
   if (dg_is_summer ()) sDesc +=
     " A tall peak rises in the west, clearly outlined against " +
     "the summer sky.";
   else sDesc +=
     " A tall peak rises in the west, shrouded in mist that " +
     "makes it hard to see the very top.";
 };

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
