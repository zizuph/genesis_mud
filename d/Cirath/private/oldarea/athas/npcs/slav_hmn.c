/* slav_hmn: ACME-Slave (TM). */
inherit "/std/monster";
#include "defs.h"

#define RNDRACE ({"human", "human", "human", "half-elf", "dwarf", "dwarf", "half-giant", "mul", "elf", "halfling"})
#define RNDADJ ({"starving", "scarred", "withdrawn", "angry", "pathetic", "frightened", "weary", "old", "sullen", "dirty"})

void
create_monster()
{
    add_adj("enslaved");
    set_adj(RNDADJ[random(10)]);
    set_race_name(RNDRACE[random(10)]);
    set_name("slave");
    set_gender(random(2));
    set_long("Worn and dirty, this slave has lost the will to live, or "+
             "even move. Only the threat of the whip, or worse yet the "+
             "Arena, keeps such people from just stopping entirely and "+
             "letting death take them.\n");
    add_prop (LIVE_I_NEVERKNOWN, 1);

    set_act_time(14);
    add_act("sigh");
    add_act("emote looks at you with sunken eyes.");
    add_act("emote tries not to think of the future.");
    add_act("ponder painful hunger");
    add_act("emote wipes away some sweat, and swallows it!");
    add_act("emote cries softly, but quickly hides the emotion.");
    set_cact_time(3);
    add_cact("say Yes, end it now. Please.");
    add_cact("emote seems almost happy to be facing death.");
    add_cact("emote tries half-heartedly to defend.");

    set_alignment(random(100)-50);

    set_stats(({20, 10, 25, 5, 5, 15}));

    set_skill(SS_WEP_CLUB, 30);
    set_skill(SS_UNARM_COMBAT, 30);
    set_skill(SS_DEFENCE, 20);
    set_skill(SS_PARRY, 10);
}

void
arm_me()
{
    clone_object(ATH_WEAPON+"chipper.c")->move(TO);
    command("wield all");
}
