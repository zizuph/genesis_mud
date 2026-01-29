/*******************************************************************\
| SPIKES_14.C                                                       |
\*******************************************************************/

/*
 * 20/08/06 Lucius      Reset herbs
 * 07/06/24 Arandir     Created from description by Sionell
 *
 */

#include "../defs.h"

inherit MT_ROOM_BASE;

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
  set_short ("");
  set_long  (&dg_long ());

  dg_add_herbs (DG_HERBS_CLIFFS);

  add_exit ("spikes_13", "southwest");
  add_exit ("spikes_15", "west");

  dg_item_sky_outside ();
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "You pass carefully between two jagged spires, coming out on the " +
          "eastern edge with barely tenable foot and hand holds keeping you " +
          "fastened to the rock face.";

  if (dg_is_night ()) sDesc +=
    " Darkness is all around, it is difficult to see very far.";
  else sDesc +=
    " The view here is spectacular. Volcanic rock, flecked with obsidian " +
    "gleams in the sun, casting bewitching flashes in your eyes.";

  sDesc += " The wind whips harshly around and between the spires, " +
           "convincing you that this is not a  good place for a long pause.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
