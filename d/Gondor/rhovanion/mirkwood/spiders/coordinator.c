#pragma no_clone

#include <ss_types.h>
#include <wa_types.h>
#include "../defs.h"

object *
create_spiders_for_target(object target, int level)
{
    int target_con = target->query_stat(SS_CON);

    float armour_modifier = 1.0;
    float weapon_modifier = 1.0;
    int special_attack = 60;
    int extra_spiders = 0;

    switch(level)
    {
        case 1:
            armour_modifier = 0.6;
            weapon_modifier = 0.6;
            special_attack = 20;
            break;
        case 2:
            armour_modifier = 0.80;
            weapon_modifier = 0.80;
            special_attack = 40;
            extra_spiders = 1;
            break;
        case 3:
            armour_modifier = 1.00;
            weapon_modifier = 1.00;
            special_attack = 60;
            extra_spiders = 2;
            break;
        case 4:
            armour_modifier = 1.0;
            weapon_modifier = 1.0;
            special_attack = 80;
            extra_spiders = 3;
            break;
        case 5:
            armour_modifier = 1.2;
            weapon_modifier = 1.2;
            special_attack = 100;
            extra_spiders = 4;
            break;
        case 6:
            armour_modifier = 1.2;
            weapon_modifier = 1.2;
            special_attack = 110;
            extra_spiders = 5;
            break;
    }

    setuid();
    seteuid(getuid());

    object *spiders = ({ });
    int spider_count = 2 + extra_spiders;

    float *size_modifiers = ({ 0.86, 0.75, 0.7, 0.75, 0.7, 0.75, 0.7, 0.75, 0.7 });
    int special_attack_chance = special_attack / spider_count;

    for(int i = 0; i < spider_count; i++) 
    {
        object spider = clone_object(MIRKWOOD_SPIDER_DIR + "spider");
        spider->setup_stats(ftoi(itof(target_con) * size_modifiers[i]));
        spider->set_armour_modifier(armour_modifier);
        spider->set_victim(target);
        spider->set_special_attack_chance(special_attack_chance);
        spiders += ({ spider });
    }

    return spiders;
}