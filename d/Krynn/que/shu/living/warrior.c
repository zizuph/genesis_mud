/* Barbarian warrior for the Que Kiri village
 * Aridor 07/97
 */

#include "../local.h"
#include <ss_types.h>

inherit BARBARIAN

void
create_barbarian()
{
    add_name(({"warrior","man"}));
    add_pname(({"men","warriors"}));
    set_gender(0);
    set_extra_long("This man is a warrior, his task is to guard the village.\n");
    default_config_npc(random(60) + 70);
    set_skill(SS_WEP_KNIFE, 74);
    set_skill(SS_WEP_POLEARM, 89);
    set_skill(SS_DEFENSE, 81);
    set_skill(SS_PARRY, 87);
    set_skill(SS_AWARENESS, 53);

    if (random(10))
      set_give_quest(0);
}

void
arm_me()
{
    clone_object(KNIFE)->move(TO,1);
    clone_object(STAFF)->move(TO,1);
    clone_object(LEATHERARMOR)->move(TO,1);
    clone_object(PANTS)->move(TO,1);
    clone_object(CLOAK)->move(TO,1);
    command("wield staff");
    ::arm_me();
}
