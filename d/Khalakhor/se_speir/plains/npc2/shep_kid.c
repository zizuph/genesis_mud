//
// shepherd's kid - a little brat
//
// Zima  - May 18, 1998
//
#pragma strict_types
 
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "npc.h"
 
inherit STDHUMAN;
inherit "/d/Khalakhor/lib/clan_support";
inherit "/d/Khalakhor/se_speir/port/npc/help_me";
 
int has_armed=0;
 
//
// arm_me
//
public void arm_me()
{
    if (has_armed) return;
    seteuid(getuid());
    if (query_gender())
       {
       clone_object("/d/Khalakhor/common/arm/dress")->move(TO);
       }
    else
       {
       clone_object("/d/Khalakhor/common/arm/shirt_cloth")->move(TO);
       clone_object("/d/Khalakhor/common/kilts/kilt_tabor")->move(TO);
       }
    command("wield all");
    command("wear all");
    has_armed = 1;
}
 
//
// create_khalakhor_human
//
public void create_khalakhor_human()
{
    set_gender(random(2));
    set_name("raymund");
    add_name(({"child","shepherd"}));
    set_adj("skinny");
    add_adj("red-headed");
    cs_set_sept("Gilvary");
    cs_set_clan("Tabor");
    cs_set_title("the Shepherd's Kid");

    if (query_gender())
       {
       set_long(
          "She is the child of a shepherd, at home roaming the grassy "+
          "plains and annoying the sheep. She has a devilish smile on her "+
          "innocent face.\n");
       set_short("red-headed girl");
       add_name("girl");
       }
    else
       {
       set_long(
          "He is the child of a shepherd, at home roaming the grassy "+
          "plains and annoying the sheep. He has a devilish smile on his "+
          "innocent face.\n");
       set_short("red-headed boy");
       add_name("boy");
       }
 
    default_config_npc(20);
    set_skill(SS_AWARENESS, 15);
    set_skill(SS_UNARM_COMBAT, 10);
    set_skill(SS_DEFENCE, 10);
    set_skill(SS_PARRY,   10);
 
    set_random_move(60);
    set_act_time(60);
    add_act("emote kicks a stone across the ground.");
    add_act("emote giggles inanely.");
    add_act("emote snickers at you.");
    add_act("emote pokes you in the ribs and giggles.");
    add_act("emote sticks "+HIS_HER(TO)+" tongue out at you.");
    add_act("emote baaa's at you like a sheep and snickers.");
 
 
    set_default_answer("Ask my ma! I'm not 'sposed to talk to strangers.");
 
    set_alignment(100);
    set_exp_factor(100);
    set_size_descs("short", "of normal width");
}
 
public int hook_return_intro(string str) {
    command("say I'm not 'sposed to talk to strangers.");
    command("emote sticks "+HIS_HER(TO)+" tongue out at you.");
    command("emote snickers devilishly.");
    return 1;
}
 
