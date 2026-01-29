/*
 * miach.c
 *
 * Landlord for the village pub in Tabor Sagh.
 *
 * Khail - April 4/97
 * Zima  - March 15/98
 * Refactored
 * Tapakah, 07/2021
 */

#pragma strict_types
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "npc.h"
 
inherit BASE_NPC;
inherit "/d/Khalakhor/se_speir/common/landlord.c";
 
void
arm_me ()
{
  armours = ({ "/d/Khalakhor/common/arm/shirt_cloth",
               "/d/Khalakhor/common/arm/belt",
               "/d/Khalakhor/common/kilts/kilt_tabor" });
  ::arm_me();
}
 
/*
 * Function name: create_khalakhor_human
 * Description  : Turns this object into a landlord.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_khalakhor_human ()
{
  explicit_name = "miach";
  ::create_khalakhor_human();
  add_name("landlord");
  add_name("man");
  set_adj("thin");
  add_adj("cheerful");
  set_long("For a man whose entire life revolves around " +
           "food, he seems to fit into rather small clothes. He's " +
           "thin as a reed! The broken blood vessels in his nose, " +
           "however, tend to indicate his indulgences lie more " +
           "within the liquid portion of his menu.\n");
  
  default_config_npc(40);
  set_skill(SS_AWARENESS, 75);
  set_skill(SS_UNARM_COMBAT, 30);
  set_skill(SS_DEFENCE, 30);
  set_skill(SS_WEP_SWORD, 35);
  
  set_alignment(400);
  set_exp_factor(50);
  set_size_descs("tall", "skinny");
  remembered = ([]);
}
 
void
hook_return_intro_new (string str)
{
  command("say Good day, " + capitalize(str) +
          "! I'm " + query_name() + ", " + query_name() +
          " "+query_title()+", and welcome "+
          "to The Summer Squall. What can I get for you?");
  command("bow " + str);
}

void
hook_return_intro_bad (string str)
{
  command("growl");
  command("say I know who you are, you bully. Now buy " +
          "something and leave!");
}

void
hook_return_intro_good (string str)
{
  command("grin misch");
  command("say I may have a few blank spots in my memory, " +
          capitalize(str) + ", but I remember you. What'll it " +
          "be this time?");
  command("smile bright");
}
