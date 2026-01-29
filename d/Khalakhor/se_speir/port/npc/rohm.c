/*
 * rohm.c
 *
 * Bladesmith for Port MacDunn.
 * 
 * Khail - April 21/97
 * Refactored
 * Tapakah, 07/2021
 */
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>
#include <cmdparse.h>
#include <formulas.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "npc.h"

inherit BASE_NPC;
inherit "/d/Khalakhor/lib/weapon_repairs";
inherit "/d/Khalakhor/guilds/blademasters/lib/smith";

/*
 * Function name: arm_me
 * Description  : Clones in the npc's equipment
 *                and has him wear/wield it.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
arm_me ()
{
  armours = ({ "/d/Khalakhor/common/arm/vest_hard_leather",
               "/d/Khalakhor/common/arm/belt",
               "/d/Khalakhor/common/kilts/kilt_macdunn" });
  weapons = ({ "/d/Khalakhor/common/wep/claymore" });
  ::arm_me();
}

/*
 * Function name: create_khalakhor_human
 * Description  : Turns this object into an npc.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_khalakhor_human()
{
  ::create_khalakhor_human();
  add_name("smith");
  add_name("bladesmith");
  add_name("man");
  set_adj(({"muscular", "grey-haired"}));
  set_long("Years hammering out hot steel and shaping blades " +
           "in a forge have left this man heavily muscled, even " +
           "though the grey hair tied back behind his neck indicate " +
           "he's no longer a young man. Something about the way " +
           "he carries himself suggests he hasn't always been a " +
           "smith, however.\n");

  default_config_npc(60);
  set_skill(SS_AWARENESS, 50);
  set_skill(SS_UNARM_COMBAT, 30);
  set_skill(SS_DEFENCE, 50);
  set_skill(SS_WEP_SWORD, 90);

  set_alignment(400 + random(200));
  set_exp_factor(50);
  set_act_time(15);
  add_act("ponder");
 
  set_repair_base_cost(10);
  set_repair_incr_cost(2);

  create_bladesmith();

  set_size_descs("of normal length", "of normal width");
}

int
hook_return_intro_new (string str)
{
  command("greet " + str);
  command("say " +capitalize(query_name()) + " " +
          query_title() + ", what brings you to my forge?");
}

int
hook_return_intro_bad (string str)
{
  command("emote slowly tightens his fingers into a " +
          "hammer-like fist.");
  command("say I remember you, and you'd be wise to " +
          "leave because of it.");
}

int
hook_return_intro_good (string str)
{
  command("chuckle");
  command("say Just because there's snow on the roof " +
          "doesn't mean I'm losing my mind, " +
          capitalize(str) + ", I remember you.");
}
        
/*
 * Function name: init_living (MASK)
 * Description  : Called when we meet another object. Masked
 *                here to add the 'sharpen' and 'polish' commands
 *                to a player.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
init_living()
{
  ::init_living();
  init_smith_repairs("sharp");
  init_bladesmith();
}

/*
 * Function name: hook_weapon_type_fail
 * Description  : Ensures the weapon is of a type the npc can repair.
 *                For example, a bladesmith cannot 'sharpen' a club,
 *                but a blacksmith might be able to 'strengthen' it.
 * Arguments    : wep - Object pointer to the weapon to test.
 *                activity - String identifying the repair. i.e.
 *                           "sharpen" or "polish".
 * Returns      : 0 - Yes, we can perform 'activity' repair on 'wep'.
 *                1 - Fail, cannot do 'activity' on 'wep'.
 */
int
hook_weapon_type_fail(object wep, string activity)
{
  int dt;

  dt = wep->query_dt();

  /* With this particular smith, we'll fail on any weapon */
  /* that doesn't have a sharp part (i.e. isn't W_SLASH or */
  /* W_IMPALE). */
  if (!(dt & W_SLASH) && !(dt & W_IMPALE))
    {
      command("smirk");
      command("say I work on blades, not fence posts. Try the " +
              "blacksmith, maybe he can do something for you.");
      return 1;
    }
  return 0;
}
