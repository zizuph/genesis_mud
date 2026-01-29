#pragma strict_types

#include "../guild.h"

inherit GUILDDIR+"lib/train_base";

mapping skills = SKILL_LEVELS;

void
set_up_skills()
{
    sk_add_train(SS_ELEMENT_WATER, "cast water spells",        0, 0, skills[SS_ELEMENT_WATER][10] );
    sk_add_train(SS_ELEMENT_EARTH, "cast earth spells",        0, 0, skills[SS_ELEMENT_EARTH][10] );
    sk_add_train(SS_ELEMENT_AIR, "cast air spells",            0, 0, skills[SS_ELEMENT_AIR][10] );
    sk_add_train(SS_FORM_TRANSMUTATION, "transmutate objects", 0, 0, skills[SS_FORM_TRANSMUTATION][10] );
    sk_add_train(SS_FORM_ENCHANTMENT, "enchant objects",       0, 0, skills[SS_FORM_ENCHANTMENT][10] );
    sk_add_train(SS_FORM_CONJURATION, "conjure objects",       0, 0, skills[SS_FORM_CONJURATION][10] );
    sk_add_train(SS_ALCHEMY, "brew potions",                   0, 0, skills[SS_ALCHEMY][10] );
}
