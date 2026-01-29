inherit "/d/Emerald/lib/train";

#include <ss_types.h>

void set_up_skills()
{
    create_skill_raise();
  
    sk_add_train(SS_AWARENESS, "perceive", "awareness", 0, 100);
    sk_add_train(SS_DEFENSE, "dodge attacks", "defense", 0, 100);
}

>>()
{
    set_up_skills();
}

