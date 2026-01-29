
 /*    An eel for the water area

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
#include <formulas.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "defs.h"

#define A_BITE  0
#define A_JAWS 1
#define A_TAIL 2

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2
#define H_EYES 3


object tp = this_player();
create_creature()
{
	set_name("shock");
	set_living_name("shock");
	set_race_name("eel");
    set_gender(2);
    set_short("small electric eel");
    set_pshort("small electric eels");
    set_adj(({"small", "electric"}));
    set_long("This small creature is about two feet in length and "+
        "about six inches in diameter. It looks very much like a "+
        "fat snake only it is blue-grey in color and has two "+
        "very prominent blue eyes. It does not appear to be "+
        "aggressive but you think you probably shouldn't mess "+
        "with it.\n");

	set_stats(({50, 45, 45, 15, 15, 30}));

	set_skill(SS_SWIM, 100);
	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_BLIND_COMBAT, 80);
	set_skill(SS_DEFENCE, 100);
	set_alignment(-100);

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(NPC_I_NO_LOOKS,1);

    add_leftover(SEA_LEFTOVERS+"eel_meat","eel meat", (random(2)+1), 0, 0, 1);
    add_leftover(SEA_LEFTOVERS+"eel_skin","eel skin", 1, 0, 0, 1);

	set_attack_unarmed(A_JAWS, 40, 50, W_IMPALE, 45, "jaws");
	set_attack_unarmed(A_BITE, 35, 45, W_SLASH, 45, "teeth");
	set_attack_unarmed(A_TAIL, 20, 25, W_BLUDGEON, 10, "tail");

    set_hitloc_unarmed(H_HEAD, ({5,5,5,5}), 40, "head");
    set_hitloc_unarmed(H_TAIL, ({5,5,5,10}), 15, "tail");
	set_hitloc_unarmed(H_BODY, ({10,15,15,20}), 35, "body");
    set_hitloc_unarmed(H_EYES, ({10,5,10,5}), 10, "eye");
	add_act("emote swims around in circles.");
	add_act("emote eyes some insects hungrily.");

    set_random_move(15);
    set_restrain_path(({(SECTOR_PATH(0, 0, 1)),(SECTOR_PATH(0, 0, 2)),
        (SECTOR_PATH(0, 0, 3)),(SECTOR_PATH(0, 0, 4)),
        (SECTOR_PATH(0, 10, 1)),(SECTOR_PATH(0, 10, 2)),
        (SECTOR_PATH(0, 10, 3)),(SECTOR_PATH(0, 10, 4)),
        (SECTOR_PATH(10, 10, 1)),(SECTOR_PATH(10, 10, 2)),
        (SECTOR_PATH(10, 10, 3)),(SECTOR_PATH(10, 10, 4)),
        (SECTOR_PATH(10, 0, 1)),(SECTOR_PATH(10, 0, 2)),
        (SECTOR_PATH(10, 0, 3)),(SECTOR_PATH(10, 0, 4))}));
}
/*
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:     The string to send
 */
static void
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
}

int
special_attack(object enemy)
{
    object me;
	mixed *hitresult;
    string how1, how2, my_name, his_name;


    me = this_object();
    if(random(4))
	return 0;                         /* Continue with the attack. */

    hitresult = enemy->hit_me(F_PENMOD(random(35)+20, 100), W_IMPALE, 
                              me, -1);
    my_name = QCTNAME(me);
    his_name =  QTNAME(enemy);
    switch(hitresult[0])
    {
        case -1:
        {
            how1 = my_name+" nips at you but misses.\n";
            how2 = my_name+" nips at "+his_name+" but misses.\n";
            break;
        }
        case 0..5:
        {
            how1 = my_name+" nibbles hungrily at your flesh, "+
                "grazing you slightly.\n";
            how2 = my_name+" nibbles hungrily at "+his_name+"'s "+
                "flesh.\n";
            break;
        }
        case 6..7:
        {
             how1 = my_name+" brushes itself against your leg, "+
                 "electricuting you!\n";
             how2 = my_name+" brushes itself against "+his_name+
                 "'s leg!\n";
             enemy->add_attack_delay(5);
             break;
        }
        case 8..10:
        {
             how1 = my_name+" wraps itself around your leg, hindering you "+
                 "as well as electricuting you!\n";
             how2 = my_name+" wraps itself around "+his_name+
                 "'s leg!\n";
             enemy->add_attack_delay(5);
             break;
        }
        case 11..15:
        {
            how1 = my_name+" wraps itself around your arm, hindering you "+
                "as well as electricuting you!\n";
            how2 = my_name+" wraps itself around "+his_name+
                "'s arm!\n";
            enemy->add_attack_delay(5);
            break;
        }
        default:
        {
            how1 = my_name+" wraps itself around your neck, choking you "+
                "as well as electricuting you!\n";
            how2 = my_name+" wraps itself around "+his_name+
                "'s neck!\n";
            enemy->add_attack_delay(10);
        }
    }

	if(enemy->query_hp() <= 0)
		enemy->do_die(me);
    
    enemy->catch_msg(how1, tp);
    tell_watcher(how2, enemy);

    
	return 1;
}
