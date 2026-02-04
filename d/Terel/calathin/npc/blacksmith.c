/*  
 *  Blacksmith
 *
 *
 */
#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>

void
create_monster()
{
    if (!IS_CLONE) return;

    set_name("Sodar Nordgren");
    add_name("sodar");
    add_name("nordgren");
    add_name("keeper");
    set_race_name("human");
    set_adj("nordgren");
    set_long("Mr Nordgren is a blacksmith.\n");

    default_config_npc(88);


    set_skill(SS_DEFENCE, 70);
    set_skill(SS_PARRY, 70);
    set_skill(SS_UNARM_COMBAT, 80);
    SET_MAX_HP;

    set_all_hitloc_unarmed(40);
    set_all_attack_unarmed(50, 40);

    set_chat_time(15);
    add_chat("I can fix your dull weapons.");
    add_chat("Don't throw dull weapons out, I'll make them good as new!");

    add_prop(LIVE_I_ALWAYSKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS, 80);
}
