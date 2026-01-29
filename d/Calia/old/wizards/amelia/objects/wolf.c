
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

create_creature()
{
	set_name("wolf");
	set_race_name("wolf");
	set_short("great white wolf");
	set_pshort("great white wolves");
	set_adj(({"great", "white", "wild"}));
	set_long("This is a great white wolf, whose fur is thick "+
		"and shiny and whose yellow eyes watch you "+
		"intelligently.\n");

    /* str, con, dex, int, wis, dis
    */
    set_stats(({ 90, 30, 80, 20, 5, 75}));

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 30);
    set_skill(SS_SWIM, 80);

    set_attack_unarmed(A_BITE,  20, 30, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 40, 20, W_SLASH,  30, "left paw");
    set_attack_unarmed(A_RCLAW, 40, 20, W_SLASH,  30, "right paw");
   
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");

	set_act_time(15);
	add_act("emote sits on his haunches and watches you intently.");
	add_act("emote sniffs the air and looks around cautiously.");
	add_act("emote leans his head back, opens his jaws wide and howls!");
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
    mixed* hitresult;
    string how;

    me = this_object();
    if(random(10))
	return 0;                         /* Continue with the attack. */

    hitresult = enemy->hit_me(20+random(30), W_IMPALE, me, -1);
    how = " without effect";
	if(hitresult[0] > 0)
	how = "";
    if (hitresult[0] > 10)
	how = " hard";
    if (hitresult[0] > 20)
	how = " very hard";
    
	enemy->catch_msg(QCTNAME(me)+" bares his fangs and leaps "+
		"at your throat!  You are hit "+ how + ".\n");
    tell_watcher(QCTNAME(me)+" leaps into "+QTNAME(enemy)+"!\n"+
		 capitalize(enemy->query_pronoun()) + " is hit" + 
		 how + ".\n", enemy);
    if(enemy->query_hp() <= 0)
	enemy->do_die(me);
    
	return 1;
}
