/* Barbarian child for the Que Kiri village
 * Aridor 07/97
 */

#include "../local.h"
#include <ss_types.h>

inherit BARBARIAN

void
create_barbarian()
{
    string t = (query_gender() ? "girl" : "boy");

    add_name(({"child"}));
    add_pname(({"children"}));
    add_name(t);
    set_short(t);

    default_config_npc(random(10) + 10);
    set_skill(SS_WEP_KNIFE, 14);
    set_skill(SS_DEFENSE, 11);
    set_skill(SS_AWARENESS, 3);
    
    add_prop(CONT_I_HEIGHT,76+random(119));
    add_prop(CONT_I_WEIGHT,40000+random(20000));
    add_prop(CONT_I_VOLUME,40000+random(20000));

    set_give_quest(0);
}

void
arm_me()
{
}
