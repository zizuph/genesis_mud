/* Barbarian shepherd for the Que Kiri village
 * Aridor 07/97
 */

#include "../local.h"
#include <ss_types.h>

inherit BARBARIAN

void
create_barbarian()
{
    add_name(({"villager","man","shepherd"}));
    add_pname(({"men","villagers","shepherds"}));
    set_gender(0);
    set_extra_long("This man seems to be a shepherd.\n");
    default_config_npc(random(40) + 20);
    set_skill(SS_WEP_KNIFE, 44);
    set_skill(SS_WEP_POLEARM, 43);
    set_skill(SS_DEFENSE, 41);
    set_skill(SS_PARRY, 37);
    set_skill(SS_AWARENESS, 43);

    if (random(20))
      set_give_quest(0);
}

void
arm_me()
{
    clone_object(STAFF)->move(TO,1);
    clone_object(CLOAK)->move(TO,1);
    clone_object(JACKET)->move(TO,1);
    clone_object(PANTS)->move(TO,1);
    ::arm_me();
}
