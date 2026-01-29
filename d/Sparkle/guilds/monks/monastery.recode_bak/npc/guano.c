/*******************************************************************\
| GUANO.C                                                           |
\*******************************************************************/

/*
 * 06/09/02 Arandir     Removed the focus skill
 * 03/05/08 Arandir     Polished up
 * 02/05/02 Arandir	Ported to new area without rewrite
 * 98/10/22 Cirion	Created
 *
 */

#include <const.h>
#include <ss_types.h>

#include "../defs.h"

inherit M_NPC_MONK_BASE;

//-------------------------------------------------------------------

void create_monster ()
{
  ::create_monster ();

  set_name ("guano");
  set_gender (G_MALE);
  set_race_name ("goblin");
  set_adj (({ "surly", "ancient", "surly-looking" }));
  set_long ("Very short and lean, this elderly goblin's eyes show " +
            "that he has seen much of the world, and has enjoyed very " +
            "little of it. He stands in the center of the room with " +
            "a confidence and poise rare for his species.\n");

  m_init ();
  m_equip (({ 0, 20 + random (90) }));
  m_stature (155, 60);

  // Trainer has all skills maxed

  set_skill (SS_DEFENCE, 100);
  set_skill (SS_AWARENESS, 100);
  set_skill (SS_BLIND_COMBAT, 100);
  set_skill (SS_UNARM_COMBAT, 100);
  set_skill (M_SKILL_STRIKE, 100);
  set_skill (M_SKILL_PLEXUS, 100);

  set_act_time (10);
  add_act ("emote belches.");
  add_act ("snarl");
  add_act ("emote does a quick backroll on the floor.");
  add_act ("peer suspiciously");
  add_act ("emote grins unpleasantly.");
  add_act (({ "hiccup", "hiccup", "hiccup",
              "swear", "hiccup", "hiccup", "sigh" }));
  add_act ("jump");
}

//-------------------------------------------------------------------

