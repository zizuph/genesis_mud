/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * colonel.c Trofast 10-25-1998
 *
 * stolen from:
 * a captain of the legion 921104 redhawk
 * Modified by Sorgum 941029
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <wa_types.h>
#include <formulas.h>
#include <money.h>
#include <ss_types.h>
#include <options.h>

// global variable for unarmed option
int unarmed=0;



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
    /*    set_option(OPT_UNARM_COMBAT,1); */

    set_stats(({160, 175, 136, 90, 90, 90}));
    SET_MAX_HP;
    
    set_skill(SS_DEFENCE,      90);
    set_skill(SS_PARRY,        90);
    set_skill(SS_WEP_SWORD,    100);
    set_skill(SS_WEP_KNIFE,    100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_2H_COMBAT,    90);
    set_skill(SS_BLIND_COMBAT, 60);
    set_skill(SS_AWARENESS,    70);
    /*    set_all_attack_unarmed(40,40); */
    
    add_prop(LIVE_I_QUICKNESS, 150);
    add_prop(OBJ_M_HAS_MONEY, ({0,50,5,0}) );
    add_prop(NPC_I_NO_FEAR,1);

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

    if( sizeof(TO->query_weapon(-1)) )
      unarmed=1;
    else
      unarmed=0;


if ( (random(10))<2 )
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

      if (unarmed)
      {
	hitresult = enemy->hit_me(700, W_IMPALE, TO, hitloc);
	enemy->catch_msg("The legion colonel studies your defenses "+
			 "carefully.  Suddenly he stabs you in the "+
			 where+"!\n");
	tell_watcher("The legion colonel stabs his longsword into "+
		     QTNAME(enemy)+"'s weakest spot.\n",enemy);
      }
    else
      {
	hitresult = enemy->hit_me(700, W_BLUDGEON, TO, hitloc);
	enemy->catch_msg("The legion colonel studies your defenses "+
			 "carefully.  Suddenly he bashes you in the "+
			 where+" with his gauntleted fist!\n");
	tell_watcher("The legion colonel bashes his gauntleted fist into "
		     +QTNAME(enemy)+"'s weakest spot.\n",enemy);
      }
  return 1;
  }
return 0;
}

int query_option(int opt)
{

if (opt==OPT_UNARMED_OFF)
  return unarmed;

}
