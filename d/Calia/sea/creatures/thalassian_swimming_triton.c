
 /* 
  * A swimming triton for Thalassia
    coder(s):    Jaacar  July 2003

  * Cotillion - 2017-06-25
  * - fixed runtime in special_attack
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
#include <cmdparse.h>
#include "/d/Genesis/gems/gem.h"
#include "defs.h"
#include GLYKDEF
#include MAP_HEADER

#define A_TAIL  0

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2

create_creature()
{
    object gem;

    set_name("triton");
    set_short("massive triton");
    set_adj("massive");
    set_race_name("triton");
    set_long("He is a strikingly beautiful creature with long "+
        "black hair.  He is human in appearance above the waist, "+
        "but has a large fish-like tail instead of legs.  He is "+
        "covered in dark green scales, and has long, sharp claws "+
        "on his webbed fingers.  His smile reveals what look like "+
        "very sharp fish teeth.\n");


    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    set_alignment(300);
    set_gender(0);
    set_random_move(10);
    set_restrain_path(({(THAL),(THALL),(THALM),(THALC)}));
    set_stats(({(random(80)+40),(random(60)+40),(random(60)+40),
        70,70,(random(40)+20)}));
    set_act_time(15);
    add_act("emote bubbles: Go, devote yourself to Lady Aeria.");
    add_act("emote bubbles: Go, worship the Elementals.");

	set_skill(SS_SWIM, 100);
	set_skill(SS_UNARM_COMBAT, 100);
	set_skill(SS_BLIND_COMBAT, 80);
	set_skill(SS_DEFENCE, 100);

	set_attack_unarmed(A_TAIL,15,25,W_IMPALE,100,"tail");
    set_hitloc_unarmed(H_HEAD, ({5,5,5,5}), 40, "head");
    set_hitloc_unarmed(H_TAIL, ({5,5,5,10}), 25, "tail");
	set_hitloc_unarmed(H_BODY, ({10,15,15,20}), 35, "body");

    if (random(10) > 5)
    {
        gem=RANDOM_GEM_BY_RARITY(GEM_COMMON);
        gem->move(TO);
    }

	
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

    me = TO;
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
            how1 = my_name+" attempts to hit you with his fins "+
                "but misses.\n";
            how2 = my_name+" attempts to hit "+his_name+" with "+
                "his fins but misses.\n";
            break;
        }
        case 0..4:
        {
            how1 = my_name + " attempts to hit your legs with his fins, "+
                "but only manages to graze them!\n";
            how2 = my_name + " attempts to hit " + his_name + "'s legs, "+
                "who is only grazed by the blow!\n";
            break;
        }
        case 5..9:
        {
            how1 = my_name + " hits your legs with his tail, "+
                "but doesn't manage to knock you off balance!\n";
            how2 = my_name + " hits " + his_name + "'s legs, "+
                "who seems uneffected by the blow!\n";
            break;
        }
        case 10..14:
        {
            how1 = my_name + " hits your legs with his tail, "+
                "knocking you off balance for just a moment!\n";
            how2 = my_name + " hits " + his_name + "'s legs, "+
                "who is knocked off balance!\n";
            enemy->add_attack_delay(5);
            break;
        }
        case 15..19:
        {
            how1 = my_name + " hits you with his tail, cutting "+
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
                "dizzying effect in your head.  He quickly bashes "+
                "you with his tail while you are effected!\n";
            how2 = my_name + " screams out some high pitched sounds "+
                "directed at "+ his_name + " then quickly bashes "+
                enemy->query_objective() + " while " +
                enemy->query_pronoun() + " is effected!\n";
            enemy->add_attack_delay(15);
        }
    }

    if (enemy->query_hp() <= 0)
        enemy->do_die(me);
    enemy->catch_msg(how1, TP);
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
