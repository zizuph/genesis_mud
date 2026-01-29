/*******************************************************************\
| HOOK_TRAINING_OCCUPATINAL.C                                       |
\*******************************************************************/

/*
 * 99/02/22 Cirion      Created
 * 03/04/29 Arandir	Created
 *
 */

#include <ss_types.h>

#include "../defs.h"
#include "hook_training.h"

inherit M_HOOK_TRAINING;

//-------------------------------------------------------------------

void create_object ()
{
  ::create_object ();
  m_training_setup (SS_OCCUP, M_SKILL_LIST, NULL);
}

//-------------------------------------------------------------------

