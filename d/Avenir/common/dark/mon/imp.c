// file name:		~Avenir/common/dark/mon/imp.c
// creator(s):		Denis
// revision history:
//			Denis, Jan'96: Minor changes due to impquest recoding.
//			Denis, Jul'96: Removed poison, it scared people far too
//				       much. Added logging death to statserv.
// purpose:		common inhabitant of Unterdark Level 3 
// note:		monster with stats 50+random(10) with lots of
//			special attacks and other features.
//	 		gives no corpse after killing turning into statue which
//			becomes alive again after some time.
// bug(s):
// to-do:

#include "../l3/l3_defs.h"
//#include "/d/Avenir/smis/sys/statserv.h"

inherit "/std/npc";
inherit "/std/combat/humunarmed";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/action";

#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/common/dark/l3/l3_defs.h"

object chains;           // Object pointer to the mighty paralyzer
// to hold in the air.
int flying;              // Im flying and holding someone while my friend
// helps me to deal with him.
mixed imps;              // Temporary variable to sort out all that can
// help us.
int fly_id;
int slave;

/*-----[ Prototypes ]-----*/
void imps_in_room();
void flying_special(object victim);
void flying_slave(object victim);

public void
create_npc()
{
    set_name("dark imp");
    set_race_name("imp");
    set_adj("dark");
    set_short("dark imp");
    set_long("A grotesquely shaped creature of the shadows, it reminds"+
      " you of a gargoyle.\nTwo leathery wings protrude from a"+
      " misshapen back, while a long barbed tail waves threateningly."+
      " The last time you saw something like this, it was in a nightmare.\n");

    set_stats(({50+random(10),50+random(10),50+random(10),                 
	50+random(10),50+random(10),50+random(10)}));              
    set_hp(query_max_hp());                                                
    set_appearance(10);
    set_gender(G_NEUTER);                                                  


    set_act_time(4);
    add_act("@@combat_hook");

    set_attack_unarmed(W_RIGHT,15,17,W_SLASH|W_BLUDGEON,20,"right claw");
    set_attack_unarmed(W_LEFT,15,17,W_SLASH|W_BLUDGEON,20,"left claw");
    set_attack_unarmed(W_BOTH,10,15,W_SLASH|W_IMPALE,10,"tail");
    set_attack_unarmed(W_FOOTL,15,15,W_BLUDGEON,10,"left wing");
    set_attack_unarmed(W_FOOTR,15,15,W_BLUDGEON,10,"right wing");

    set_hitloc_unarmed(A_BODY,35,50,"body");
    set_hitloc_unarmed(A_HEAD,20,10,"wings");
    set_hitloc_unarmed(A_LEGS,20,10,"tail");
    set_hitloc_unarmed(A_R_ARM,20,15,"right arm");
    set_hitloc_unarmed(A_L_ARM,20,15,"left arm");

    set_skill(SS_DEFENCE,50+random(10));
    set_skill(SS_WEP_SWORD,60+random(30));
    set_skill(SS_WEP_POLEARM,80+random(10));

    add_prop(LIVE_I_NO_CORPSE,1);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,
      " won't accept any gifts from you.\n");
    add_prop(IS_IMP, 1);

    set_alarm(5.0,0.0,"reset_room_env");
}

public void
reset_room_env()
{
    environment(TO)->delayed_reset_room();
}

/*--[ Provides tail regeneration and help to friends through emote ]--*/
public string
combat_hook()
{
    object will_help;
    int i;

    will_help=0;
    imps_in_room();
    if(!query_attack())
	for(i=0;i<sizeof(imps);i++)
	    if(imps[i]->query_attack())
		will_help=imps[i];
    if(will_help)
    {
	set_alarm(3.0,0.0,"attack_enemy",will_help->query_attack());
	return "grin devil";
    }

    if(random(3))
	return "";

    switch(random(3))
    {
    case 0:
	return "emote stares into space.";
    case 1: 
	return "emote flaps its wings.";
    case 2:
	return "emote taps its foot impatiently.";
    }
}

public void
attack_enemy(object victim)
{
    command("kill "+victim->query_real_name());
}

/*
static void
tell_watcher(string str, object enemy)
{
    object *ob;
    int i;

    ob = FILTER_LIVE(all_inventory(environment(TO)))-({TO});
    ob -= ({enemy});
    for(i=0;i<sizeof(ob);i++)
	if(ob[i]->query_i_see_blood())
	    ob[i]->catch_msg(str);

}
*/
/*--[ All the nasty things start here. ]-----*/
public int
special_attack(object victim)
{
    if(random(5)||flying)
	return 0;

    switch(random(3))
    {
    case 0:
	// Hurting special attack.
	tell_watcher(
	  QCTNAME(TO)+" jumps and turns around in the air, biting "+
	  QTNAME(victim)+" with its tail.\n",victim);
	victim->catch_msg(
	  QCTNAME(TO)+" jumps and turns around in the air, biting "+
	  "you with its tail.\n");
	victim->hit_me(50,W_SLASH,TO,-1);
	return 1;
	break;
    case 1:
	// Impaling.
	tell_watcher(
	  QCTNAME(TO)+" stings "+QTNAME(victim)+" with its tail.\n",victim);
	victim->catch_msg(QCTNAME(TO)+" stings you with its tail.\n");
	victim->hit_me(35,W_IMPALE,TO,-1);
	return 1;
	break;
    case 2:
	// Raise him into the air!
	imps_in_room();
	if(!sizeof(imps)||random(3))
	    return 0;
	if(sizeof(imps)==1||random(3))
	    flying_special(victim);
	else
	    return 0;

	return 1;
	break;
    }
}

public void
imps_in_room()
{
    imps=filter(all_inventory(environment(TO)),"is_imp",TO);
    imps-=({TO});
}

public int
is_imp(object ob)
{
    if(ob->query_name()=="Dark imp"&&TO!=ob)
	return 1;
}

/*-----[ If there are at least 2 imps in the room this function ]-----*/
/*-----[ raises player into the air and the second imps attacks ]-----*/
/*-----[ the player. The first imp can be hurt only by polearms ]-----*/
/*-----[ that time.                                             ]-----*/
public void
flying_special(object victim)
{
    int duration;

    if(present("chains",victim))
	return;

    flying=1;

    victim->catch_msg("The dark imp raises you off the ground, suspending "+
      "you in midair. Another imp, taking advantage of your "+
      "helpless condition, sinks it claws into you! "+
      "Nothing can save you, all is lost.\n");
    chains=clone_object(OBJ+"chains");
    chains->move(victim);
    chains->set_fail_message(
      "You cannot do that, the dark imp holds you in the air!\n");
    chains->set_no_show();
    chains->set_remove_time(duration+1);
    fly_id=set_alarm(itof(duration),0.0,"stop_flying");
    imps[0]->flying_slave(victim);

    duration=40+random(20);
    add_attack_delay(duration, 1);
    victim->add_attack_delay(duration, 1);
}

public void
flying_slave(object enemy)
{
    command("kill "+enemy->query_real_name());
}

public void
stop_flying()
{
    flying=0;
    environment(chains)->catch_msg(
      "Unable to hold you anymore, the dark imp releases you and you fall on "+
      "the ground.\n");
    tell_room(environment(TO),"The dark imp stops flying.\n");
    if(objectp(imps[0]))
	imps[0]->stop_slave();

    chains->remove_object();
    remove_prop(LIVE_I_ATTACK_DELAY);
}

public void
stop_slave()
{
}

public mixed *
hit_me(int wcpen, int dt, object attacker, int aid, int hloc)
{
    if (flying &&
	(!attacker->query_weapon(aid) ||
	    attacker->query_weapon(aid)->query_wt() != W_POLEARM))
    {
	return ({ -1,
	    ({"body","tail","left wing","right wing"})[random(4)],
		  -1,
		  -1,
		  -1 });
    }
    return ::hit_me(wcpen, dt, attacker, aid, hloc);
}

public void
do_die(object killer)
{
    if(flying)               // Make an imp stop flying if it dies.
    {
	remove_alarm(fly_id);
	stop_flying();
    }

    if (random(3))
	query_weapon(W_RIGHT)->remove_object();

    if (random(3))
	query_weapon(W_LEFT)->remove_object();

    tell_room(environment(TO),capitalize(short())+" steps back to the "+
      "tunnel wall and turns into a statue!\n");
    environment(TO)->add_prop(STATUES_IN_ROOM,
	environment(TO)->query_prop(STATUES_IN_ROOM)+1);

//    STATSERV_LOG_EVENT("impquest", "Imp died");

    ::do_die(killer);
}
