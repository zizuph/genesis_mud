/*******************************************************************\
| CLAW_4.C                                                          |
\*******************************************************************/

/*
 * 01/12/09 Arandir	Created
 * 02/07/03 Arandir     First decription
 * 02/09/09 Arandir     Incorporated suggestions from Tijgen
 * 02/09/29 Arandir     Added items
 * 02/11/09 Arandir     Added items
 *
 */

#include <tasks.h>
#include <ss_types.h>

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
  set_short ("a mountain slope");
  set_long  (&dg_long ());

  dg_add_movement (({ "spikes_5" }),
    "You notice a movement on the mountain slope across the valley.");

  add_exit ("claw_5", "north");
  add_exit ("claw_3", "southeast");

  dg_item_sky_outside ();

  mt_item_forest_medium ();
  mt_item_path_trodden ();
  mt_item_stream_deep ();
  mt_item_valley_far ();

  add_item (({ "slope", "surface", "rocky surface" }),
    "The slope is covered with scattered trees, thinning as the " +
    "slope rises towards north.\n");
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;
  object oMe = this_player ();

  if (dg_is_winter ()) sDesc =
    "The harsh winter weather has leeched the life from the " +
    "greenery that dominated the ground around you.";
  else sDesc =
    "The greenery around you is scarred from battling the elements " +
    "during the past winters.";

  sDesc += " Here and there, a twisted, stunted pine or alder tree can " +
           "be seen. Soft leaves of cudweed cover sparse patches " +
           "of soil lodged in the cracks of the rock.";

  if (dg_is_night ()) sDesc +=
    " Even in the dark of night, you feel the empty space to your " +
    "east, where a deep valley opens.";
  else
  {
    sDesc += " To your east is a deep valley with a stream at " +
             "its bottom.";
    if (oMe->resolve_task (DG_DIFFICULTY_KNOWNAME_HARD, DG_SKILLS_KNOWNAME))
    {
      sDesc += " Further to the west, jagged cliffs, called Claws " +
               "because of their uncanny resemblance to huge talons, " +
               "can be seen.";
    }
    else
    {
      sDesc += " Further to the west, jagged cliffs can be seen.";
    };
  };

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
