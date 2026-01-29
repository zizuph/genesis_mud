/*******************************************************************\
| TRAINING_DEFENCE.C                                                |
\*******************************************************************/

/*
 * 08/02/02 Arandir     Removed extra newline typo
 * 04/08/15 Arandir     Added the missing inside property
 * 03/04/29 Arandir     Polished up
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 98/06/14 Cirion	Created
 *
 */

#include <ss_types.h>
#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_TRAINING_BASE;

inherit DG_OBJ_LIBS;

//-------------------------------------------------------------------

private object oSamir;

void reset_room();

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("granite stone building");
  set_long ("Covering the floor of this large, one-room stone " +
            "building is a carpet of dried reeds, which crackle " +
            "underfoot. " +
            dg_embed_composite () +
            "Sunlight from the garden to the southwest, as well " +
            "as the three small windows in each of the other " +
            "walls, give a good illumination to this room.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("garden", "southwest");

  dg_add_entrance ("southwest",
                   "As you enter the granite stone building, " +
                   "the dry reeds of the floor crackle noisly.");

  reset_room ();

  m_training_setup (SS_LAYMAN, ({ SS_DEFENCE }), oSamir);
  m_training_setup (SS_OCCUP, ({ SS_DEFENCE }), oSamir);
}

//-------------------------------------------------------------------

void reset_room ()
{
  ::reset_room ();

  if (!oSamir)
  {
    oSamir = dg_clone_here (M_PATH_NPC + "/samir", "arm_me",
      "Standing in the center of the room is a stern, confident human " +
      "with dark skin and blue eyes. ");
  };

  if (!present (oSamir))
  {
    oSamir->move_living ("away", this_object ());
  };
}

//-------------------------------------------------------------------

