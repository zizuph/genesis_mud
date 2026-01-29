
 /*    A demon toad for the water area

    coder(s):    Jaacar

 */

inherit "/d/Calia/std/sea_creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <formulas.h>
#include "defs.h"

object tp = this_player();

#define A_BITE  0
#define A_FRONT_FEET 1

#define H_HEAD 0
#define H_BODY 1
#define H_EYES 2
#define H_LEGS 3

create_creature()
{
    set_name("toad");
    add_name("demon toad");
    add_name("demon frog");
    set_short("large demon toad");
    set_adj("large");
    add_adj("demon");
    set_race_name("toad");
    set_long("Two enormous green-lidded eyes set in a gnarled "+
        "reptilian head. When its nostrils flare and its long "+
        "scarlet mouth opens, it reveals a pink, flickering "+
        "tongue. The extraordinarily dense weight of scaly flesh "+
        "is supported on massive webbed feet and limbs as thick "+
        "as elm trunks. When it breathes, its whole body shakes "+
        "and shudders.\n");

    add_leftover(SEA_LEFTOVERS+"toad_legs", "legs", 1, 0, 0, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_alignment(-300);
    set_gender(2);
    set_random_move(15);
    set_restrain_path(({(SECTOR_PATH(0, 0, 1)),(SECTOR_PATH(0, 0, 2)),
        (SECTOR_PATH(0, 0, 3)),(SECTOR_PATH(0, 0, 4)),
        (SECTOR_PATH(0, 10, 1)),(SECTOR_PATH(0, 10, 2)),
        (SECTOR_PATH(0, 10, 3)),(SECTOR_PATH(0, 10, 4)),
        (SECTOR_PATH(10, 10, 1)),(SECTOR_PATH(10, 10, 2)),
        (SECTOR_PATH(10, 10, 3)),(SECTOR_PATH(10, 10, 4)),
        (SECTOR_PATH(10, 0, 1)),(SECTOR_PATH(10, 0, 2)),
        (SECTOR_PATH(10, 0, 3)),(SECTOR_PATH(10, 0, 4))}));
        add_prop(OBJ_I_VOLUME, 50);
	add_prop(OBJ_I_WEIGHT, 50);

	set_stats(({120,90,85,80,80,90}));

	set_skill(SS_SWIM, 100);
	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_BLIND_COMBAT, 80);
	set_skill(SS_DEFENCE, 100);

/*	set_attack_unarmed(A_BITE,15,25,W_SLASH,80,"teeth");
	set_attack_unarmed(A_FRONT_FEET,15,25,W_IMPALE,80,"front feet");
	set_hitloc_unarmed(A_HEAD, ({5,5,5,5}), 40, "head");
	set_hitloc_unarmed(H_BODY, ({10,15,15,20}), 35, "body");
	set_hitloc_unarmed(H_BODY, ({10,5,10,5}), 10, "eyes");*/

	set_attack_unarmed(A_BITE,15,25,W_SLASH,80,"teeth");
	set_attack_unarmed(A_FRONT_FEET,15,25,W_IMPALE,20,"front feet");
	set_hitloc_unarmed(H_HEAD, ({5,5,5,5}), 40, "head");
	set_hitloc_unarmed(H_BODY, ({10,15,15,20}), 35, "body");
	set_hitloc_unarmed(H_EYES, ({10,5,10,5}), 10, "eyes");
	set_hitloc_unarmed(H_LEGS, ({10,15,15,20}), 15, "legs");
}
/*
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:     The string to send
 */
/*static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}*/

int
special_attack(object enemy)
{
    object me;
    mixed *hitresult;
    string how1, how2, my_name, his_name;

    me = this_object();
    if (random(4))
        return 0;      /* Continue with the attack. */

    hitresult = enemy->hit_me(F_PENMOD(random(35)+20, 100), W_IMPALE,
        me, -1);

    my_name = QCTNAME(me);
    his_name = QTNAME(enemy);

    switch(hitresult[0])
    {
        case -1:
        {
            how1 = my_name+" tries to hit you with its front feet but misses.\n";
            how2 = my_name+" tries to hit "+his_name+" with its front feet "+
                "but misses.\n";
            break;
        }
        case 0..4:
        {
            how1 = my_name + " attempts to bite your legs, "+
                "but only manages to graze them!\n";
            how2 = my_name + " attempts to bite " + his_name + "'s legs, "+
                "who is only grazed by the blow!\n";
            break;
        }
        case 5..10:
        {
            how1 = my_name + " bites your legs, "+
                "but doesn't manage to knock you off balance!\n";
            how2 = my_name + " bites " + his_name + "'s legs, "+
                "who seems uneffected by the blow!\n";
            break;
        }
        case 11..14:
        {
            how1 = my_name + " hits your legs with its front feet, "+
                "knocking you off for just a moment!\n";
            how2 = my_name + " hits " + his_name + "'s legs, "+
                "who is knocked off balance!\n";
            enemy->add_attack_delay(5);
            break;
        }
        default:
        {
            how1 = my_name + " hits your legs with its front feet, "+
                "knocking you off balance temporarily!\n";
            how2 = my_name + " hits " + his_name + "'s legs, "+
                "who is knocked off balance!\n";
            enemy->add_attack_delay(10);
        }
    }
    if (enemy->query_hp() <= 0)
        enemy->do_die(me);
    enemy->catch_msg(how1, tp);
    tell_watcher(how2, enemy);
    return 1;
}
