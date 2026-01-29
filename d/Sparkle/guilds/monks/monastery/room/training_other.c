/*******************************************************************\
| TRAINING_OTHER.C                                                  |
\*******************************************************************/

/*
 * 08/02/02 Arandir     Removed extra newline typo
 * 06/09/02 Arandir     Moved the awareness training elsewhere
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

private object oEsaria;

void reset_room ();

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("stone building");
  set_long ("The walls of this one-room stone building are made " +
            "from soft grey basalt. " +
            dg_embed_composite () +
            "The floor is uncovered gravel, and a wide doorway " +
            "leads out to the northwest into the brightly-lit " +
            "garden.\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("garden", "northwest");

  dg_add_entrance ("northwest", "You enter the basalt stone building.");

  reset_room ();

  m_training_setup (SS_LAYMAN,
                    ({ SS_HERBALISM, SS_APPR_OBJ, SS_APPR_MON,
                       SS_ELEMENT_AIR, SS_FORM_DIVINATION }),
                    oEsaria);
  m_training_setup (SS_OCCUP,
                    ({ SS_HERBALISM, SS_APPR_OBJ, SS_APPR_MON,
                       SS_ELEMENT_AIR, SS_FORM_DIVINATION }),
                    oEsaria);
}

//-------------------------------------------------------------------

void reset_room ()
{
  ::reset_room ();

  if (!oEsaria)
  {
    oEsaria = dg_clone_here (M_PATH_NPC + "/esaria", "arm_me",
      "Leaning against the corner of the room is a smiling, " +
      "childlike female gnome. ");
  };

  if (!present (oEsaria))
  {
    oEsaria->move_living ("away", this_object ());
  };
}

//-------------------------------------------------------------------

