#pragma strict_types

#include "../guild.h"
inherit (GUILDDIR+"lib/train_base");

mapping skills = SKILL_LEVELS;

void
set_up_skills()
{
    sk_add_train(SS_WEP_CLUB, "fight with a club",      0, 0, skills[SS_WEP_CLUB][10] );
    sk_add_train(SS_WEP_KNIFE, "prune plants",          0, 0, skills[SS_WEP_KNIFE][10] );
    sk_add_train(SS_DEFENCE,  "defend against attacks", 0, 0, skills[SS_DEFENCE][10] );
    sk_add_train(SS_PARRY, "parry blows",               0, 0, skills[SS_PARRY][10] );
    sk_add_train(SS_APPR_MON, "estimate your opponents",0, 0, skills[SS_APPR_MON][10] );
}
