#pragma strict_types

#include "../guild.h"

inherit GUILDDIR+"lib/train_base";

mapping skills = SKILL_LEVELS;

void
set_up_skills()
{
    sk_add_train(SS_SPELLCRAFT,         "cast spells",          0, 0, skills[SS_SPELLCRAFT][10] );
    sk_add_train(SS_ELEMENT_LIFE,       "cast life spells",     0, 0, skills[SS_ELEMENT_LIFE][10] );
    sk_add_train(SS_FORM_DIVINATION,    "divine information",   0, 0, skills[SS_FORM_DIVINATION][10] );
    sk_add_train(SS_AWARENESS,          "be alert",             0, 0, skills[SS_AWARENESS][10] );
    sk_add_train(SS_LOC_SENSE,          "be aware of your surroundings", 0, 0, skills[SS_LOC_SENSE][10] );
    sk_add_train(SS_LANGUAGE,           "understand languages", 0, 0, skills[SS_LANGUAGE][10] );
    sk_add_train(SS_ANI_HANDL,          "tend animals",         0, 0, skills[SS_ANI_HANDL][10] );
}
