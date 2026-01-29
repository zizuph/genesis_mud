/* Barbarian chieftain for the Que Shu village
 * Aridor 07/97
 */

#include "../local.h"
#include <ss_types.h>

inherit BARBARIAN

void
create_barbarian()
{
    add_name(({"villager","man","chieftain"}));
    add_pname(({"men","villagers","chieftains"}));
    set_gender(0);
    set_long("This is a @@query_old_nonmet_name@@ of the Que Shu tribe.\n");
    set_extra_long("This man seems to be the chieftain of the Que Shu tribe.\n");
    default_config_npc(random(40) + 80);
    set_skill(SS_WEP_KNIFE, 74);
    set_skill(SS_WEP_POLEARM, 99);
    set_skill(SS_DEFENSE, 91);
    set_skill(SS_PARRY, 87);
    set_skill(SS_AWARENESS, 63);
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

string
query_nonmet_name()
{
    return ::query_nonmet_name() + " chieftain";
}

string
query_old_nonmet_name()
{
    return ::query_nonmet_name();
}
