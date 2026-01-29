inherit "/lib/skill_raise";

#include "/d/Emerald/sys/skills.h"
#include <ss_types.h>

#define SK_ADD(sknum, level) sk_add_train(sknum, 0, 0, 0, level)

void
create()
{
    create_skill_raise();

    SK_ADD(SS_DEFENSE, 40);
    SK_ADD(SS_PARRY, 40);
    SK_ADD(SS_TRADING, 40);
    SK_ADD(SS_AWARENESS, 60);
    SK_ADD(SS_WEP_SWORD, 40);
    SK_ADD(SS_LANGUAGE, 60);
    SK_ADD(SS_APPR_MON, 50);
    SK_ADD(SS_ELEMENT_LIFE, 30);

#ifdef SS_PROT_CLARITY
    SK_ADD(SS_PROT_CLARITY, 50);
#endif

#ifdef SS_PROT_2H_SWORD
    SK_ADD(SS_PROT_2H_SWORD, 50);
#endif
}
