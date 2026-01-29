inherit "/lib/skill_raise";

#include "/d/Emerald/sys/skills.h"
#include <ss_types.h>

#define SK_ADD(sknum, level) sk_add_train(sknum, 0, 0, 0, level)

void
create()
{
    create_skill_raise();

    SK_ADD(SS_SPELLCRAFT, 50);
    SK_ADD(SS_HERBALISM,  50);
    SK_ADD(SS_TRADING, 40);
    SK_ADD(SS_AWARENESS, 60);
    SK_ADD(SS_LANGUAGE, 60);
    SK_ADD(SS_ELEMENT_LIFE, 50);
    SK_ADD(SS_FORM_CONJURATION, 50);
    SK_ADD(SS_FORM_ENCHANTMENT, 30);
    SK_ADD(SS_FORM_DIVINATION, 40);
}
