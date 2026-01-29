/* Farmer of the Plains of Solamnia
 * Aridor 08/99
 */

#include "../local.h"
#include <ss_types.h>

inherit SOLAMNIAN

void
create_solamnian()
{
    add_name(({"villager","man","farmer"}));
    add_pname(({"men","villagers","farmers"}));
    set_gender(0);
    default_config_npc(random(40) + 10);
    set_skill(SS_WEP_KNIFE, 34);
    set_skill(SS_DEFENSE, 31);
    set_skill(SS_PARRY, 17);
    set_skill(SS_AWARENESS, 43);

    set_give_quest(0);
}

void
arm_me()
{
    clone_object(KNIFE)->move(TO,1);
    clone_object(CLOAK)->move(TO,1);
    clone_object(JACKET)->move(TO,1);
    clone_object(PANTS)->move(TO,1);
    ::arm_me();
}

string
query_nonmet_name()
{
    return ::query_nonmet_name() + " farmer";
}
