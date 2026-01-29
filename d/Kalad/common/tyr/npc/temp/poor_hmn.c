/* poor_hmn: ACME-Poor-Athasian-Citizen (TM). */
inherit "/std/monster";
#include "defs.h"

#define RNDRACE ({"human", "human", "human", "half-elf", "dwarf"})
#define RNDADJ ({"sad", "tired", "ugly", "pathetic", "dirty", "hungry"})

void
create_monster()
{
    set_adj("poor");
    add_adj(RNDADJ[random(6)]);
    set_name("citizen");
    set_race_name(RNDRACE[random(5)]);
    set_long  ("This is one of the many unfortunate souls who inhabit "+
               "Athas, who like most combines brutal stoicism and "+
               "depressive apathy.\n");
    add_prop (LIVE_I_NEVERKNOWN, 1);

    set_act_time(8);
    add_act("sigh");
    add_act("ponder");
    add_act("emote looks somewhat afraid of you.");
    add_act("say Why don't you just leave me alone?");
    set_gender(random(2));
    set_alignment(random(150)-50);

    default_config_npc(random(6)+10);

    set_skill(SS_WEP_KNIFE, 30);
    set_skill(SS_DEFENCE, 20);
    set_skill(SS_PARRY, 10);
}

void
arm_me()
{
    clone_object(TYR_WEP+"knife_sd.c")->move(TO);
    command("wield all");
}
