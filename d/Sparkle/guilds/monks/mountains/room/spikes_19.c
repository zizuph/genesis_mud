/*******************************************************************\
| SPIKES_19.C                                                       |
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

  add_exit ("east_cliffs_1", "northeast");
  add_exit ("spikes_18", "east");
  add_exit ("west_cliffs_1", "northeast");

  dg_item_sky_outside ();
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;
  object oMe = this_player ();

  sDesc = "You have reached the north end of the spire trail. Your breath is " +
          "coming more easily now that you have the leisure to look around " +
          "and appreciate the beauty that surrounds you.";

  if (oMe->resolve_task (DG_DIFFICULTY_KNOWNAME_HARD, DG_SKILLS_KNOWNAME)) sDesc +=
    " To your northeast, you see the forbidding cliffs that form an impassible border to the Dragon Mountains.";
  else sDesc +=
    " To your northeast, you see forbidding cliffs cutting off the mountain range.";

  sDesc += " Something makes you feel certain that travelling towards them " +
           "would be a difficult and probably dangerous endeavor. To the west, " +
           "the path seems to descend slowly towards a forested area that looks " +
           "quite inviting after the harshness of the peaks.";

  if (oMe->resolve_task (DG_DIFFICULTY_KNOWNAME_HARD, DG_SKILLS_KNOWNAME)) sDesc +=
    " Eastward, the Dragon Spikes loom before you, cast of jagged obsidian and dark grey granite, with the tear of Serpent Eye Lake below.";
  else sDesc +=
    " Eastward, the dark spires cast forbidding shadows over the valley that cradles a small lake.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------
