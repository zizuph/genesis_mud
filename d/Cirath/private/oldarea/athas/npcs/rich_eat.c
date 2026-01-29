/* rich_eat: ACME-Rich-Athasian-Hungry-Citizen (TM). */
 
#pragma strict_types
 
inherit "/d/Cirath/std/monster";
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
    set_long("This noble enjoys flaunting wealth by buying expensive "+
             "food and fancy clothes. Largely though it is the same sort "+
             "of pretentious fop you find anywhere else.\n"+
             "A Member of The Rich Men's Club.\n");
    add_prop (LIVE_I_NEVERKNOWN, 1);

    set_act_time(12);
    add_act("emote tries to sound knowledgeable about art.");
    add_act("emote orders some expensive food.");
    add_act("emote pats his purse lovingly. It looks well filled.");
    add_act("say The Minthors don't eat as well as this.");
    add_act("say The food here is excellent.");
    set_cact_time(3);
    add_cact("shout GUARDS! GUARDS! HELP!");
    add_cact("emote clutches his purse in fear");
    add_cact("emote begs for mercy");

    set_alignment(random(150)-100);

    set_stats(({15, 25, 35, 10, 10, 20}));

    set_skill(SS_WEP_KNIFE, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 30);
}

void
arm_me()
{
    clone_object(ATH_WEAPON+"knife_nk.c")->move(TO);
    clone_object(ATH_ARMOUR+"body_lth.c")->move(TO);
    make_cash(random(20), "copper");
    command("wield all");
    command("wear all");
}
