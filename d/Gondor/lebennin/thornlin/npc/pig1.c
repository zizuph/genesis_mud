/*
Last edited :
-----------------05-02-95 17.38-------------------
 A pig for Thornlin
 coded by: Boromir
--------------------------------------------------
*/

inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */

inherit "/std/act/domove"; /* Include this if you want the creature to move */
inherit "/std/act/action"; /* Include this if you want your creature to act */

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../locals.h"

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_PHEAD 1
#define A_SNOUT 2

#define H_HEAD 0
#define H_BODY 1

string alignlook();

create_creature()
{
    int rnd;
    setuid(getuid(TO));

    set_name("pig");
    set_race_name("pig");
    set_gender(random(2));

    set_adj(alignlook());
    add_adj("pink-skinned");

    set_long("This is a pig, "+TO->query_pronoun()+
      " has clearly been wallowing in the mud, because "+
      TO->query_pronoun()+" is very dirty.\n");
    set_whimpy(10+random(99));

    set_act_time(10);
    add_act("emote rolls in the dirt.");
    add_act("emote tries to dig in the ground with "+
      TO->query_possessive()+" snout.");

    set_cact_time(2);
    add_cact("scream");
    add_cact("panic");

    rnd = random(2);
    //          STR DEX CON INT WIS DIS
    set_stats(({  9,  2,  7, 10,  7,  7}));

    set_skill(SS_DEFENCE, 5);

    set_attack_unarmed(A_BITE,  2+rnd, 5+rnd, W_IMPALE, 40, "teeth");
    set_attack_unarmed(A_PHEAD,  3+rnd, 5+rnd, W_BLUDGEON,  30, "head");
    set_attack_unarmed(A_SNOUT, 3+rnd, 5+rnd, W_BLUDGEON,  30, "snout");

    set_hitloc_unarmed(H_HEAD, ({ 4, 4, 4, }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 4, 4, 8, }), 80, "body");
}


/*
 * Here we redefine the special_attack function which is called from
 * within the combat system. If we return 1 then there will be no
 * additional ordinary attack.
 *
 */
int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;

    me = this_object();
    if(random(10))
	return 0;                         /* Continue with the attack. */

    hitresult = enemy->hit_me(20+random(50), W_IMPALE, me, -1);
    how = " without effect";
    if (hitresult[0] > 0)                 /* hitresult[0] yields the % hurt. */
	how = "";
    if (hitresult[0] > 10)
	how = " hard";
    if (hitresult[0] > 20)
	how = " very hard";

    me->catch_msg("You run right into your enemy.\n" +
      capitalize(enemy->query_pronoun()) + " is hit" +
      how + ".\n");
    enemy->catch_msg(QCTNAME(me) + " runs snout first into you.\n"+
      "You are hit" + how + ".\n");
    tell_watcher(QCTNAME(me)+" runs snout first into "+QTNAME(enemy)+"!\n"+
      capitalize(enemy->query_pronoun()) + " is hit" +
      how + ".\n", enemy);
    if(enemy->query_hp() <= 0)
	enemy->do_die(me);

    return 1; /*  Important! Should not have two attacks in a round. */
}

string
alignlook()
{
    string *alignlooks;
    alignlooks = ({"ugly", "grim", "fat", "small", "porky", "dirty", "tough"});
    return alignlooks[random(sizeof(alignlooks))];
}

