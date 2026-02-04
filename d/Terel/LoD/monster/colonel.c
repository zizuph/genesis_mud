/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * colonel.c Trofast 10-25-1998
 *
 * stolen from:
 * a captain of the legion 921104 redhawk
 * Modified by Sorgum 941029
 
 After a bug report I changed his special description  -
   if he can't see his enemy he's not studing his defence,
  but he's still lucky enough to hit the right spot;]
      /Udana
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <wa_types.h>
#include <formulas.h>
#include <money.h>
#include <ss_types.h>
#define KILL_LOG "/d/Terel/log/colonel_kills"
#define KILLS_LOG "/d/Terel/log/cap_kills"
#define MAX_HELP        4

void call_for_help();

int no_help=0;

/*
 * Function name: query_object_list
 * Description:   return list of equipment
 */
public string*
query_object_list()
{
  return ({
    LOD_DIR + "armour/suit_armour",
    LOD_DIR + "weapon/colonel_sword"
      });
}


/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{

    ::create_monster();
    set_name ("colonel");
    set_short("legion colonel");
    set_long("The colonel of the legion army, they who have sworn not to " +
	     "rest until they have spread darkness all over the " +
	     "world.\n");
    set_adj("legion");
    set_race_name("elf");
    set_gender(MALE);
    set_alignment(-400);

    set_stats(({160, 175, 156, 140, 140, 140}));
    SET_MAX_HP;
    set_exp_factor(150);
    
    set_skill(SS_DEFENCE,      90);
    set_skill(SS_PARRY,        90);
    set_skill(SS_WEP_SWORD,    100);
    set_skill(SS_WEP_KNIFE,    100);
    set_skill(SS_2H_COMBAT,    90);
    set_skill(SS_BLIND_COMBAT, 60);
    set_skill(SS_AWARENESS,    70);
    set_all_attack_unarmed(0,0);
    
    add_prop(LIVE_I_QUICKNESS, 50);
    add_prop(OBJ_M_HAS_MONEY, ({0,50,5,0}) );
    add_prop(NPC_I_NO_FEAR,1);
    /*    AGGRESSIVE; */

    set_chat_time(15);
    set_cchat_time(21);
    set_act_time(18);
    add_act("frown worriedly");
    add_act("pace");
    add_act("grumble deeply");
    add_act("emote casts an appraising glance at your armour.");
    add_chat("Get out of my quarters NOW.");
    add_chat("It's been a long time since I had to kill anyone personally.");
    add_chat("Are you a spy from Calathin?");
    add_chat("I've not been defeated in single combat.");

}

public int
special_attack(object enemy)
{
    mixed *hitresult;
    int hitloc, aclass=100, temp=99;
    string where;


if ( (random(10))<3 )
  {
    hitloc=A_BODY;
    where="body";

    //Find their weakest spot!
    temp=enemy->query_armour(A_BODY)->query_ac();

    if (aclass > temp)
      {
	aclass=temp;
	hitloc=A_BODY;
	where="body";
      }

    temp=enemy->query_armour(A_HEAD)->query_ac();
   
    if (aclass > temp)
      {
	aclass=temp;
	hitloc=A_HEAD;
	where="head";
      }

    temp=enemy->query_armour(A_LEGS)->query_ac();

    if (aclass > temp)
      {
	aclass=temp;
	hitloc=A_LEGS;
	where="legs";
      }
    temp=enemy->query_armour(A_R_ARM)->query_ac();

    if (aclass > temp)
      {
	aclass=temp;
	hitloc=A_R_ARM;
	where="right arm";
      }
    temp=enemy->query_armour(A_L_ARM)->query_ac();

    if (aclass > temp)
      {
	aclass=temp;
	hitloc=A_L_ARM;
	where="left arm";
      }

    //query_weapon needs -1 as argument to list all locations,
    //Since its an array need to use sizeof
    if( sizeof(TO->query_weapon(-1)) )
      {
	set_all_attack_unarmed(0,0);
	hitresult = enemy->hit_me(700, W_IMPALE, TO, hitloc);
        if(CAN_SEE_IN_ROOM(TO))
        {
          enemy->catch_msg("The legion colonel studies your defenses "+
			 "carefully.  Suddenly he stabs you in the "+
			 where+"!\n");
        }
        else
        {
          enemy->catch_msg("The legion colonel instinctively finds "+
            "a weakest spot in your defences and stabs you in the " + where + "!\n");
        }
	tell_watcher("The legion colonel stabs his longsword into "+
		     QTNAME(enemy)+"'s weakest spot.\n",enemy);
      }
    else
      {
	set_all_attack_unarmed(40,40);
	hitresult = enemy->hit_me(700, W_BLUDGEON, TO, hitloc);
        if(CAN_SEE_IN_ROOM(TO))
        {
          enemy->catch_msg("The legion colonel studies your defenses "+
			 "carefully.  Suddenly he bashes you in the "+
			 where+" with his gauntleted fist!\n");
        }
        else
        {
          enemy->catch_msg("The legion colonel instinctively finds "+
            "a weakest spot in your defences and bashes you in the " 
          + where + "with his gauntleted!\n");
        }
          
	tell_watcher("The legion colonel bashes his gauntleted fist into "
		     +QTNAME(enemy)+"'s weakest spot.\n",enemy);
      }
	call_for_help();
  return 1;
  }
return 0;
}

void
do_die(object killer)
{
    int i;
    string str;
    object *enemies;
    
    if (query_hp() > 0) return;
    enemies = query_my_enemies();
    str = killer->query_name() + "[" + killer->query_average_stat() + "]";
    for (i=0; i<sizeof(enemies); i++) {
       if (enemies[i] != killer)
           str += ", " + enemies[i]->query_name() +
           "[" + enemies[i]->query_average_stat() + "]";
      }
    write_file(KILL_LOG, str + " (" + ctime(time()) + ")\n");
    
    ::do_die(killer);
}


void
call_for_help()
{
    object *enemies, knight;

    enemies = query_my_enemies();
    if (sizeof(enemies) == 0) {
        add_panic(-query_panic());
        return;
    }

    if (query_hp() > query_max_hp()/(2 + 2*no_help)) return;

    if (no_help >= MAX_HELP) {
        command("shout Captains! I need help! Where are you?");
        if (query_panic() < 100) command("panic");
        no_help++;
        return;
    }

    if (no_help == 0) {
        command("shout Captain! Believe it or not, but I need " +
                "help at once!");
    } else {
        command("shout Captain! Come to my aid! " +
                "These bastards are tough!");
    }
    FIX_EUID;
    knight = clone_object(LOD_DIR + "monster/captain");
    knight->move_living("M", ETO);
    tell_room(ETO, QCTNAME(knight) + " arrives.\n");
    knight->equip_actions();
    knight->command("gasp");
    knight->help_the_boss(TO);
    knight->attack_someone();
    no_help++;
}

int
notify_you_killed_me(object player)
{
    command("get all from corpse");
    if(player->query_npc()) return 1;
    seteuid(getuid(this_object()));
    write_file(KILLS_LOG,player->query_name() +
          " ("+player->query_average_stat()+
          ") by "+this_object()->query_name()+" on " +
          ctime(time())+" ("+file_name(environment(this_object()))+").\n");
    return 1;
}

