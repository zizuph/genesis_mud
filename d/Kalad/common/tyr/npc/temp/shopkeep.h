/* shopkeep.h: Generic shop keeper */
#include "defs.h"

void create_monster()
{
    set_name(MOBNAME);
    set_adj(ADJ1);
    add_adj(ADJ2);
    set_title(TITLE);
    set_race_name(RACE);
    set_long(LONG);
    set_gender(SEX);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    default_config_npc(random(21)+49);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_WEP_KNIFE, 100);

    set_alignment(50);
}

void arm_me()
{
    clone_object(TYR_WEP+"knife_nk.c")->move(TO);
    command("wield all");
}
