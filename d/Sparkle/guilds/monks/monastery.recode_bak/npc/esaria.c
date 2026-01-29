/*******************************************************************\
| ESARIA.C                                                          |
\*******************************************************************/

/*
 * 06/09/02 Arandir     Removed the focus skill
 * 03/05/08 Arandir     Polished up
 * 02/05/02 Arandir	Ported to new area without rewrite
 * 98/10/22 Cirion	Created
 *
 */

#include <const.h>
#include <macros.h>
#include <ss_types.h>

#include "../defs.h"

inherit M_NPC_MONK_BASE;

//-------------------------------------------------------------------

void create_monster ()
{
  ::create_monster ();

  set_name ("esaria");
  set_gender (G_FEMALE);
  set_race_name ("gnome");
  set_adj (({ "short", "childlike" }));
  set_long ("Sweet and smiling, this gnome looks around her " +
            "with curious and child-like eyes. Her soft robe reaches " +
            "to the ground, so that is drags lightly along as " +
            "she moves.\n");

  m_init ();
  m_equip (({ 0, 20 + random (90) }));
  m_stature (165, 50);

  // Trainer has all skills maxed

  set_skill (SS_DEFENCE, 100);
  set_skill (SS_AWARENESS, 100);
  set_skill (SS_BLIND_COMBAT, 100);
  set_skill (SS_UNARM_COMBAT, 100);
  set_skill (M_SKILL_STRIKE, 100);
  set_skill (M_SKILL_PLEXUS, 100);

  set_act_time (10);
  add_act ("emote shuffles about.");
  add_act ("twinkle");
  add_act ("wink knowingly " + VBFC_ME ("dg_get_present_living_str"));
  add_act ("grin softly " + VBFC_ME ("dg_get_present_living_str"));
}

//-------------------------------------------------------------------

