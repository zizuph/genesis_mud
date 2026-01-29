/*******************************************************************\
| BASE_ROOM_TRAINING.C                                              |
+-------------------------------------------------------------------+
| Base room module for trainings in the monk area.                  |
\*******************************************************************/

/*
 * 03/04/29 Arandir	Created
 *
 */

#include "../defs.h"

inherit M_ROOM_BASE;

inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

varargs void m_training_setup (int iType, int *aiSkills, object oTrainer = NULL)
{
  object oTraining;

  DG_FIXUID;

  oTraining = clone_object (M_HOOK_TRAINING);
  oTraining->m_training_setup (iType, aiSkills, oTrainer);
  oTraining->move (this_object ());
}

//-------------------------------------------------------------------

