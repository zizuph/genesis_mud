/*
 * Base class for a Neverwinter bridge guard 
 * by Kehr, October 2006
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>

inherit FAERUN_NPC_BASE;

inherit "/d/Faerun/lib/gems";
inherit "/lib/unique";

#define LOG "/d/Faerun/log/guard_combat"

#define FIGHT_SHIELD_WEP 1
#define FIGHT_WEP_WEP    2	 

void set_level(int sta, int ska);

int use_two_weapons() ;
int use_shield_weapon();
void notify_team_attacked(object attacker);
void order_team_assist(object *team, object attacker);
void do_assist();
void manage_team_assist(object target);
void special_hit_msg(mixed hit, object enemy);
mixed special_hit(object enemy, int i);
object * team_enemies(object member);

int fightmode = 0;

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
	::init_living();
}

void notify_enemy_leaves(object enemy) {
	this_object()->command("shout Come back here you coward!");
	//tell_room(environment(), file_name(enemy) + " is a coward!\n");
	do_assist();
}

void create_faerun_npc()
{
    int i;

    seteuid(getuid());


    set_race_name("human");
    set_short("base smart npc");
    set_pshort("base smart npcs");
    set_long("This is Kehr's base smart npc. This description should be customized.\n");

    add_prop(CONT_I_WEIGHT,80000+random(20000));
    add_prop(CONT_I_HEIGHT,160+random(20)+random(20));
    add_prop(LIVE_I_SEE_DARK,0);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, "Don't try to bribe me!\n");
    add_prop(LIVE_I_ATTACK_THIEF,1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_I_NO_UNARMED, 1);
    
    
    set_alignment(0);
	
	// You REALLY need to call this yourself !
	//set_level (1,0);
	
    set_alarm(1.0, 0.0, "equip_me");
}

/* Sets stats and some skills around given averages
 * sta - stats average
 * ska - skill average
 *
 * WARNING - biased to create "warrior-type" npc's (higher str,dex,con and dis, lower wis and int)
 *           actual stat average might be up to 10% higher
 *			 
 */
void set_level(int sta, int ska) {
	
	int tmp;

	tmp = sta/10;
	
    set_base_stat(0, 110*sta/100 + random(tmp));
    set_base_stat(1, 120*sta/100 + random(tmp));
    set_base_stat(2, 120*sta/100 + random(tmp));
    set_base_stat(3,  70*sta/100 + random(tmp));
    set_base_stat(4,  80*sta/100 + random(tmp));
    set_base_stat(5, 100*sta/100 + random(tmp));
	
	tmp = ska/10;
    set_skill(SS_UNARM_COMBAT,	 80*ska/100 + random(tmp));
    set_skill(SS_DEFENCE,	 90*ska/100 + random(tmp));
    set_skill(SS_WEP_AXE,	100*ska/100 + random(tmp));
    set_skill(SS_WEP_CLUB,	100*ska/100 + random(tmp));
    set_skill(SS_WEP_SWORD,	100*ska/100 + random(tmp));
    set_skill(SS_WEP_POLEARM,	100*ska/100 + random(tmp));
    set_skill(SS_PARRY, 	 90*ska/100 + random(tmp));
    set_skill(SS_AWARENESS, 	 80*ska/100 + random(tmp));
    set_skill(SS_2H_COMBAT, 	 90*ska/100 + random(tmp));

	// ok, thats a cheat - but lets just make them a little bit more difficult ;)
	// up to +60 in AC on all hit locations ;)
	set_all_hitloc_unarmed(min(60, 60*sta/200));

}

void
equip_me()
{
    object torch;
    
    torch = clone_object("/std/torch");
    torch -> set_short("wooden torch");
    torch -> set_long("It is a plain wooden torch that will burn for a while.\n");
    
    torch -> move (this_object());
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

	// who am I ?
	//dump_array(({TO}));
	
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
	if (es == 0 && random(2) == 0) {
		// lets see what is our index on our targets enemy list
		i = member_array(TO, query_attack()->query_enemy(-1));

		hitresult = special_hit(enemy, i);
		special_hit_msg(hitresult, enemy);
		return 1;
	}
	
	return 0;
}

void
special_hit_msg(mixed hit, object enemy)
{
	tell_room(ENV(TO), QCTNAME(TO) + " smiles as he wickedly slashes " + QPNAME(enemy) + " back with his " + TO->query_weapon(-1)[0]->query_name() + ".\n", enemy);
	enemy->catch_tell(QCTNAME(TO) + " smiles wickedly as he buries his " + TO->query_weapon(-1)[0]->query_name() + " deep into your back.\n");
}

mixed 
special_hit(object enemy, int i) 
{
	int dmg;
	// i>1 means our target is already defending from two others
	// so we make him much more vulnerable
	// yes, someone tanking 5 of them is potentially really screwed
	if (i>1) {
		dmg = 100*i;
	} else {
		dmg = 100;
	}	
	return enemy->hit_me(dmg, W_SLASH, TO, -1);
}

// this function is here only because I don't know how to call it directly in a leader
void alarm_helper(object target) {
	set_alarm(30.0, 0.0, &notify_team_attacked(target));
}

void
manage_team_assist(object target)
{
	object *team;
   	object leader;
	int i,m;
	               
	// are we a team member ?
	leader=query_leader();
	if (leader) {
		// lets schedule an notify_team_attacked alarm for a leader - but only if
		// he has no such alarm scheduled !
		tell_room(ENV(TP), "Leader !\n");
		
		mixed *calls = leader->query_alarms();
		m=sizeof(calls);
		
		for (i = 0; i < m; i++) {
			dump_array(calls[i]);
		}
		
		//leader->set_alarm(30.0, 0.0, &notify_team_attacked(target));
		// I'm using this helper because the code above (or many of its variations
		// I managed to devise) did not work
	
		leader->alarm_helper(target);
	//	leader->set_alarm(30.0, 0.0, &(leader->notify_team_attacked(target)));
		
		calls = leader->query_alarms();		
		m=sizeof(calls);
		
		for (i = 0; i < m; i++) {
			dump_array(calls[i]);
		}
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

void                                                                            
attacked_by(object attacker)                                                          
{                                                                               
   // this is called when our npc is attacked by a player         
   //tell_room(ENV(TP), QCTNAME(TO) + " attacked by " + QCTNAME(attacker) + " !\n");
                                                                          
   ::attacked_by(attacker);    
   TO->command("shout Help me!");
   manage_team_assist(attacker);                                                       
}  

// assist teamleader by attacking his target
void do_assist()
{
	object *eteam = team_enemies(TO);
	
	tell_room(ENV(TP), QCTNAME(TO) + " do_assists! ----------------------------------------------\n");
	dump_array(eteam);

	command("kill " + OB_NAME(eteam[0]));	
}

void notify_team_attacked(object attacker)
{
	// this function is called in a team leader
	write("TEAM MEMBER ATTACKED !!!\n");
	object *team;
	
	//command("kill " + attacker->query_name());
	team=query_team();
	
	order_team_assist(team, attacker);	
}

void do_attack(object enemy) 
{
	//tell_room(ENV(TP), QCTNAME(TO) + " do_attack()!\n");
	// ATTENTION: we have to avoid calling of an overloaded attack_object() !
	//command("kill " + e->query_name());
	//attack_object(e, this_object());
	// TODO: add messages here
	command("shout Die fool!");
	tell_room(ENV(TO), QCTNAME(TO) + " attacks " + QTNAME(enemy) + "!\n", enemy);
	enemy->catch_tell(QCTNAME(TO) + " attacks you!\n");	
	::attack_object(enemy);	
}

void order_team_assist(object *team, object attacker)
{
	// list=(list-listN)+listN;
	//tell_room(ENV(TP), QCTNAME(TO) + " order_team_assist()!\n");
	object *eteam;
	object *tmp;
	team = team + ({this_object()});
	int ts, es;
	int t, e;
	
	eteam = ({});
	
	ts = sizeof(team);
	for (t=0; t<ts; t++) {
		tmp = team[t]->query_enemy(-1);
		eteam=(eteam-tmp)+tmp;
	}
	
	//dump_array(eteam);
	
	es = sizeof(eteam);
	
	for (t=0, e=0; t<ts; t++) {
		//if (!team[t]->query_attack())
			team[t]->do_attack(eteam[e]);
		if ((t % 3) == 0) {
			e=(e+1) % es;
		}	
	}
}


// Finds all current enemies of NPC's team
// member is either team leader or team member
// Returns the sorted array (by number of attackers)

// helper function - comparison for sorting
int sort_helper(object a, object b) {
	return sizeof(b->query_enemy(-1)) - sizeof(a->query_enemy(-1));
}

object * team_enemies(object member) {
	// 1. Do we have a team leader ?
	object leader;
	object *team;
	object *eteam;
	object *tmp;
	
	int ts, t;
		
	leader = query_leader();
	if (leader) {
		team = leader->query_team();	
	} else {
		team = query_team();
	}	

	// lets make sure we are in a team (but only once !
	team = (team - ({member})) + ({member});
	// now, lets get the list of our enemies:
	eteam = ({});
	
	ts = sizeof(team);
	for (t=0; t<ts; t++) {
		tmp = team[t]->query_enemy(-1);
		eteam=(eteam-tmp)+tmp;
	}
	return sort_array (eteam, sort_helper);
}

/* --------------------------------------------------------------------------
 * Light management
 */ 

void do_light_torch()
{
	// check if it is still necessary
	//if (environment(TO)->query_prop(OBJ_I_LIGHT)<1)
	if (environment(TO)->light()<1)
		command("light torch");	
}

void do_extinguish_torch()
{
	// check if it is still necessary
	// >1 because torch has +1 light - so it means someone else lit a torch as well
	if (environment(TO)->light()>1)
		command("extinguish torch");	
}

void notify_light_level(int ln)
{
	float time;

	time = 3.0 + 3.0*rnd();
	
	if (ln<1)
		set_alarm(time, 0.0, do_light_torch);
	else
		set_alarm(time, 0.0, do_extinguish_torch); 	
}
	
void hook_torch_burned_out(object torch)
{
	object torch;
	
	tell_room(environment(), short() + " curses silently and grabs a new torch.\n");
	command("drop torch");
	    
    torch = clone_object("/std/torch");
    torch -> set_short("wooden torch");
    torch -> set_long("It is a plain wooden torch that will burn for a while.\n");
    
    torch -> move (this_object());
}
	

