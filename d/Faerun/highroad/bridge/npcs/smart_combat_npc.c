#pragma strict_types
#pragma no_clone

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

//inherit FAERUN_NPC_BASE;
inherit "/d/Faerun/highroad/bridge/npcs/base_npc.c";

/*
 * "Smart" combat (solo and team) routines
 *  
 * by Kehr, October 2006 - March 2007
 */


#define LOG "/d/Faerun/log/guard_combat"
#define FIGHT_SHIELD_WEP 1
#define FIGHT_WEP_WEP    2	 

private int fightmode = 0;
private int alarm_id = 0;

int get_alarm_id() 
{ 
	return alarm_id;
}

void set_alarm_id(int id) 
{
	alarm_id = id;
}

int use_two_weapons() ;
int use_shield_weapon();
void notify_team_attacked(object thisobj, object target);
void order_team_assist(object *team, object attacker);
void do_assist();
void manage_team_assist(object target);
void special_hit_msg(mixed hit, object enemy);
mixed special_hit(object enemy, int i);
object * team_enemies();
void do_attack(object enemy);


void set_fightmode(int mode)
{
	fightmode=mode;
}

int get_fightmode ()
{
	return fightmode;	
}

void init_living() {
	//tell_room(environment(), file_name(this_player()) + " entered the room!\n");
	//::init_living();
}

void notify_enemy_leaves(object enemy) {
	this_object()->command("shout Come back here you coward!");
	//tell_room(environment(), file_name(enemy) + " is a coward!\n");
	do_assist();
}


int use_two_weapons() 
{
	command("remove shield");
	command("wield all");
	return 0;
}

int use_shield_weapon() 
{
	command("unwield all");
	command("wear shield");
	command("wield all");
	return 0;
}

int special_attack(object enemy)
{
	object *enemies;
	int es, i;
	int flag=0;
	mixed *hitresult;

	// how many people do I defend from ?
	enemies = query_enemy(-1)->query_attack() & ({this_object()});
	//dump_array(enemies);
	
	es = sizeof (enemies);

	// switch to 2 handed fighting if not tanking	
	if (es == 0 && fightmode != FIGHT_WEP_WEP) {
		use_two_weapons();
		fightmode=FIGHT_WEP_WEP;
	} else if (es > 0 && fightmode != FIGHT_SHIELD_WEP) {
		use_shield_weapon();
		fightmode=FIGHT_SHIELD_WEP;
	}
	
	// lets punish mega tankers
   	//dump_array(query_attack()->query_enemy(-1));

	// if we are not tanking we may try to execute a special attack
	// random(2) = 50% chance
	// otherwise we have 25% chance for a weaker spec
	if (es == 0 && random(2) == 0) {
		// lets see what is our index on our targets enemy list
		i = member_array(TO, query_attack()->query_enemy(-1));

		hitresult = special_hit(enemy, i);
		special_hit_msg(hitresult, enemy);
		return 1;
	} else if (random(4) == 0) {
		special_hit_msg(hitresult, enemy);
		return 1;
	}
	
	return 0;
}

void
special_hit_msg(mixed hit, object enemy)
{
	tell_room(ENV(TO), QCTNAME(TO) + " smiles as he wickedly slashes " + QPNAME(enemy) + " back with his " + TO->query_weapon(-1)[0]->query_name() + ".\n", enemy);
	enemy->catch_vbfc(QCTNAME(TO) + " smiles wickedly as he buries his " + TO->query_weapon(-1)[0]->query_name() + " deep into your back.\n");
}

mixed 
special_hit(object enemy, int i) 
{
	int dmg = 100;
	// i>1 means our target is already defending from two others
	// so we make him much more vulnerable
	// yes, someone tanking 5 of them is potentially really screwed
	if (i>1) {
		dmg = dmg*i;
	} 
	return enemy->hit_me(dmg, W_SLASH, TO, -1);
}

/* -------------------------------------------------------------
 *
 *   TEAM MANAGEMENT
 * 
 * ------------------------------------------------------------- */


// Called in team leader via alarm
// so we pass thisobj to make sure its valid !
void notify_team_attacked(object thisobj, object target)
{
	// first thing - clear alarm_id so that we could react 
	// for future attacks
	
	thisobj->set_alarm_id(0);
	
	// this function is called in a team leader
	//tell_room(ENV(thisobj), "TEAM MEMBER ATTACKED, alarm_id=0 !!!\n");
	
	order_team_assist(thisobj->query_team(), target);
}


// This function checks if we have an alarm scheduled

void notify_team_attacked_helper(object target) {
	//tell_room(ENV(TO), "Notify TEAM ATTACKED !!!\n");
	if (alarm_id == 0) {
		alarm_id = set_alarm(3.0, 0.0, &notify_team_attacked(TO, target));
	}
}

void manage_team_assist(object target)
{
	object *team;
   	object leader;
	int i,m;
	               
	// are we a team member ?
	leader=query_leader();
	if (leader) {
		// Call leader's team management function
		//tell_room(ENV(TP), "Telling leader we need help !\n");
		
		// we are calling a helper function because we need to 
		// avoid calling notify_team_attacked to often 
		leader->notify_team_attacked_helper(target);

/*		mixed *calls = leader->query_alarms();
		m=sizeof(calls);
		
		for (i = 0; i < m; i++) {
			dump_array(calls[i]);
		}
*/		
	//	leader->set_alarm(30.0, 0.0, &(leader->notify_team_attacked(target)));
		
		//leader->notify_team_attacked(target);
		return;
	}
	
	// nah, we are team leader (or alone)
	team=query_team();
	if (team) {
		order_team_assist(team, target);
		return;
	}
	//write("I am all alooone!\n");                       
}

void                                                                     
attack_object(object target) 
{
/*	tell_room(ENV(TP), "attack_object(" + file_name(ob) +")\n");
	tell_room(ENV(TP), "this_object() = " + file_name(this_object()) +"\n");
	tell_room(ENV(TP), "this_player() = " + file_name(this_player()) +"\n");
	tell_room(ENV(TP), "this_interactive() = " + file_name(this_interactive()) +"\n");
	tell_room(ENV(TP), "query_verb() = " + query_verb() +"\n");
	tell_room(ENV(TP), "previous_object() = " + file_name(previous_object()) +"\n");
	tell_room(ENV(TP), "previous_object(-1) = " + file_name(previous_object(-1)) +"\n");
	tell_room(ENV(TP), "previous_object(-2) = " + file_name(previous_object(-2)) +"\n");
	*/
	
	// This routine is called when this npc attacks a player due to:
	// 1. player forcing him to attack (steal, maybe other skills)
	// 2. npc->command("kill player") is invoked
		
	::attack_object(target);
    TO->command("shout Die!");
	manage_team_assist(target);
}

/* 
 * This is called when our npc is attacked by a player
 */

void attacked_by(object attacker)                                                          
{                                                                               
	object leader;
	object *team;
	//tell_room(ENV(TP), QCTNAME(TO) + " attacked by " + QCTNAME(attacker) + " !\n");

	// Do we have a leader ?
	leader = query_leader();
	
	// Am I team leader (== do I have a team ?)
	team = query_team();
	
	if (leader) {
		// alarm_id in leader == 0 means that leader is not yet scheduling
		// any team assist
		if (leader->get_alarm_id() == 0) { 
			TO->command("shout Help me!");
		}	
		manage_team_assist(attacker);
			
	} else if (sizeof(query_team())) {
		TO->command("shout You will regret this!");
		manage_team_assist(attacker);
	}
	
	// Call standard routine	
	::attacked_by(attacker);    
}  

// assist teamleader by attacking his target
// FIXME: replace with a query to team leader that returns an optimal target
void do_assist()
{
	object *eteam = team_enemies();
	
	//tell_room(ENV(TP), QCTNAME(TO) + " do_assists! ----------------------------------------------\n");
	//dump_array(eteam);

	do_attack(eteam[0]);	
}


// perform attack but avoid calling attack_object defined in this file
void do_attack(object enemy) 
{
	//write("In do_attack...\n");
	if (ENV(TO) != ENV(enemy))
		return;
	
	if (TO->query_combat_object()->cb_query_attack() != enemy)
	{
		command("shout Die fool!");
		tell_room(ENV(TO), QCTNAME(TO) + " attacks " + QTNAME(enemy) + "!\n", enemy);
		enemy->catch_vbfc(QCTNAME(TO) + " attacks you!\n");	
		::attack_object(enemy);
	}	
}

// This function is called by team leader
// Leader makes an assesment of current combat situation and
// gives orders to his teammates (and to himself)

/*
 
 1. tanker[]  - for each TM (team member) count how many people attack him
 2. target[]  - list whom each TM attacks
 3. enemies[] - list of all enemies of our team
 4. etanker[] - for each enemy - count how many TM attack him
 
 The attack procedure is as follows:
 1. check if someone attacks team leader. rescue him if possible (that is - if any of
    team members are still alive)
    
 2. for each unoccupied team   
 
 1. get enemies[], sort it by
 	- stat average, altered by  
 Now, for each _not_attacked_ enemy (that is - etanker[i]=null - noone attacks us)
 
 
 
 
 */ 

void order_team_assist(object *team, object attacker)
{
	int ts, es;
	int t, e;

	// list=(list-listN)+listN;
	
	// Lets get a list of our enemies
	object *eteam = team_enemies();
	eteam = (team_enemies() - ({attacker})) + ({attacker});
	team = team + ({this_object()});

	ts = sizeof(team);
	es = sizeof(eteam);
	
	/*eteam = ({});
	for (t=0; t<ts; t++) {
		tmp = team[t]->query_enemy(-1);
		eteam=(eteam-tmp)+tmp;
	}*/
	
	
	/*tell_room(ENV(TO), "---------------------- TEAM ENEMIES --------------------\n");
	dump_array(eteam);

	tell_room(ENV(TO), "---------------------- TEAM MEMBERS --------------------\n");
	dump_array(team);
	*/
	
	for (t=0, e=0; t<ts; t++) {
		
		team[t]->do_attack(eteam[e]);
		if ((t % 2) == 0) {
			e=(e+1) % es;
		}	
	}
}


// Finds all current enemies of NPC's team
// member is either team leader or team member
// Returns the sorted array (by number of attackers)

// helper function - comparison for sorting

int sort_helper(object a, object b) {

	// sort by size
	return a->query_average_stat() - b->query_average_stat();
    // sort by the number of enemies fought
	// return sizeof(b->query_enemy(-1)) - sizeof(a->query_enemy(-1));
}

object * team_enemies() {
	// 1. Do we have a team leader ?
	object leader;
	object *team;
	object *eteam;
	object *tmp;
	
	int ts, t;
		
	leader = query_leader();
	if (leader) {
		team = leader->query_team();	
		team = team + ({leader});
	} else {
		team = query_team();
		team = team + ({TO});
	}	

	ts = sizeof(team);

	// now, lets get the list of our enemies:
	eteam = ({});
	
	for (t=0; t<ts; t++) {
		tmp = team[t]->query_enemy(-1);
		eteam=(eteam-tmp)+tmp;
	}

	// 
	function f = &operator(==)(ENV(TO)) @ &environment();
	eteam = filter(eteam, f);
	eteam = sort_array (eteam, sort_helper);
	//dump_array(eteam);
	return eteam;
}



