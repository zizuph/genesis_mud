/*
 * Battle tactics for npcs.
 * This file can be inherited and the individual routines used 
 * simply by calling them.
 *
 * Developed by Finwe, January 2002
 *
 */

inherit "/std/monster";

#include "/d/Shire/sys/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>

// Prototypes
void check_my_weapon();
int find_valid_enemy(object foe);
int shire_break_weapon();


/* Function name: break_weapon
 * Description:   When active, the npc will attempt to break the 
 *                player's weapons
 * Files used:    shire_break_weapon(), check_my_weapon(), find_valid_enemy()
 */

void check_my_weapon() 
{
    if (!query_skill(SS_UNARM_COMBAT) && !sizeof(query_weapon(-1)))
    {
    set_skill(SS_UNARM_COMBAT, 94);
    map(query_combat_object()->query_attack_id(), cr_reset_attack);
    }
    else
    if (query_skill(SS_UNARM_COMBAT))
    {
    remove_skill(SS_UNARM_COMBAT);
    map(query_combat_object()->query_attack_id(), cr_reset_attack);
    map(query_weapon(-1), update_weapon);
    }
}

int find_valid_enemy(object foe)
{
    if (ENV(foe) != ENV(TO))   
    return 0;
    if (!sizeof(foe->query_weapon(-1)))
    return 0;

    // Passed all checks.    
    return 1;
}

int shire_break_weapon()
{
    object *foes, *weapons, *my_weapons, weapon;

            check_my_weapon();

            if (random(7))
            return 0;
            my_weapons = query_weapon(-1);
            weapons = ob->query_weapon(-1);

    // If I have no weapon wielded I can't do this attack.
            if (!sizeof(my_weapons))
            {
    // Posibily do an unarmed attack here?
                return 0;
            }

    // My enemy has no weapon so lets look for another :)
            if (!sizeof(weapons))
            {
                if (!sizeof(foes = filter(query_enemy(-1), find_valid_enemy)))
                    return 0;
                ob = foes[random(sizeof(foes))];
                weapons = ob->query_weapon(-1);
            }

    // Sanity check
            if (!sizeof(weapons))
                return 0;
    // What weapon are we attacking.
            weapon = weapons[random(sizeof(weapons))];

    // Do we hit with this attack?
            if (query_combat_object()->cb_tohit(-1,100,ob) >= 0)
            {
                if (!weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON))
                {
        // See if we are able to break non-magical weapons.
                    if (resolve_task(TASK_DIFFICULT, ({TS_DEX, SS_WEP_POLEARM}), ob,
                        ({SKILL_AVG, TS_DEX, TS_WIS, SKILL_END, SS_PARRY})) >= 0)
                    {
                        ob->catch_tell("The "+query_nonmet_name()+" strikes your "+
                        weapon->short()+" with "+HIS_HER(TO)+" "+
                            my_weapons[0]->short()+" with tremendous force damaging "+
                            "your "+weapon->short()+" beyond repair.\n");
                        tell_room(ENV(TO), QCTNAME(TO) + " strikes "+QTNAME(ob)+
                            "'s "+weapon->short()+" with "+HIS_HER(TO)+" "+
                        my_weapons[0]->short()+" with tremendous force damaging "+
                            QTNAME(ob)+"'s "+weapon->short()+" beyond repair.\n", 
                            ({TO,ob}));
                       weapon->remove_broken();
                        return 1;
                    }
                }
                ob->catch_tell("The "+query_nonmet_name()+" strikes your "+
                weapon->short()+" with "+HIS_HER(TO)+" "+
                    my_weapons[0]->short()+" leaving your "+weapon->short()+
                    " somewhat damaged from the blow.\n");
                tell_room(ENV(TO), QCTNAME(TO) + " strikes "+QTNAME(ob)+
                    "'s "+weapon->short()+" with "+HIS_HER(TO)+" "+
                my_weapons[0]->short()+" leaving "+QTNAME(ob)+"'s "+
                    weapon->short()+" somewhat damaged by the blow.\n",({TO,ob}));
    // The weapon condition gets worse by 1-2 levels.
                weapon->set_dull(weapon->query_dull() + random(2) + 1); 
                return 1;
            }
            else
            {
    // Damn we missed so nothing bad happens.. but lets let people
    // know we tried to do something.
                ob->catch_tell("The "+query_nonmet_name()+" attempts to strike "+
                    "your "+weapon->short()+" with "+HIS_HER(TO)+" "+
                my_weapons[0]->short()+", but you manage to avoid the blow.\n");
                tell_room(ENV(TO), QCTNAME(TO) + " attemptes to strike "+QTNAME(ob)+
                    "'s "+weapon->short()+" with "+HIS_HER(TO)+" "+
                    my_weapons[0]->short()+", but "+QTNAME(ob)+" manages to "+
                    "avoid the blow.\n",({TO,ob}));    
                return 1;
            }
}


