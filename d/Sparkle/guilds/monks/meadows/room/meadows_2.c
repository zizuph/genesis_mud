/*******************************************************************\
| MEADOWS_2.C                                                       |
\*******************************************************************/

/*
 * 20/08/06 Lucius	Reset herbs
 * 06/09/17 Arandir     Added herbs
 * 02/09/17 Arandir     Items added
 * 02/09/12 Arandir     Typo fixes
 * 02/06/18 Arandir     First description
 * 01/11/10 Arandir	Created
 *
 */

#include <stdproperties.h>
#include <tasks.h>

#include "../defs.h"

inherit MD_ROOM_BASE;

inherit DG_CLOCK_LIBS;

//-------------------------------------------------------------------

string dg_long ();

//-------------------------------------------------------------------

/*
 * Function name : reset_room
 */

void reset_room ()
{
    set_searched(0);
}

/*
 * Function name : create_room
 *
 */

void create_room ()
{
  ::create_room ();
  set_short ("narrow path");
  set_long  (&dg_long ());

  dg_add_herbs (DG_HERBS_MEADOW);

  add_exit ("meadows_1", "west");
  add_exit ("meadows_3", "east");

  dg_add_movement (({ DG_PATH + "/mountains/room/claw_1" }),
                   "You can see a movement in the forest below.");

  dg_add_climb (DG_PATH + "/mountains/room/claw_1",
                ({"up", "slope"}), TASK_ROUTINE,
                "You climb up the slope.",
                "climbs up the slope.",
                "arrives climbing up the slope.",
                "You try to climb up the slope but fail.",
                "tries to climb up the slope but fails.");

  dg_item_sky_outside ();

  md_item_countryside ();
  md_item_forest_south ();
  md_item_grass ();
  md_item_mountains ();
  md_item_rock_cliffs ();
  md_item_trees_cliffs ();

  add_item (({ "path", "road" }),
    "You are standing on a narrow forest path.\n");

  add_item (({ "slope", "mountain side" }),
    "The slope to your north rises slowly from the forest, " +
    "providing a navigable if not comfortable access to the " +
    "higher parts of the mountains.\n");

    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "A narrow path traces the outline of a mountain side " +
          "which slowly rises out of the forest. Belying the true " +
          "size of the mountain range to your north, the slope begins " +
          "as a scattered group of rocks that gain in height towards the " +
          "west.";

  if (dg_is_winter ()) sDesc +=
    " Twisted trees cling to life in crevices between the rocks, " +
    "battered by the cold winter winds.";
  else sDesc +=
    " Twisted trees grow in crevices between the rocks, desperately " +
    "reaching for scarce sun rays.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
