/*******************************************************************\
| TRAINING_FOCUS.C                                                  |
\*******************************************************************/

/*
 * 08/02/02 Arandir     Removed extra newline typo
 * 06/09/02 Arandir     Replaced focus with awareness
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

private object oFylia;

void reset_room();

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("dark stone building");
  set_long ("Gloom and shadows pervade this place. Shadows " +
            "seem to cling to every corner of the room. The " +
            "very air seems laden with dragon sighs.\n");

  add_prop (ROOM_I_INSIDE, TRUE);
  add_prop (ROOM_I_LIGHT, -20);

  add_exit ("garden", "northeast");

  dg_add_entrance ("northeast",
                   "As you pass through the doorway to the " +
                   "shale building, you are suddenly engulfed " +
                   "in impenetrable shadows.");

  reset_room ();

  m_training_setup (SS_LAYMAN, ({ SS_AWARENESS, SS_BLIND_COMBAT }), oFylia);
  m_training_setup (SS_OCCUP, ({ SS_AWARENESS, SS_BLIND_COMBAT }), oFylia);
}

//-------------------------------------------------------------------

void reset_room ()
{
  ::reset_room ();

  if (!oFylia)
  {
    oFylia = dg_clone_here (M_PATH_NPC + "/fylia", "arm_me");
  };

  if (!present (oFylia))
  {
    oFylia->move_living ("away", this_object ());
  };
}

//-------------------------------------------------------------------

