/*
 * Merchant - /d/Gondor/rhovanion/dolguldur/npc/rushk.c
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
   
   set_name("rushk");
   add_name("orc");
   add_adj( ({"scarred", "one-eyed"}) );
   set_title("the Merchant of Dol Guldur");
   set_long("This uruk appears to have seen a few battles, but it appears " +
      "that what he is really looking for is more gold. He seems to be " +
      "the owner of a successful general store in Dol Guldur.\n");
   set_race_name("uruk");
   set_gender(0);
   
   add_act("emote gives you a small, subtle smile.");
   add_act("emote stares confidently at you with piercing eyes.");
   add_act("scratch nose");
   add_act("say Have you got anything to sell? Or perhaps you want to buy?");
   add_act("burp");
   add_act("fart");
   add_act("emote looks you over carefully, assessing you.");
   add_act("yawn");

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