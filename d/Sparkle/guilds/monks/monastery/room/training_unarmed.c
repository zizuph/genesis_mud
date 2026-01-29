/*******************************************************************\
| TRAINING_UNARMED.C                                                |
\*******************************************************************/

/*
 * 08/02/02 Arandir     Removed extra newline typo
 * 06/09/13 Arandir     Removed the polearm skill
 * 04/08/15 Arandir     Added the missing inside property
 * 03/04/29 Arandir     Polished up and bugfixed
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

private object oGuano;

void reset_room ();

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("stone building");
  set_long ("This is a large, one-room stone building. The floor " +
            "is made from very smooth, almost soft, stone. The walls " +
            "of the building are made from rough blocks of granite. " +
            dg_embed_composite () +
            "A narrow doorway leads out into a wide garden to the " +
            "southeast.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("garden", "southeast");

  dg_add_entrance ("southeast", "You enter the cool stone building.");

  reset_room ();

  m_training_setup (SS_LAYMAN,
                    ({ SS_UNARM_COMBAT, M_SKILL_STRIKE, M_SKILL_PLEXUS }),
                    oGuano);
  m_training_setup (SS_OCCUP,
                    ({ SS_UNARM_COMBAT, M_SKILL_STRIKE, M_SKILL_PLEXUS }),
                    oGuano);
}

//-------------------------------------------------------------------

void reset_room ()
{
  ::reset_room ();

  if (!oGuano)
  {
    oGuano = dg_clone_here (M_PATH_NPC + "/guano", "arm_me",
      "Standing in the center of the room is an ancient " +
      "and surly-looking goblin. ");
  };

  if (!present (oGuano))
  {
    oGuano->move_living ("away", this_object ());
  };
}

//-------------------------------------------------------------------

