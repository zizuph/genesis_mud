/*
 * Tavern owner - /d/Gondor/rhovanion/dolguldur/npc/norgsh.c
 *
 * Varian - November 2020
 */

#pragma strict_types

inherit "/std/monster.c";
inherit "/d/Gondor/common/lib/friend_or_foe.c";

#include "/d/Gondor/rhovanion/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/sys/ss_types.h"

void arm_me();

void
create_monster()
{
   
   set_name("norgsh");
   add_name("orc");
   add_adj( ({"tall", "black-skinned"}) );
   set_title("Proud Owner of the Rusty Axe");
   set_long("This tall orc is the owner of the Rusty Axe tavern, "+
      "and he doesn't appear to be picky about his customers.\n");
   set_race_name("uruk");
   set_gender(0);
   
   add_act("emote pretends to clean a mug before filling it with ale.");
   add_act("say The elf steak is fresh, harvested just a week ago!");
   add_act("emote picks his nose.");
   add_act("say You look thirsty, how about a drink?");
   add_act("say I was very lucky to find this nice wooden bar intact!");
   add_act("say I spent a lot of time and money fixing this place up!");
   add_act("emote screams at the patrons who just broke some " +
      "of his furniture.");
   add_act("shout Settle down you bloody fools! There is enough ale " +
      "for everyone!");

   set_act_time(10);
   
   set_skill(SS_WEP_AXE, 70);
   set_skill(SS_DEFENCE, 70);

   set_stats(({ 100, 100, 100, 110, 110, 100}), 10);
   
   set_alignment(-150);
   
   set_alarm(0.5,0.0,"arm_me");

}

void
arm_me()
{
   object axe, shirt, pants;

   FIXEUID;

   axe = clone_object(DG_DIR + "wep/axe.c");
   shirt = clone_object(DG_DIR + "arm/shirt.c");
   pants = clone_object(DG_DIR + "arm/pants.c");

   axe->move(TO);
   shirt->move(TO);
   pants->move(TO);   

   command("wear all");
   command("wield all");
}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}