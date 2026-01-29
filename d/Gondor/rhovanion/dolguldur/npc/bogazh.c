/*
 * Trainer - /d/Gondor/rhovanion/dolguldur/npc/bogazh.c
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
   
   set_name("bogazh");
   add_name( ({"orc", "trainer"}) );
   add_adj( ({"massive", "menacing"}) );
   set_long("This uruk is busy training the soldiers of Dol Guldur.\n");
   set_race_name("uruk");
   set_gender(0);
   
   add_act("emote swings his axe through a complex series of strokes.");
   add_act("say You maggots are lucky I don't kill you all!");
   add_act("scowl");
   add_act("say Who's next?");
   add_act("burp");
   add_act("fart");
   add_act("emote gives a blood-curlding war cry!");
   add_act("yawn");

   set_act_time(10);
   
   set_skill(SS_WEP_AXE, 95);
   set_skill(SS_DEFENCE, 95);
   set_skill(SS_PARRY, 95);

   set_stats(({ 200, 200, 200, 110, 110, 200}), 10);
   
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