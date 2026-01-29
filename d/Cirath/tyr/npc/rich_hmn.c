/* rich_hmn: ACME-Rich-Athasian-Citizen (TM). */
 
#pragma strict_types
 
inherit "/d/Cirath/std/monster.c";
#include "defs.h"
 
#define RNDRACE ({"human", "human", "human", "half-elf", "dwarf"})
#define RNDADJ ({"stylish", "sarcastic", "grinning", "dull", "clean"})
 
void
create_monster()
{
    ::create_monster();
    set_adj("rich");
    add_adj(RNDADJ[random(5)]);
    set_race_name(RNDRACE[random(5)]);
    set_name("noble");
    set_gender(random(2));
    set_long("Well fed and happy, this noble citizen enjoys flaunting "+
             "extreme wealth with fancy clothes, excellent grooming, and "+
             "even regular bathing in clean water. You receive a stare "+
             "mixing contempt and well....just contempt really.\n"+
             "A Member of The Rich Men's Club.\n");
    add_prop (LIVE_I_NEVERKNOWN, 1);
 
    set_act_time(7);
    add_act("emote spits on the ground, wasting precious moisture.");
    add_act("emote smiles with unyielding avarice.");
    add_act("emote pats a purse lovingly. It looks well filled.");
    add_act("say The Minthors? Nothing compared to me.");
    add_act("say Out of my way before I call my guards.");
    set_cact_time(3);
    add_cact("shout GUARDS! GUARDS! HELP!");
    add_cact("emote clutches a purse in fear");
    add_cact("emote begs for mercy");
 
    set_alignment(random(150)-100);
 
    set_stats(({10, 20, 30, 10, 5, 5}));
 
    set_skill(SS_WEP_KNIFE,40);
    set_skill(SS_DEFENCE,  30);
    set_skill(SS_PARRY, 20);
}
 
void
arm_me()
{
    clone_object(TYR_WEP+"knife_nk.c")->move(TO);
    clone_object(TYR_ARM+"body_fin.c")->move(TO);
    make_cash((random(5)+5), "copper");
    make_cash(1, "silver");
    command("wield all");
    command("wear all");
}
