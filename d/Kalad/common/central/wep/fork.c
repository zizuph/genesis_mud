/*
 * Modified:
 * Cotillion - 2006-04-20
 * - fixed call of ::did_hit
 */

inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
int npc;
#define time 50.0
#define chance 4
#define time_wield 10.0

/* by Korat */
create_weapon()
{
    ::create_weapon();
    set_name("fork");
    set_pname("forks");
    set_adj("military");
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_short("military fork");
    set_long("This is a deadly weapon when used in skilled hands, with its two "+
	     "long prongs that will pierce through flesh and armours with ease and "+
	     "the two hooks that bends backwards. You are not sure, but you "+
	     "think the hooks are used to parry and catch weapons with.\n");
    add_item(({"prong","prongs"}),"Being long and with very sharp tips, these "+
	     "these prongs will pierce through almost anything, especially "+
	     "flesh.\n");
    add_item(({"hook","hooks"}),"The two metal hooks bends backwards in "+
	     "delicately arches, ready to be used to catch weapons and parry blows. "+
	     "To be able to use the full potentional power of such a weapon "+
	     "would demand a life-time of training.\n");
    set_hit(37);
    set_pen(31);
    set_wt(W_POLEARM);
    set_dt(W_IMPALE);
    set_hands(W_BOTH);
    set_wf(TO);
    add_prop(OBJ_I_VALUE,2000);
    add_prop(OBJ_I_WEIGHT,20000);
    add_prop(OBJ_I_VOLUME,20000);
    add_prop(OBJ_S_WIZINFO,
	     "This fork has a special ability: When it hits an arm, "+
	     "it may disarm the weapon wielded in that arm. This ability is limited "+
	     "since one cannot be drunk doing it and it checks the "+
	     "polearm skill vs. awareness off oponent as base for "+
	     "a random chance of success. Furtehr on, its a 1/4 chance that it "+
	     "will succeed. "+
	     "All in all, this ability is more an emote than a special attack. But, "+
	     "one might get lucky...\nAll npc's will wield after a short time, while "+
	     "players has to wield it by themselves...\n");
}


public int
  wield(object wep)
{
    write("With pleasure you glance at the hooks on the fork, thinking "+
	  "on all the weapons you will catch with them!\n");
    return 0;
}

public int
  unwield(object wep)
{
    write("With sadness you look at the hooks on the fork, thinking on "+
	  "all the weapons you didn't catch!\n");
    return 0;
}


public mixed did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{    
    if(phurt>0 &&(hdesc=="left arm" || hdesc=="right arm"))
    {
        set_alarm(0.0,0.0,"try_to_disarm",enemy,hdesc);
    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

int
  try_to_disarm(object enemy,string hdesc)
{
    object wep_in_lefthand;
    object wep_in_righthand;
    object wep_in_bothhands;
    object person;
    object me;
    seteuid(getuid(TP));
    
    if (!TO -> query_wielded())
    {
        return 1;
    }
    
    me = query_wielded();
    person = enemy;
    npc = person->query_npc();
    /* Ok, now lets check if oponent wields a weapon. */
    wep_in_righthand = person->query_weapon(W_RIGHT);
    wep_in_lefthand = person->query_weapon(W_LEFT);
    wep_in_bothhands = person->query_weapon(W_BOTH);
    if (!wep_in_righthand && !wep_in_lefthand && !wep_in_bothhands)
    {
        return 1;
    }
    
    if (!wep_in_bothhands)
    {
        if(hdesc=="left arm" && !wep_in_lefthand)
            return 1;
        if(hdesc=="right arm" && !wep_in_righthand)
            return 1;
    }
    
    /* ok, now lets make it harder to do this ... a 50/50 chance */
    /* If npc, we will not chech for a random chance. */
    if (!me->query_npc())
    {
        if (random(chance)) 
	{
            me->catch_msg("You tried to hook up a weapon, but got too "+
			  "distracted by your environment.\n");
            me->tell_watcher(QCTNAME(me)+" concentrates on disarming "+
			 QTNAME(person)+", but gets distracted.\n",person);
            person->catch_msg(QCTNAME(me)+" tried to disarm you, "+
			      "but got too distracted.\n");
            return 1;
        }
    }
    
    
    /* now, first check if wielder is too drunk to do it */
    if (me->query_intoxicated() > 10)
    {
        me->catch_msg("You try to concentrate on using the hooks to "+
		      "disarm "+QTNAME(person)+", but you fail utterly.\n");
        me->tell_watcher(QCTNAME(me)+" tries to concentrate, but fails utterly!\n",person);
        person->catch_msg(QCTNAME(me)+" tries to concentrate, but fails utterly!\n");
        return 1;
    }
    
    
    /* ok, lets check if s/he manages the trick! */
    if (random((me->query_skill(SS_WEP_POLEARM) -
		person->query_skill(SS_AWARENESS) +100)) < 50)
    {
        me->catch_msg("You try to disarm "+QTNAME(person)+", but fail.\n");
        person->catch_msg(QCTNAME(me)+
			  " swings his fork around and tries to disarm you!\n"+
			  "You notice it in time and avoid the hooks on the fork.\n");
        me->tell_watcher(QCTNAME(me)+" swings the fork around, trying to "+
		     "disarm "+QTNAME(person)+", but misses.\n",person);
        return 1;
    }
    
    /* The disarming worked! */
    me -> catch_msg("You managed to hook up a weapon!\n");
    person -> catch_msg(QCTNAME(me)+
			" catches your weapon with some hooks on the fork!\n");
    me->tell_watcher(QCTNAME(me)+" manages to disarm "+QTNAME(person)+"!\n",person);
    if(wep_in_bothhands)
    {
        person -> command("unwield "+wep_in_bothhands->query_name());
        person->catch_msg("Your weapon is ripped from your hands as "+
			  "the hooks on the fork pulls hard on it!\n");
        if (npc == 1) set_alarm(time_wield,0.0,"do_wield_wep",person,wep_in_bothhands);
        return 1;
    }
    if(wep_in_righthand)
    {
        person -> command("unwield "+wep_in_righthand->query_name());
        person->catch_msg("The weapon is ripped from your right hand when "+
			  "the hooks on the fork pulls hard on it!\n");
        if (npc == 1) set_alarm(time_wield,0.0,"do_wield_wep",person,wep_in_righthand);
        return 1;
    }
    if(wep_in_lefthand)
    {
        person -> command("unwield "+wep_in_lefthand->query_name());
        person->catch_msg("The weapon is ripped from your left hand when "+
			  "the hooks on the fork pulls hard on it!\n");
        if (npc == 1) set_alarm(time_wield,0.0,"do_wield_wep",person,wep_in_lefthand);
        return 1;
    }
    return 1;
}


void
  do_wield_wep(object wielder, object weapon)
{
    if (wielder->query_prop(LIVE_I_STUNNED))
    {
        set_alarm(1.0,0.0,"do_wield_wep",wielder,weapon);
        return;
    }
    wielder -> command("wield "+ weapon->query_name());
    npc = 0;
}


