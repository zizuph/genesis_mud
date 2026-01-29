/* Barbarian woman for the Que Kiri village
 * Aridor 07/97
 */

#include "../local.h"
#include <ss_types.h>

inherit BARBARIAN

void
create_barbarian()
{
    add_name(({"woman"}));
    add_pname(({"women"}));
    set_gender(1);
    default_config_npc(random(30) + 10);
    set_skill(SS_WEP_KNIFE, 24);
    set_skill(SS_DEFENSE, 21);
    set_skill(SS_AWARENESS, 33);

    if (random(20))
      set_give_quest(0);
}

void
arm_me()
{
    clone_object(KNIFE)->move(TO,1);
    clone_object(CLOAK)->move(TO,1);
    clone_object(BLOUSE)->move(TO,1);
    clone_object(SKIRT)->move(TO,1);
    ::arm_me();
}
