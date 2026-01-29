/*******************************************************************\
| MEADOWS_1.C                                                       |
\*******************************************************************/

/*
 * 20/08/06 Lucius	Reset herbs
 * 06/09/17 Arandir     Added herbs
 * 02/09/29 Arandir     Added items
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
  set_short ("forest clearing");
  set_long  (&dg_long ());

  dg_add_herbs (DG_HERBS_MEADOW);

  add_exit ("meadows_2", "east");

  dg_add_movement (({ DG_PATH + "/mountains/room/claw_2" }),
                   "You can see a movement on the clearing below.");

  dg_add_climb (DG_PATH + "/mountains/room/claw_2",
                ({"up", "slope", "cliff", "slide", "rockslide", "chimney"}), TASK_ROUTINE,
                "You climb up the steep slope.",
                "climbs up the steep slope.",
                "arrives climbing up the steep slope.",
                "You try to climb up the steep slope but fail.",
                "tries to climb up the steep slope but fails.");

  dg_item_sky_outside ();

  md_item_forest_south ();
  md_item_grass ();
  md_item_mountains ();
  md_item_rock_cliffs ();

  add_item (({ "clearing" }),
    "A small forest clearing opens around you. From the north, " +
    "it is sheltered by a rather steep cliff, forest trees " +
    "enclose it from all other sides.\n");

  add_item (({ "cliff", "cliffs", "cliffside" }),
    "The cliffs to your north and west are just a small " +
    "beginning of a vast mountain range which spans the " +
    "northern horizon. The rock is weathered and would be " +
    "dangerous to climb, if it were not for wide cracks that " +
    "scar the cliffside.\n");

  add_item (({ "crack", "cracks", "chimney", "chimneys", "slope", "slide", "rockslide", "rockslides" }),
    "Wide cracks form chimneys and rockslides, in places " +
    "turning the impassable cliffside into a steep rocky " +
    "slope.\n");

  add_item (({ "path", "road" }),
    "A narrow forest path is to your east.\n");

    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "A small forest clearing opens at the end of a narrow " +
          "path.";

  if (dg_is_afternoon ()) sDesc +=
    " A nearby cliffside protects the clearing from the afternoon " +
    "sun, casting a shadow that grows longer as the day progresses.";
  else sDesc +=
    " A cliffside towers over the clearing to the north and west.";

  if (dg_is_winter ()) sDesc +=
    " The ground is covered by grass, brownish and fragile in " +
    "the winter season.";
  else sDesc +=
    " The ground is covered by green grass, here and there trampled " +
    "by the passing animals that live in the forest.";

  if (!dg_is_night ()) sDesc +=
    dg_normalize_room ("meadows_2")->dg_get_livings (
      " You can see ", " on the path to the east.", "");

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
