/*******************************************************************\
| CLAW_6.C                                                          |
\*******************************************************************/

/*
 * 01/12/09 Arandir	Created
 * 02/07/04 Arandir     First decription
 * 02/09/09 Arandir     Incorporated suggestions from Tijgen
 * 04/03/13 Arandir     Unblocked the exit into new rooms
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
  set_short ("a mountain path at a bridge head");
  set_long  (&dg_long ());

  add_exit ("claw_spikes_bridge_1", "northeast");
  add_exit ("claw_5", "south");
  add_exit ("claw_12", "west");

  dg_item_sky_outside ();

  mt_item_bridge ();
  mt_item_path_trodden ();
  mt_item_stream_deep ();
  mt_item_valley_near_east ();
}


/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;
  object oMe = this_player ();

  sDesc = "The sharp turn of the path gives this place a feeling of the " +
          "very edge of the world. With the mountainside to your back, " +
          "the gorge cut into the mountains by";

  if (oMe->resolve_task (DG_DIFFICULTY_KNOWNAME_HARD, DG_SKILLS_KNOWNAME))
  {
    sDesc += " the Stream of Tears";
  }
  else
  {
    sDesc += " the noisy stream";
  };

  sDesc += " opens up right in front of you. The stream hurls " +
           "itself against the fallen rocks that have intruded " +
           "on its rough bed, bound by a thin rope bridge which " +
           "sways slowly in the howling winds. Everything around " +
           "you exists only through defying the harshness of the " +
           "mountains.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------

