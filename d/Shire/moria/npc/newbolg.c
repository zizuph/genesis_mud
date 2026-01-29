/*   Replaced the IM_TELL_FILE functions  -Igneous- Dec 5th 96
 *
 *   Made bolg hunt players, he's not too agressive thought so most
 *   players venturing in Moria should live ;) -Igneous April 16th 1997
 *
 *   Final tweeking with the hunting routines -Igneous June 14th 1997
 */  


#include "defs.h"

inherit BASE_MONSTER;

#include <const.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <filter_funs.h>

#include "/d/Shire/moria/skills/skill_types.h"

#define BOLG_HUNTER_LOG "/d/Shire/moria/npc/bolg_hunt.log"
#define BOLG_KILLER_LOG "/d/Shire/log/kill/bolg_killers.log"
#define HUNT_SHADOW     "/d/Shire/moria/npc/follow.c"


#define DEBUGGING
//  Comment out the undefine if you wish to clone Bolg otherwise
//  He will he will make his way to the mines.
// #undef  DEBUGGING

object w1,w2,w3;
int time_next;	  /* Next time to check for players in Moria. */

static object prey = 0;
static int    shadowed = 0;
int           hunt_alarm = 0;

void check_health();
void arm_me();
void bolg_kick(object enemy);
void bolg_headbutt(object enemy);
void do_intro(string who);
void start_hunting();
void my_attack();

string
short() { return "very evil Uruk captain"; }

string
query_nonmet_name() { return "Uruk Captain"; }

string
query_met_name() { return "Bolg"; }

#ifndef DEBUGGING
public void
set_restrain_path_with_delay()
{
    if (!query_restrain_path() || !sizeof(query_restrain_path()))
	set_restrain_path(implode(explode(file_name(ENV(TO)),"/")[0..3], "/"));
}  
#endif

CONSTRUCT_MONSTER
{
    if (!IS_CLONE)
	return;

    set_name("bolg");
    add_name("captain");
    add_name("_uruk_hai_captain_");
#ifndef DEBUGGING
    set_living_name("bolg");
#endif
    add_name("orc");
    set_race_name("uruk");
    add_adj("uruk-hai");
    add_adj("evil");
    set_title("the Large, Son of Azog, Captain of the Red-Claws");

    /*
    set_long(
	"This is a Uruk-Hai orc captain (very evil).\n"+
	"Uruk-Hai is a special race --- They were crossed between orcs and elves "+
	"and corrupted by the evil Sauron. They are big and ugly, though not as "+
	"much as the orcs and the trolls. "+
	"It is said that they are both cunning in witch-craft and swordsmanship, "+
	"and they can endure the light of day!\n");
    */

    set_alignment(-700);
    set_gender(G_MALE);
    set_aggressive(my_attack);

    set_act_time(5);
    add_act("say What do you do here, Snaga!!?");
    add_act("emote spits on you.");
    add_act("say Bug off, pity moron!");
    add_act("say If YOU ever get nice, I'll smash your brains!");
    add_act(({"emote hits you in the stomack!","emote made you puke on your shoes."}));
    add_act("emote lifts his voluminous feet and stamps them on the floor!");
    add_act("say No action here, ever! Wanna fight, you piece of shit!");
    add_act("grin");
    add_act(({"scream","emote 's scream causes rocks to fall on your heads, but the Captain is not affected."}));
    add_act("emote kicks you in the groin and laughs! (What an asshole!!)");
    add_act("emote looks carefully at his armour.");
    add_act(({"say One good soul here, and I'll convert him!","grin"}));
    add_act("yawn");
    add_act("say Hey! YOU! Go and kill some good guys!");

    set_cact_time(4);
    add_cact("emote laughs, and says: You really think you've got a chance, SNAGA!");
    add_cact("say What a pityful performance, MUD-FACE!!");
    add_cact("emote puts two fingers in your eyes and throws you away!");
    add_cact("shout BETTER TO BURN OUT, THAN FADE AWAY!!");
    add_cact("laugh");
    add_cact("emote throws his knee into your face!!!");
    add_cact("yawn");
    add_cact("emote spits right into your face!!");
    add_cact("say I'll rip your nasty heart out and eat it raw!!");

    add_prop(CONT_I_WEIGHT, 300*1000);
    add_prop(CONT_I_HEIGHT, 400);

    add_prop(NPC_M_NO_ACCEPT_GIVE, " doesn't want your crap!\n");
    set_stats( ({ 200, 250, 235, 45, 20, 150 }) );

    set_skill(SS_WEP_SWORD,    100);
    set_skill(SS_WEP_AXE,      100);
    set_skill(SS_WEP_CLUB,	100);
    set_skill(SS_WEP_KNIFE,	90);
    set_skill(SS_WEP_POLEARM,  100);
    set_skill(SS_DEFENCE,	90 + random(11));
    set_skill(SS_PARRY,        100);
    set_skill(SS_AWARENESS,	90);
    set_skill(SS_BLIND_COMBAT, 100);

    add_prop(LIVE_I_SEE_DARK,	10); /* Night vision. */

    set_skill(SS_PUNCH, 	80);
    set_skill(SS_BASH,		50);
    set_skill(SS_DIS_FOE_ARMED,	50);
    set_skill(SS_DIS_FOE_UNARMED, 50);

    set_pick_up(43);

    set_random_move(10);
#ifndef DEBUGGING
    set_monster_home(MINES_DIR+"mjunc");
    /*    set_restrain_path(MINES_DIR); */
#endif

    set_alarm(1.0, 0.0, &arm_me());
    set_alarm(120.0, 120.0, &check_health());

    add_prop(NPC_I_NO_LOOKS, 1);
}

int
my_attack()
{
    if (present(prey, ENV(TO)))
    {
        if (TP != prey)
	    return 0;
    }
    return 1;
}

void
arm_me()
{
    clone_object(MORIA_ARM+"blackpl")->move(this_object(), 1);
    clone_object(MORIA_ARM+"gorget")->move(this_object(), 1);
    clone_object(MORIA_ARM+"skullhel")->move(this_object(), 1);
    clone_object(MORIA_ARM+"hauberk")->move(this_object(), 1);
    clone_object(MORIA_ARM+"orcshield")->move(this_object(), 1);
    //    clone_object(MORIA_ARM+"comboots")->move(this_object(), 1);

    w1=clone_object(MORIA_WEP+"maul"); w1->move(this_object(),1);
    w2=clone_object(MORIA_WEP+"orcaxe"); w2->move(this_object(), 1);

    /*  w3=clone_object(MORIA_WEP+"dagger"); w3->move(this_object(), 1); */

    command("wear fullplate");
    command("wear gorget");
    command("wear boots");
    command("wear helmet");
    command("wear hauberk");
    command("wield maul");
    command("wear shield");
    command("scream");
#ifndef DEBUGGING    
    if (!query_restrain_path() || !sizeof(query_restrain_path()))
	set_alarm(0.0, 0.0, set_restrain_path_with_delay);   
#endif
}

//
// Bolg's special abilities:
// * Takes half damage from hits.
// * Heals twice normal speed.
//
void
heal_hp(int dam)
{
    if (dam < 0)
	::heal_hp(dam / 2);
    else 
	::heal_hp(dam * 2);
}

void
check_health() 
{
    if (query_hp() <= (query_max_hp() - 200))
    {
	if (query_mana() >= 100) 
	{
	    tell_room(ENV(TO),
	      "The Captain suddenly gets a flashing red light in his eyes, screams terribly\n"+
	      "and then he seems to get back to normal. That is.. he seems to be\n"+
	      "much better now, as if he was healed by an obscene dark power....\n");
	    heal_hp(500 + random(1200));
	    add_mana(-100);
	    add_panic(-250);

	}
    }    
    start_hunting();
}

void
do_command(object who)
{
    switch(random(7))
    {
    case 0:
	if( (SKILL_DIR+"bash")->bash(who, TO))
	    break;
    case 1:
	if( (SKILL_DIR+"fumble")->fumble(who, TO))
	    break;
    case 2:
	if( (SKILL_DIR+"fist")->fist_punch(who, TO, W_LEFT))
	    break;
    case 3:
	if( (SKILL_DIR+"fist")->fist_punch(who, TO, W_RIGHT))
	    break;
    case 4:
	if( (SKILL_DIR+"disarm_a")->disarm_foe_armed(who, TO))
	    break;
    case 5:
	if( (SKILL_DIR+"disarm")->disarm_foe_unarmed(who, TO))
	    break;
    case 6:
	command("frighten "+lower_case(who->query_name()));
	break;
    case 7:
	command("kick");
	break;
    }
}

void
check_fight_status()
{
    object *wep = query_weapon(-1);
    if(sizeof(wep))
	return;
    if(present("maul", ETO))
	command("get maul");
    if(present("maul", TO))
    {
	command("wield maul");
	command("shout HA! I am ready for battle ANYTIME and ANYWHERE, fool!");
	return;
    }

    if(present("waraxe", ETO))
	command("get waraxe");
    if(present("waraxe", TO))
    {
	command("wield waraxe");
	command("shout Thought you could fool me, BASTARD!");
	return;
    }

    /*
    if(present(w2, ETO))
	command("get scimitar");
    if(present(w2, TO)) {
	command("wield scimitar");
	return;
    }
    if(present(w3, ETO))
	command("get dagger");
    if(present(w3, TO)) {
	command("wield dagger");
	command("shout PECKS!!");
	return;
    }
    */
}


int
special_attack(object who)
{
    check_fight_status();

    switch(random(6)) {
    case 0:
	who->catch_msg(QCTNAME(TO)+" jumps over you and kicks you "+
	  "from behind!\n");
	tell_room(ENV(TO),QCTNAME(TO)+" jumps over "+QTNAME(who)+
	  " and kicks "+HIM_HER(who)+" in the behind!\n",({who,TO}));
	bolg_kick(who);
	return 1;
    case 1:
	who->catch_msg(QCTNAME(TO)+" headbutts you right in the nose!!!\n");
	tell_room(ENV(TO),QCTNAME(TO)+" headbutts "+QTNAME(who)+
	  " right in the nose!!!\n",({TO,who}));
	bolg_headbutt(who);
	return 1;
    case 2:
	change_opponent();
    }
    return 0;
}

void
bolg_kick(object enemy) 
{
    int bolg_dex = query_stat(SS_DEX);
    int bolg_str = query_stat(SS_STR);
    mixed  *hitresult;
    string *how = allocate(2);

    hitresult = enemy->hit_me(bolg_str + bolg_dex + random(100) ,
      W_BLUDGEON, this_object(), -1);
    if (enemy->query_wiz_level())
	enemy->catch_msg("Bolg did "+hitresult[3]+" damage to your "+hitresult[1]+"!\n");
    switch (hitresult[3])
    {
    case 0:
	how[0] = "misses you entirely!\n";
	how[1] = "misses "+QTNAME(enemy)+" entirely!\n";
	break;
    case 1..150:
	how[0] = "bruises your "+hitresult[1]+" slightly.\n";
	how[1] = "bruises "+QTNAME(enemy)+"'s "+hitresult[1]+" slightly.\n";
	break;
    case 151..400:
	how[0] = "leaves an extremely painful bruise on your "+
	hitresult[1]+"!\n";
	how[1] = "leaves an extremely painful bruise on "+QTNAME(enemy)+
	"'s "+hitresult[1]+"!\n";
	break;
    default:
	how[0] = "crushes your "+hitresult[1]+" with a forcefull blow!\n";
	how[1] = "crushes "+QTNAME(enemy)+"'s "+hitresult[1]+" with a "+
	"forcefull blow!\n";
    }
    enemy->catch_msg(QCTNAME(TO)+"'s kick "+how[0]);
    TO->tell_watcher(QCTNAME(TO)+"'s kick "+how[1], enemy);
    if (enemy->query_hp() <= 0)
	enemy->do_die();
}

void
bolg_headbutt(object enemy)
{
    int bolg_str = query_stat(SS_STR);
    int bolg_dis = query_stat(SS_DIS) / 2;
    mixed *hitresult;

    hitresult = enemy->hit_me(bolg_str+bolg_dis + random(150),
      W_BLUDGEON, this_object(), -1, TS_HEAD);
    if (enemy->query_wiz_level())
	enemy->catch_msg("Bolg did "+hitresult[3]+" damage to your "+hitresult[1]+
	  ".\n");
    if (enemy->query_hp() <= 0)
    {
	enemy->do_die();
	return;
    }
    enemy->add_attack_delay(hitresult[3] / 50 + 5, 0);
    if (enemy->query_prop(LIVE_I_ATTACK_DELAY))
	enemy->catch_msg("You feel stunned by the forcefull hit to your "+
	  "nose.\n");
}

int
query_knight_prestige() { return 1200; }

int
add_introduced(string who)
{
    if (strlen(who)) 
    {
	who = lower_case(who);
	set_alarm(itof(random(7)), 0.0, &do_intro(who));
    }
    return 1;
}

int last_intro;

void
do_intro(string who)
{
    object obj;

    if((obj=present(who, ETO)))
    {
	if (obj->query_npc()) {
	    command("kick " + who);
	    return;
	}
	if (time() < last_intro + 20) {
	    command("yawn");
	    return;
	}
	last_intro = time();
	command("grin");
	command("introduce me");
	command("puke " + who);
	command("shout I'll tear your bloody remains and eat you raw " +
	  "when I am done with you, " + CAP(who) + "!!");
    }
}

public int
second_life(object killer)
{
    object *team;
    int i;

    team = killer->query_team_others();
    setuid(); seteuid(getuid());
    write_file(BOLG_KILLER_LOG,ctime(time()) + " "+
      capitalize(killer->query_real_name())+" ("+killer->query_average_stat()+
      ") killed Bolg"+(sizeof(team) ? " with the help of:" : ".")+"\n");
    for (i = 0;i < sizeof(team); i++)
    {
	write_file(BOLG_KILLER_LOG,capitalize(team[i]->query_real_name())+
	  "("+team[i]->query_average_stat()+")     ");
    }
    write_file(BOLG_KILLER_LOG,"\n\n");
    return 0;
}

//  Here are the hunting functions :)
public void
attack_object(object ob)
{
    if (!prey && !shadowed && !hunt_alarm)
	hunt_alarm = set_alarm(itof(8 + random(8)),0.0,&start_hunting());
    ::attack_object(ob);
}

public void
attacked_by(object ob)
{
    if (!prey && !shadowed && !hunt_alarm)
	hunt_alarm = set_alarm(itof(8 + random(8)),0.0,&start_hunting());
    ::attacked_by(ob);
}

void
start_hunting()
{
    object *enemies;

    if (hunt_alarm)
    {
        remove_alarm(hunt_alarm);
	hunt_alarm = 0;
    }
    //  Can't hunt if we aren't killing somene ;)
    if (!objectp(query_attack()))
	return;
    //  We already got our prey in our hunting sights
    if (objectp(prey) && shadowed)
	return;
    enemies = FILTER_PRESENT_LIVE(query_enemy(-1));
    //  Make sure there are no npcs in the array.
    enemies = FILTER_PLAYERS(enemies);
    if (!sizeof(enemies))
	return;
    prey = enemies[random(sizeof(enemies))];
    setuid(); seteuid(getuid());
    clone_object(HUNT_SHADOW)->follow(prey,TO);
    shadowed = 1;
#ifdef BOLG_HUNTER_LOG
    write_file(BOLG_HUNTER_LOG,ctime(time()) + " started to hunt "+
      CAP(prey->query_real_name()) +".\n");
#endif
}

//  Called from the follow shadow
void
notify_stopped_hunt()
{
    prey = 0;
    shadowed = 0;
}

string
query_hunting()
{
    return prey->query_real_name();
}

int
query_shadowed()
{
    return shadowed;
}
