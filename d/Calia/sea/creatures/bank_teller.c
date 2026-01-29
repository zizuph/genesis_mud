
 /*    A bank teller mermaid for Thalassia

    coder(s):    Jaacar

 */

inherit "/d/Calia/std/sea_creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <formulas.h>
#include <cmdparse.h>
#include "defs.h"
#include GLYKDEF
#include MAP_HEADER

object tp = this_player();

#define A_TAIL  0

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2

create_creature()
{
    set_name("eeeeeek");
    add_name("mermaid");
    set_short("beautiful swimming mermaid");
    set_adj("beautiful");
    add_adj("swimming");
    set_race_name("mermaid");
    set_long("She is one of the most beautiful creatures you have "+
        "ever laid eyes upon in your life.  She has long "+
        "flowing golden hair and deep sea-green eyes.  She "+
        "is human in appearance above the waist, but has a "+
        "large fish-like tail instead of legs.  Her bare breasts "+
        "are fully exposed as she swims through the water.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_alignment(300);
    set_gender(1);
    set_stats(({(random(80)+40),(random(60)+40),(random(60)+40),
        70,70,(random(40)+20)}));

    set_skill(SS_SWIM, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_DEFENCE, 100);

    set_attack_unarmed(A_TAIL,15,25,W_IMPALE,100,"tail");
    set_hitloc_unarmed(H_HEAD, ({5,5,5,5}), 40, "head");
    set_hitloc_unarmed(H_TAIL, ({5,5,5,10}), 25, "tail");
	set_hitloc_unarmed(H_BODY, ({10,15,15,20}), 35, "body");


	
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
            how1 = my_name+" attempts to hit you with her fins "+
                "but misses.\n";
            how2 = my_name+" attempts to hit "+his_name+" with "+
                "her fins but misses.\n";
            break;
        }
        case 0..4:
        {
            how1 = my_name + " attempts to hit your legs with her fins, "+
                "but only manages to graze them!\n";
            how2 = my_name + " attempts to hit " + his_name + "'s legs, "+
                "who is only grazed by the blow!\n";
            break;
        }
        case 5..9:
        {
            how1 = my_name + " hits your legs with her tail, "+
                "but doesn't manage to knock you off balance!\n";
            how2 = my_name + " hits " + his_name + "'s legs, "+
                "who seems uneffected by the blow!\n";
            break;
        }
        case 10..14:
        {
            how1 = my_name + " hits your legs with her tail, "+
                "knocking you off balance for just a moment!\n";
            how2 = my_name + " hits " + his_name + "'s legs, "+
                "who is knocked off balance!\n";
            enemy->add_attack_delay(5);
            break;
        }
        case 15..19:
        {
            how1 = my_name + " hits you with her tail, cutting "+
                "your legs badly and leaving you in much pain!\n";
            how2 = my_name + " hits " + his_name + "'s legs, "+
                "cutting them badly!\n";
            enemy->add_attack_delay(10);
            break;
        }
        default:
        {
            how1 = my_name + " screams some high pitched sounds "+
                "directed towards you which seem to cause a "+
                "dizzying effect in your head.  She quickly bashes "+
                "you with her tail while you are effected!\n";
            how2 = my_name + " screams out some high pitched sounds "+
                "directed at "+ his_name + " then quickly bashes "+
                his_name->query_objective() + " while " +
                his_name->query_pronoun() + " is effected!\n";
            enemy->add_attack_delay(15);
        }
    }

    if (enemy->query_hp() <= 0)
        enemy->do_die(me);
    enemy->catch_msg(how1, tp);
    tell_watcher(how2, enemy);
    return 1;
}

void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    MAP_ATTACK(FIND_STR_IN_OBJECT("mermaids", environment()), attacker);
    MAP_ATTACK(FIND_STR_IN_OBJECT("tritons", environment()), attacker);
}
