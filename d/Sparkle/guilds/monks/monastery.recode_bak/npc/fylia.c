/*******************************************************************\
| FYLIA.C                                                           |
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

  set_name ("fylia");
  set_gender (G_FEMALE);
  set_race_name ("elf");
  set_adj (({ "lithe", "red-haired" }));
  set_long ("Highlighting her deep red hair are streaks of white, " +
            "twisting and falling around her long neck in graceful " +
            "strands. Falling about her ageless body is a soft, low-cut " +
            "robe. Her smile is otherwordly, haunting.\n");

  m_init ();
  m_equip (({ 0, 20 + random (90) }));
  m_stature (190, 75);

  // Trainer has all skills maxxed

  set_skill (SS_DEFENCE, 100);
  set_skill (SS_AWARENESS, 100);
  set_skill (SS_BLIND_COMBAT, 100);
  set_skill (SS_UNARM_COMBAT, 100);
  set_skill (M_SKILL_STRIKE, 100);
  set_skill (M_SKILL_PLEXUS, 100);

  set_act_time (10);
  add_act (({ "emote raises her hands upwards, palms outward.",
              "emote sings in a soft, strange voice.",
              "smile wearily" }));
  add_act ("stare wisely " + VBFC_ME ("dg_get_present_living_str"));
}

//-------------------------------------------------------------------

