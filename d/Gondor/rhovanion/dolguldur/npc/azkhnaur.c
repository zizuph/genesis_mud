/*
 * Tower lord - /d/Gondor/rhovanion/dolguldur/npc/azkhnaur.c
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
   
   set_name("azkhnaur");
   add_name("half-orc");
   add_adj( ({"scarred", "black-haired"}) );
   set_title("Chief of the Bloody Eye, Captain of Dol Guldur");
   set_long("This man looks like very much like one of the " +
      "Easterlings, but you can see several orc features " +
      "beneath the scars on his face.\n");
   set_race_name("half-orc");
   set_gender(0);
   
   add_act("emote taps his fingers idly on the desk.");
   add_act("say Nobody wants to work anymore!");
   add_act("scowl");
   add_act("frown");
   add_act("emote sits down at the desk to work.");
   add_act("emote looks for something in the bookcase.");
   add_act("emote scratches a scar on his cheek.");
   add_act("say Where is my messenger to Lugburz? I sent him " +
      "months ago!");

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