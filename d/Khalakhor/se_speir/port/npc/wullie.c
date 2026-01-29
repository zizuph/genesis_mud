/*
 * wullie.c
 *
 * Harbour master for Port MacDunn.
 * 
 * Khail - April 21/97
 * Refactored
 * Tapakah - 07/2021
 */
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "npc.h"

inherit BASE_NPC;

/*
 * Function name: arm_me
 * Description  : Clones in the harbour master's equipment
 *                and has him wear/wield it.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
arm_me ()
{
  armours = ({ "/d/Khalakhor/common/arm/shirt_wool",
               "/d/Khalakhor/common/arm/belt",
               "/d/Khalakhor/common/kilts/kilt_maccrimmon" });
  ::arm_me();
}

/*
 * Function name: add_shipline_asks
 * Description  : Sets up add_asks for directions to several
 *                ports around Genesis.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
add_shipline_asks()
{
  set_default_answer("say Please consult the timetable, or get a leaflet "+
                     "from my desk.", 1);
}

/*
 * Function name: create_khalakhor_human
 * Description  : Turns this object into a shopkeeper.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_khalakhor_human()
{
  ::create_khalakhor_human();
  add_name("master");
  add_name("harbour master");
  add_name("man");
  set_adj("lean");
  add_adj("stone-faced");
  set_long("This man appears to be cut from stone, and " +
           "has eyes that could pin a man to a wall. His face is " +
           "deeply tanned and lined from years of exposure to " +
           "the salt water of the seas.\n");

  default_config_npc(40);
  set_skill(SS_AWARENESS, 50);
  set_skill(SS_UNARM_COMBAT, 30);
  set_skill(SS_DEFENCE, 20);
  set_skill(SS_WEP_SWORD, 25);

  set_alignment(200 + random(200));
  set_exp_factor(50);
  set_act_time(15);
  add_act("ponder");
  add_act("emote shuffles through some papers.");
  add_act("say Few people knew as much about the ports " +
          "and ships of the lands as I do. " +
          "But my life has been made even easier now.");
  add_act("smile");
  add_act("point timetable");
  add_act("say Consult the timetable for local ships.");
  add_shipline_asks();

  remembered = ([]);

  set_size_descs("tall", "of normal width");
}

void
hook_return_intro_new (string str)
{
  command("say Welcome to Port Macdunn, " + capitalize(str) +
          ". " + query_name() + " " + query_title() + 
          ", at your service.");
}

void
hook_return_intro_bad (string str)
{
  command("smirk");
  command("say Piss off, before they're dragging your " +
          "body from under the piers!");
}

void
hook_return_intro_good (string str)
{
  command("say Yes, yes, I know who you are, " +
          capitalize(str) + ", what do you want this time?");
}

