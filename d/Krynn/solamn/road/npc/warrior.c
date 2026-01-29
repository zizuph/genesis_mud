/* Solamnian militia man of the Plains of Solamnia
 * Aridor 08/99
 */

#include "../local.h"
#include <ss_types.h>

inherit SOLAMNIAN

void
create_solamnian()
{
    add_name(({"militia man","warrior","man"}));
    add_pname(({"men","warriors","militia men"}));
    set_gender(0);
    set_extra_long("This man is a warrior and part of local militia, his task is to guard the area.\n");
    default_config_npc(random(60) + 70);
    set_skill(SS_WEP_KNIFE, 74);
    /*set_skill(SS_WEP_POLEARM, 89);*/
    set_skill(SS_WEP_SWORD, 89);
    set_skill(SS_DEFENSE, 81);
    set_skill(SS_PARRY, 87);
    set_skill(SS_AWARENESS, 53);

    set_give_quest(0);
}

void
arm_me()
{
    clone_object(SWORD)->move(TO,1);
    clone_object(KNIFE)->move(TO,1);
    /*clone_object(STAFF)->move(TO,1);*/
    clone_object(LEATHERARMOR)->move(TO,1);
    clone_object(PANTS)->move(TO,1);
    clone_object(CLOAK)->move(TO,1);
    command("wield sword");
    /*command("wield staff");*/
    ::arm_me();
}

string
query_nonmet_name()
{
    return ::query_nonmet_name() + " militia man";
}
