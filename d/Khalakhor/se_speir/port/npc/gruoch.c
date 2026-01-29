/*
 * gruoch.c
 *
 * Blacksmith for Port MacDunn.
 * 
 * Khail - April 21/97
 * Refactored - Tapakah, 07/2021
 */
#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "npc.h"

inherit "/d/Khalakhor/lib/weapon_repairs";
inherit BASE_NPC;

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
  weapons = ({ "/d/Khalakhor/common/wep/smiths_hammer" });
  ::arm_me();
  command("lace vest");
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
  add_name("blacksmith");
  add_name("man");
  set_adj("tempered");
  add_adj("clean-shaven");
  set_long("The blacksmith is a well-muscled man, but there's " +
           "a strange glint in his eye every time it passes over " +
           "his forge that indicates that muscle is for hammering " +
           "iron and little else.\n");

  default_config_npc(60);
  set_skill(SS_AWARENESS, 30);
  set_skill(SS_UNARM_COMBAT, 30);
  set_skill(SS_DEFENCE, 30);
  set_skill(SS_WEP_CLUB, 30);

  set_alignment(200 + random(200));
  set_exp_factor(50);
  set_act_time(15);
  add_act("ponder");

  remembered = ([]);
  set_repair_base_cost(10);
  set_repair_incr_cost(2);

  set_size_descs("tall", "of normal width");
}

int
hook_return_intro_new (string str)
{
  command("greet " + str);
  command("say I am " + capitalize(query_name()) + " " +
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
  init_smith_repairs("blunt");
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
  /* that can't bludgeon. */
  if (!(dt & W_BLUDGEON)) {
    command("ponder");
    command("say I dunno, maybe you'd better try Rohm, " +
            "the bladesmith, he's better at that sort of thing " +
            "than I am.");
    return 1;
  }
  return 0;
}
