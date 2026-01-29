/*  -*- LPC -*-  */
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>

#include "defs.h"

inherit TELL_FILE;

#define ACROBATICS(who) who->query_skill(SS_ACROBAT)
#define AWARENESS(who)	who->query_skill(SS_AWARENESS)
#define UNARMED(who)	who->query_skill(SS_UNARM_COMBAT)

void get_again(object who);

/*
 * add_delay: Makes the victim wait time heartbeats to get an attack.
 */
void
add_delay(object tp, int time) 
{
    int t;
    if(time>20)
	time = 20;
    t = tp->query_prop(LIVE_I_ATTACK_DELAY);
    if(time>t)
	tp->add_attack_delay(time, 0);
}

void
remove_fumble(mixed *b) {
    string *fumble;
    object tp	  = b[0];
    string mess   = b[1];

    fumble = tp->query_prop(LIVE_AS_ATTACK_FUMBLE);

    if(!fumble || !pointerp(fumble))
	return;

    if(sizeof(fumble)==1) {
	tp->remove_prop(LIVE_AS_ATTACK_FUMBLE);
	return;
    }

    tp->add_prop(LIVE_AS_ATTACK_FUMBLE, fumble - ({ mess }) );
    return;
}


void
add_fumble(object tp, string mess, mixed time) 
{
    string *fumble;

    fumble = tp->query_prop(LIVE_AS_ATTACK_FUMBLE);
    if(!sizeof(fumble))
	tp->add_prop(LIVE_AS_ATTACK_FUMBLE, ({ mess }) );
    else
	tp->add_prop(LIVE_AS_ATTACK_FUMBLE, fumble + ({ mess }) );

    if (intp(time))
	time = itof(time);

    set_alarm(time, 0.0, "remove_fumble", ({ tp, mess }));
}

void
remove_fumble_call(object tp, string this_fumble, string call, object call_obj)
{
    string *fumble = tp->query_prop(LIVE_AS_ATTACK_FUMBLE);

    call_other(call_obj, call, tp, 1);

    if(!fumble || !pointerp(fumble))
	return;

    if(sizeof(fumble)==1) {
	tp->remove_prop(LIVE_AS_ATTACK_FUMBLE);
	return;
    }

    tp->add_prop(LIVE_AS_ATTACK_FUMBLE, fumble - ({ this_fumble }) );
    return;
}
    
varargs void
add_fumble_call(object who, mixed time, string call, object call_obj = previous_object())
{
    string new_fumble;
    string *fumbles;

    new_fumble = "@@handle_fumble:"+file_name(TO)+"|"+file_name(who)+"|"+
	         call+"|"+file_name(call_obj)+"@@";

    fumbles = who->query_prop(LIVE_AS_ATTACK_FUMBLE);
    if (!sizeof(fumbles))
	who->add_prop(LIVE_AS_ATTACK_FUMBLE, ({ new_fumble }) );
    else
	who->add_prop(LIVE_AS_ATTACK_FUMBLE, fumbles + ({ new_fumble }) );

    if (intp(time))
	time = itof(time);
    set_alarm(time, 0.0, "remove_fumble_call", who, new_fumble, call, call_obj);
}

string
handle_fumble(mixed who, string call, mixed call_obj)
{
    who = find_object(who);
    call_obj = find_object(call_obj);
    if (!who || !living(who))
	return "";
    
    return call_other(call_obj, call, who, 0);
}

void
add_cont_fumble(object tp, string mess)
{
    string *fumble;

    fumble = tp->query_prop(LIVE_AS_ATTACK_FUMBLE);
    if(!sizeof(fumble))
	tp->add_prop(LIVE_AS_ATTACK_FUMBLE, ({ mess }) );
    else
	tp->add_prop(LIVE_AS_ATTACK_FUMBLE, fumble +({ mess }) );
}

void
remove_cont_fumble(object tp, string mess)
{
    string *f;

    f = tp->query_prop(LIVE_AS_ATTACK_FUMBLE);
    if(!f || !pointerp(f))
	return;
    if(sizeof(f)<=1) {
	tp->remove_prop(LIVE_AS_ATTACK_FUMBLE);
	return;
    }
    tp->add_prop(LIVE_AS_ATTACK_FUMBLE, f-({mess}));
    return;
}


string
how_str(object who, int dam)
{
    if(dam<0) return "not at all";
    switch(dam*100/HP(who)) {
	case 0..5: return "not badly";
	case 6..20: return "somewhat";
	case 21..40: return "quite";
	case 41..69: return "very";
	case 70..85: return "increadibly";
	case 86..99: return "awesomly";
	default: return "massacrated and badly";
    }
}

/*----------------------------------------------------------*/

void
loose_balance(object who, object tp)
{
    int time = MIN( random(200/(ACROBATICS(who)+1)), 4 + random(20));
	who->catch_msg("You loose your balance and struggle to gain it again!\n");
	tp->catch_msg(QCTNAME(who)+" looses "+HIS_HER(who)+" and struggles to "+
		"gain it again!\n");
    /*tellem(who, tp,
	"$N $loose $p balance and $struggle to gain it again!\n");*/
    add_fumble(who, "You struggle to gain control again!\n", time);
}

void
fall_badly(object who, object tp)
{
    int dam = random(100)+1;
    int time = random(10)+1;
    string how = how_str(who, dam);
    string floor = ENV(who)->query_prop(ROOM_I_INSIDE)?"floor":"ground";
	who->catch_msg("You stumble in your feet and fall over!\n");
	tp->catch_msg(QCTNAME(who)+" stumbles in "+HIS_HER(who)+" feet and "+
		"fall over!\n");
	who->catch_msg("You are "+how_str(who,dam)+" hurt as you hit the floor\n");
	tp->catch_msg(QCTNAME(who)+" are "+how_str(who,dam)+" hurt as "+
	HE_SHE(who)+" falls over!\n");
/*
    tellem(who, tp,
	"$You $stumble in $your feet and $fall over!!\n");
    tellem(who, tp,
	"$You $are "+how_str(who, dam)+" hurt as $he $hit the "+
	floor+".\n");*/
    add_fumble(who, "You are trying to get on your feet again.\n", time);
    who->heal_hp(-dam);
    if(HP(who)<=0)
	who->do_die(tp);
}

void
slip_on_floor(object who, object tp)
{
    string g = ENV(who)->query_prop(ROOM_I_INSIDE)?"floor":"ground";
    int time;

	who->catch_msg("You lip with grace on the "+g+" and loose the opportunity"+
		" to get a vital blow!\n");
	tp->catch_msg(QCTNAME(who)+" slips with grace on the "+g+" and looses the"+
		"opportunity to get a vital blow!\n");
    /*tellem(who, tp,
	"$You $slip with grace on the "+g+" and $loose "+
	"the opportunity to get a vital blow!\n");*/

    time = MIN(1000/(DEX(who)+1), random(20)+1);

    add_fumble(who, "You missed your opportunity!\n", time);
}

void
smooth_moves(object who, object tp)
{
    int time;
 	who->catch_msg(QCTNAME(tp)+"'s smooth moves leave you stunned in "+
		"admiration!\n");
	tp->catch_msg("Your smooth moves leaves "+QTNAME(who)+" stunned "+
		"in admiration!\n");
/*
    tellem(who, tp,
	"#Name's smooth moves $leave $you stunned in admiration!\n");
*/
    time = MIN(1000/(DIS(who)+1), random(20)+1);

    add_fumble(who, "You stand stunned in admiration!\n", time);
}


void
hit_yourself(object who, object tp, int dam)
{
	who->catch_msg("You are shocked in the experience of hitting yourself!\n");
	tp->catch_msg(QCTNAME(who)+" is shocked in the experience of hitting "+
	HIM_HER(who)+"self!\n");
	who->catch_msg("You are "+how_str(who,dam)+" hurt from your own hit!\n");
	tp->catch_msg(QCTNAME(who)+" is "+how_str(who,dam)+" hurt form "+		
	HIS_HER(who)+" own hits!\n");
    /*tellem(who, tp,
	"$You $are shocked in the experience of hitting $yourself!\n");
    tellem(who, tp,
	"$You $are "+how_str(who, dam)+" hurt from $your own hit!\n");*/
    who->heal_hp(dam);
    if(HP(who)<=0)
	who->do_die(tp);
}

void
confused(object who, object tp)
{
    int time;
    
    time =  MIN(random(500/(AWARENESS(who)+1)), 5 + random(20)); 
	who->catch_msg("You get confused and fail to act!\n");
	tp->catch_msg(QCTNAME(who)+" gets confused and fails to act!\n");
    /*tellem(who, tp,
	"$You $get confused and $fail to act!\n");*/
    add_fumble(who, "You are too confused to attack!!\n", time);
}

void
bewildered(object who, object tp)
{
    int time = MIN(2 + random(750/(AWARENESS(who)+1)), 2 + random(20)); 
	who->catch_msg("You are beweildered in realizing that you cannot "+
		"attack!\n");
	tp->catch_msg(QCTNAME(who)+" starts to look funny. "+
		HE_SHE(who)+" fails to attack!\n");
/*
    tellem(who, tp,
	"$You ${are bewildered in realizing that you cannot attack!;" +
	   "starts to look funny. $He fails to attack!}\n");*/
    add_fumble(who, "You are too bewildered to attack!!\n", time);
}

int
loose_grip(object who, object tp)
{
    if(sizeof(who->query_weapon(-1))) {
	who->catch_msg("You loose your gip on your weapon!\n");
	tp->catch_msg(QCTNAME(who)+" looses "+HIS_HER(who)+" grip on "+
		HIS_HER(who)+" weapon!\n");
/*
	tellem(who, tp,
	    "$You $loose $your grip on $your weapon!\n");
*/
	who->command("unwield weapon");
	if(who->query_npc())
	    set_alarm(10.0, 0.0, "wield_again", who);
	return 1;
    } else
	bewildered(who, tp);
}

int
drop_weapon(object who, object tp)
{
    if(sizeof(who->query_weapon(-1))) {
	who->catch_msg("You juggle around with your weapon, and drop it!\n");
	tp->catch_msg(QCTNAME(who)+" juggles around with "+HIS_HER(who)+" weapon "+
		"and drops it!\n");
/*
	tellem(who, tp,
	    "$You $juggle around with $your weapon, and $drop it!");
*/
	who->command("drop weapon");
	if(who->query_npc())
	    set_alarm(itof(random(3)), 0.0, &get_again(who));
	if(tp->query_npc())
	    set_alarm(itof(random(3)), 0.0, &get_again(who));
	return 1;
    } else
	confused(who, tp);
    return 0;
}

wield_again(object who)
{
    who->command("wield weapon");
}

get_again(object who)
{
    who->command("get weapons");
    who->command("wield weapon");
}

int fumble(object who, object tp)
{
    switch(random(10))
    {
	case 0:
	    return 0;
	case 1:
	    loose_balance(who, tp);
	    return 1;
	case 2:
	    fall_badly(who, tp);
	    return 1;
	case 3:
	    hit_yourself(who, tp, random(UNARMED(who)*2)+1);
	    return 1;
	case 4:
	    confused(who, tp);
	    return 1;
	case 5:
	    bewildered(who, tp);
	    return 1;
	case 6:
	    loose_grip(who, tp);
	    return 1;
	case 7:
	    drop_weapon(who, tp);
	    return 1;
	case 8:
	    slip_on_floor(who, tp);
	    return 1;
	case 9:
	    smooth_moves(who, tp);
	    return 1;
    }
}
