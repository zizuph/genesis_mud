#pragma strict_types

#include "../guild.h"

inherit GUILDDIR+"lib/train_base";

mapping skills = SKILL_LEVELS;

void
set_up_skills()
{
    sk_add_train(SS_HERBALISM, "find and identify plants",  0, 0, skills[SS_HERBALISM][10] );
    sk_add_train(SS_APPR_OBJ, "appraise objects",           0, 0, skills[SS_APPR_OBJ][10] );
    sk_add_train(SS_APPR_VAL, "appraise values",            0, 0, skills[SS_APPR_VAL][10] );
}
