/* Barbarian shaman for the Que Kiri village
 * Aridor 07/97
 */

#include "../local.h"
#include <ss_types.h>

inherit BARBARIAN

void
create_barbarian()
{
    add_name(({"villager","man","shaman"}));
    add_pname(({"men","villagers","shamans"}));
    set_gender(0);
    set_long("This is a @@query_old_nonmet_name@@ of the Que Kiri tribe.\n");
    set_extra_long("This man seems to be the shaman of the Que Kiri tribe.\n");
    default_config_npc(random(40) + 20);
    set_skill(SS_WEP_KNIFE, 44);
    set_skill(SS_WEP_POLEARM, 43);
    set_skill(SS_DEFENSE, 41);
    set_skill(SS_PARRY, 37);
    set_skill(SS_AWARENESS, 43);
}

void
arm_me()
{
    clone_object(KNIFE)->move(TO,1);
    clone_object(STAFF)->move(TO,1);
    clone_object(CLOAK)->move(TO,1);
    clone_object(JACKET)->move(TO,1);
    clone_object(PANTS)->move(TO,1);
    command("wield staff");
    ::arm_me();
}

string
query_nonmet_name()
{
    return ::query_nonmet_name() + " shaman";
}

string
query_old_nonmet_name()
{
    return ::query_nonmet_name();
}
