/*
 * brom.c
 *
 * Shopkeeper for the village shop in Port MacDunn.
 *
 * Khail - April 1/97
 * Zima  - June 16/98 - made Brom a recipient of a letter in postman tour
 * Tapakah - July 2021 - complete refactoring.
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
 * Description  : Clones in the shopkeeper's equipment
 *                and has him wear/wield it.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
arm_me ()
{
  armours = ({ "/d/Khalakhor/common/arm/shirt_wool",
               "/d/Khalakhor/common/arm/belt",
               "/d/Khalakhor/common/kilts/kilt_macdunn" });
  ::arm_me();
}
 
/*
 * Function name: create_khalakhor_human
 * Description  : Turns this object into a shopkeeper.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_khalakhor_human ()
{
  ::create_khalakhor_human();
  add_name("shopkeeper");
  add_name("man");
  set_adj("fat");
  add_adj("red-bearded");
  set_long("The man appears to have seen little, if any, " +
           "exercise in years. You notice as he moves " +
           "around the rippling of muscle beneath a layer of fat, " +
           "and suspect a few years ago his build might have been " +
           "quite different.\n");
 
  default_config_npc(40);
  set_skill(SS_AWARENESS, 75);
  set_skill(SS_UNARM_COMBAT, 30);
  set_skill(SS_DEFENCE, 30);
  set_skill(SS_WEP_SWORD, 35);
 
  set_alignment(400);
  set_exp_factor(50);
 
  set_act_time(15);
  add_act("emote chuckles softly to himself.");
  add_act("say All these ships from different lands has been " +
          "great for business!");
  add_act("say Have you ever seen a shadow that looked like " +
          "it was moving around? I did once, far to the north.");
  add_act("say Rumour has it the Clans will go to war " +
          "soon, I wonder which ones.");
  add_act("ponder");
  add_cact("say Oh, so it's a fight you want, is it?");
  add_cact("emote growls.");
 
  remembered = ([]);
 
  set_size_descs("short", "plump");
 
  remove_prop(NPC_M_NO_ACCEPT_GIVE); // handled by enter_inv()
}

int
hook_return_intro_new (string str)
{
  command("say Ahh, pleased to meet you, " + capitalize(str) +
          ", " + query_name() + " " + query_title() +
          ", at your service.");
  command("bow " + str);
}

void
hook_return_intro_bad (string str)
{
  command("growl");
  command("say I remember you, thug, what do you want this " +
          "time?");
}

void
hook_return_intro_good (string str)
{
  command("chuckle");
  command("say My memory might be short, " + capitalize(str) +
          ", but I still remember you from your last visit. What " +
          "can I do for you?");
}

