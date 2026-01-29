/*******************************************************************\
| SAMIR.C                                                           |
\*******************************************************************/

/*
 * 06/09/02 Arandir     Removed the focus skill
 * 03/05/08 Arandir     Polished up
 * 02/05/02 Arandir	Ported to new area without rewrite
 * 00/12/26 Manat	Fixed a typo
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

  set_name ("samir");
  set_gender (G_MALE);
  set_race_name ("human");
  set_adj (({ "dark-skinned", "bald" }));
  set_long ("Deep, sky-blue eyes clash with the deep brown skin " +
            "of this tall and imposing human. He looks about him with " +
            "confidence and wisdom, his strength and speed apparent " +
            "beneath his flowing robe.\n");

  m_init ();
  m_equip (({ 0, 20 + random (90) }));
  m_stature (200, 130);

  // Trainer has all skills maxed

  set_skill (SS_DEFENCE, 100);
  set_skill (SS_AWARENESS, 100);
  set_skill (SS_BLIND_COMBAT, 100);
  set_skill (SS_UNARM_COMBAT, 100);
  set_skill (M_SKILL_STRIKE, 100);
  set_skill (M_SKILL_PLEXUS, 100);

  set_act_time (10);
  add_act (({ "emote kneels upon the floor.",
              "emote whispers a brief prayer.",
              "emote rises and look around with renewed strength." }));
  add_act ("smile confidently " + VBFC_ME ("dg_get_present_living_str"));
  add_act ("emote executes a quick and expert defensive roll on the floor.");
  add_act ("emote clenches his fists.");
}

//-------------------------------------------------------------------

