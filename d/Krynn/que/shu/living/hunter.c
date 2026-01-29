/* Barbarian warrior for the Que Kiri village
 * Aridor 07/97
 */

#include "../local.h"
#include <ss_types.h>

inherit BARBARIAN

void
create_barbarian()
{
    add_name(({"hunter","man"}));
    add_pname(({"men","hunters"}));
    set_gender(0);
    set_extra_long("This man is a hunter, responsible for feeding his people.\n");
    default_config_npc(random(40) + 50);
    set_skill(SS_WEP_KNIFE, 84);
    set_skill(SS_WEP_POLEARM, 69);
    set_skill(SS_DEFENSE, 71);
    set_skill(SS_PARRY, 57);
    set_skill(SS_AWARENESS, 73);

    if (random(10))
      set_give_quest(0);
}

void
arm_me()
{
    clone_object(STAFF)->move(TO,1);
    clone_object(KNIFE)->move(TO,1);
    clone_object(LEATHERARMOR)->move(TO,1);
    clone_object(PANTS)->move(TO,1);
    clone_object(CLOAK)->move(TO,1);
    command("wield staff");
    ::arm_me();
}
