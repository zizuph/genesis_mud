
/* Wolf for the wolf quest in the west moors of Calia.
   
   Coded by Maniac and Digit, May 95

   History: 
           24/8/96      updated                              Maniac
           25/5/95        Bug in enver_inv corrected         Maniac
            4/3/99      updated                              Maniac
		   26/5/15	    fixed a syntax issue                 Cherek
*/

#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <language.h>
#include <stdproperties.h>
#include "monster.h"
#include WOLF_QUEST

#define AN_ALL_INV(o) all_inventory(o) + all_inventory(environment(o))
#define FEED_NF "Feed what to what?\n"
#define PULL_NF "Pull what from what? Pull thorn from paw?\n"

#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1



void
create_creature()
{
    set_name("wolf");
    set_race_name("wolf");
    set_adj(({"large", "grey"}));

    set_long("This large grey animal is one of the wild wolves "+
       "of Calia, that hunt down prey on the moors, hills "+
       "and mountains. This one doesn't seem to have eaten " +
       "for quite some time though, as its ribs show through " +
       "its thick grey pelt. " +
       "It is not hard to see the reason: it is limping, walking " +
       "around on only three of its legs because of a large thorn " +
       "that is stuck in its right forepaw. The wolf appears to have " +
       "become separated from its pack because of its hampered mobility. " +
       "It looks wild-eyed and suspicious.\n");

    add_item(({"paw", "right paw"}),
              "The wolf's paw has a thorn stuck in it.\n"); 

    add_item(({"thorn", "large thorn"}),
              "Its deeply rooted in the wolf's paw and hampers its " +
              "mobility. You could pull it out, maybe?\n");
    
    /* str, con, dex, int, wis, dis
    */
    set_stats(({ 90, 30, 80, 20, 20, 75}));

    set_hp(3000);

    set_skill(SS_DEFENCE, 30);

    set_attack_unarmed(A_BITE,  20, 30, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 40, 20, W_SLASH,  30, "left paw");
    set_attack_unarmed(A_RCLAW, 40, 20, W_SLASH,  30, "right paw");
   
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");

    set_restrain_path(ROAD+"m"); /* restrict it to the moor */
    set_random_move(15);

    set_act_time(5);
    add_act("emote sits on his haunches and watches you intently.");
    add_act("emote sniffs the air and looks around cautiously.");
    add_act("emote leans his head back, opens his jaws wide and howls!");
    add_act("emote licks its right forepaw, obviously in pain.");

    add_prop(NPC_I_NO_LOOKS, 1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_m_in("limps in");
    set_mm_in("limps in.");
    set_m_out("limps away");
    set_mm_out("limps away");

    add_prop(CONT_I_WEIGHT, 40000); 
    add_prop(CONT_I_VOLUME, 40000); 
    add_prop(CONT_I_MAX_WEIGHT, 140000); 
    add_prop(CONT_I_MAX_VOLUME, 140000); 
}


int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;

    me = this_object();
    if(random(5))
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
		"at your throat! You are bitten"+ how + ".\n");
    tell_watcher(QCTNAME(me)+" leaps into "+QTNAME(enemy)+"!\n"+
		 capitalize(enemy->query_pronoun()) + " is bitten" + 
		 how + ".\n", enemy);
    if(enemy->query_hp() <= 0)
    enemy->do_die(me);
    
    return 1;
}


int
ok_to_eat_check(object ob)
{
    if (ob->id("corpse"))
        return 1;
    else  
        return 0;
}


void
wolf_eat_object(object ob, object from)
{
    tell_room(environment(this_object()), QCTNAME(this_object()) + 
              " hungrily devours the corpse.\n");
    ob->remove_object();
    if (interactive(from)) {
        from->add_prop(OBJ_I_FED_WOLF, 1);
        from->catch_msg(QCTNAME(this_object()) + " seems to regard " +
             "you somewhat less suspiciously now.\n");
        tell_room(environment(this_object()), QCTNAME(this_object()) + 
                  " seems to regard " + QTNAME(from) + " somewhat " +
                  "less suspiciously now.\n", from);
   }
}


void
wolf_reject_object(object ob, object from)
{
    command("emote growls, completely uninterested in " +  
                LANG_THESHORT(ob) + ".");
    if (present(ob, this_object()))
        command("drop " + ob->query_name());
}


void
wolf_consider_food(object ob, object from)
{
    if (!present(from, environment(this_object())))
        return;
    if (ok_to_eat_check(ob))
        wolf_eat_object(ob, from);
    else 
        wolf_reject_object(ob, from);
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    set_alarmv(0.5, 0.0, "wolf_consider_food", ({ob, from}));
}


/* Action of feeding something to wolf */
int
do_feed(string str)
{
    object tp; 
    object o1, o2;

    tp = this_player();
    if (!str) {
        notify_fail(FEED_NF);
        return 0;
    }

    if (!parse_command(str, AN_ALL_INV(tp),
          "%o [to] [the] %o", o1, o2)
        || (o2 != this_object()) || living(o1))  {
        notify_fail(FEED_NF);
        return 0;
    }

    tp->catch_msg("You try to feed " + LANG_THESHORT(o1) + " to " +
                  QTNAME(this_object()) + ".\n");
    tell_room(environment(this_object()), QCTNAME(tp) + " tries " +
             "to feed " + LANG_THESHORT(o1) + " to " + 
             QTNAME(this_object()) + ".\n", tp);
    wolf_consider_food(o1, tp); 
    return 1;
  
}


void
player_try_pull(object tp)
{
    if (!present(tp, environment(this_object())))
        return;

    if (!tp->query_prop(OBJ_I_FED_WOLF)) {
        tp->catch_msg(QCTNAME(this_object()) + " growls at you in rabid " +
                      "hunger, and you step back. Its famished eyes " +
                      "glares at you in distrust.\n");
        tell_room(environment(this_object()), QCTNAME(this_object()) + 
                 " growls at " + QTNAME(tp) + ", who takes a step " +
                 "back.\n", tp);
        return;
    } 

    tp->catch_msg(QCTNAME(this_object()) + " seems to trust you, and " +
                  "you are able to pull the thorn from its paw.\n");
    tell_room(environment(this_object()), QCTNAME(this_object()) + 
             " seems to trust " + QTNAME(tp) + ", and " + 
             tp->query_pronoun() + " is able to pull the thorn " +
             "from its paw.\n", tp);
    command("emote bounds off to rejoin its pack in the hills.");
    tp->remove_prop(OBJ_I_FED_WOLF);

    if (tp->test_bit(WQ_DOM, WQ_GROUP, WQ_BIT)) {
        remove_object();
        return;
    }

    tp->set_bit(WQ_GROUP, WQ_BIT);
    tp->add_exp(WQ_XP);
    tp->command("save");

    tp->catch_msg("You feel more experienced.\n");

    log_file("wolf_quest", tp->query_name() + " solved " +
             "wolf quest: " + ctime(time()) + ".\n");
    remove_object();
}


int
do_pull(string str)
{
    object tp;
    string s1, s2;

    tp = this_player();
    if (!str) {
        notify_fail(PULL_NF);
        return 0;
    }

    if (!parse_command(str, AN_ALL_INV(tp),
      "[the] %w [from] [the] [wolf's] [right] %w [of] [the] [wolf]", s1, s2)
        || (s1 != "thorn") || ((s2 != "paw") && (s2 != "forepaw")))
    {
        notify_fail(PULL_NF);
        return 0;
    }

    tp->catch_msg("You try to pull the thorn from the wolf's " +
                  "right forepaw.\n");
    tell_room(environment(this_object()), QCTNAME(tp) + " tries " +
             "to pull the thorn from the wolf's right forepaw.\n", tp);
    player_try_pull(tp); 
    return 1;
}


void
init_living()
{
    ::init_living();
    add_action(do_feed,"feed");
    add_action(do_pull,"pull");
    add_action(do_pull,"pluck"); 
    add_action(do_pull,"extract"); 
    add_action(do_pull,"draw"); 
    add_action(do_pull,"remove"); 
}

