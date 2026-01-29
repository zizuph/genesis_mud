/*
 * Created by:
 *   Antharanos
 * Modified by:
 *   Toby 97-09-17 Made a check if Goliath can see the player, and if it is dark in the room
 *   Finwe 04-01-01 Adds a prop to attackers to block them when attacked
 *   Arandir 04-01-25 Bounce protection to catch cheaters
 *   Arandir 04/01/28 Added a log to bounce protection
 *   Palmer  2004-Apr-19 Prevent Grothaur from yelling at wizards when they enter
 *   Arandir 04/06/24 Only the mapping with bouncers gets saved now
 *   Finwe   December 8, 2007 - Fixed typos
 * Cotillion 2021-09-27 - Add purge functionality of bounce list
 */

//inherit "/std/monster";
inherit "/d/Shire/orcmaker/team";

#include <macros.h>
#include <options.h>
#include <wa_types.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <stdproperties.h>

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/private/shire_admin.h"

inherit "/lib/unique";

inherit KILL_LOGGER;

#define ARM "/d/Shire/common/trollsh/arm/"
#define WEP "/d/Shire/common/trollsh/weapon/"


//-------------------------------------------------------------------

#define FALSE	0
#define TRUE	1

#define S_BOUNCE_LOG		"bounce_grothaur"

//-------------------------------------------------------------------

// Variables to hold the attacker information

mapping mAttackers = ([ ]);

#define S_ATTACKER_TIME		0
#define S_ATTACKER_COUNT	1
#define S_ATTACKER_BOUNCE	2

// S_BOUNCE_DELAY	How fast a return is a bounce
// S_BOUNCE_COUNT	How many fast returns needed
// S_BOUNCE_RESET	How long before resetting return counter
// S_BOUNCE_FORGIVE	How long before resetting bounce flag

#define S_BOUNCE_DELAY		20
#define S_BOUNCE_COUNT		5
#define S_BOUNCE_RESET		60*5
#define S_BOUNCE_FORGIVE	60*60*24*7

/*
 * Function name : s_save_object
 * Function name : s_restore_object
 * Description   : Functions to save and restore the object.
 *
 */

void s_save_object ()
{
  setuid (); seteuid (getuid (this_object ()));
  save_map (mAttackers, MASTER_OB (this_object ()));
}
 
void s_restore_object ()
{
  setuid (); seteuid (getuid (this_object ()));
  mAttackers = restore_map (MASTER_OB (this_object ()));

  /* Purge old entries */
  foreach (string key, mixed val: mAttackers)
  {
     if ((time() - val[S_ATTACKER_TIME]) > (S_BOUNCE_FORGIVE * 2))
     {
         m_delkey(mAttackers, key);
     }
  }
}


/*
 * Function name : s_got_attacked
 * Description   : Notes that we got attacked and watches for bouncers.
 *
 */

void s_got_attacked (object oWho)
{
  string sWho = oWho->query_real_name ();
  string sWhoCap = capitalize (sWho);
  int    iTime = time ();
  int    iDelta;

  log_file (S_BOUNCE_LOG, ctime (time ()) + " Grothaur attacked by " + sWhoCap + ".\n");

  if (member_array (sWho, m_indices (mAttackers)) >= 0)
  {
    iDelta = iTime - mAttackers [sWho][S_ATTACKER_TIME];
    if (iDelta > S_BOUNCE_FORGIVE)
    {
      mAttackers [sWho][S_ATTACKER_BOUNCE] = FALSE;
    }
    else if (iDelta > S_BOUNCE_RESET)
    {
      mAttackers [sWho][S_ATTACKER_COUNT] = 0;
    }
    else if (iDelta < S_BOUNCE_DELAY)
    {
      if (mAttackers [sWho][S_ATTACKER_COUNT] ++ > S_BOUNCE_COUNT)
      {
        mAttackers [sWho][S_ATTACKER_BOUNCE] = TRUE;
        log_file (S_BOUNCE_LOG, ctime (time ()) + " Grothaur bounced by " + sWhoCap + ".\n");
      }
    }
    mAttackers [sWho][S_ATTACKER_TIME] = iTime;
  }
  else
  {
    mAttackers += ([ sWho : ({ iTime, 0, FALSE }) ]);
  }
  
  s_save_object ();
}


/*
 * Function name : s_is_bouncer
 * Description   : Tells whether somebody has been estabilished as a bouncer.
 *
 */

int s_is_bouncer (object oWho)
{
  string sWho = oWho->query_real_name ();

  if (member_array (sWho, m_indices (mAttackers)) >= 0)
  {
    return (mAttackers [sWho][S_ATTACKER_BOUNCE]);
  }
  else return (FALSE);
}
 
//-------------------------------------------------------------------


void create_monster ()
{
  set_name("grothaur");
  add_name("_trollshaw_troll");
  add_name("_trollshaw_troll");
  set_living_name("grothaur");
  set_race_name("troll");
  set_adj("terrible");
  add_adj("menacing");
  set_long("This is a terrible menacing troll who lives beneath " +
           "the Trollshaws. Like all the others, he has thick " +
           "skin and towers over everyone. He is ugly and stupid " +
           "looking but this one is larger than most trolls, and " +
           "looks unusually strong for one of his kind.\n");
  
  set_base_stat (SS_STR, 200 + random (50));
  set_base_stat (SS_DEX, 200 + random (50));
  set_base_stat (SS_CON, 200 + random (50));
  set_base_stat (SS_INT, 200 + random (50));
  set_base_stat (SS_WIS, 170 + random (50));
  set_base_stat (SS_DIS, 150 + random (50));

  set_alignment (-700);

    set_skill(SS_WEP_SWORD,    100);
    set_skill(SS_WEP_AXE,      100);
    set_skill(SS_WEP_CLUB,	100);
    set_skill(SS_WEP_KNIFE,	100);
    set_skill(SS_WEP_POLEARM,  100);

  set_skill (SS_WEP_MISSILE,100);

  set_skill (SS_2H_COMBAT,100);
  set_skill (SS_UNARM_COMBAT,100);
  set_skill (SS_DEFENCE,90);
  set_skill (SS_PARRY,90);
  set_skill (SS_BLIND_COMBAT,100);
  set_skill (SS_AWARENESS,75);
  set_skill (SS_SPELLCRAFT,50);

  add_prop("_live_m_no_drain", 1);
  add_prop(NPC_I_NO_RUN_AWAY, 1);

  set_act_time(6);
  add_act("snarl");
  add_act("growl");
  add_act("grin demon");
  add_act(({"smirk","wipe"}));
  add_act("shave");


  set_cact_time(3);
  set_title("the Chief of the Trollshaws");
  set_aggressive(1);
  set_alarm(1.0,0.0,"arm_me");

  set_kill_log_name("grothaur");
  set_kill_log_size(30000);
  TELL_ADMIN("Grothaur was cloned " + ctime(time()));
  
  s_restore_object ();
}


void arm_me ()
{
    object arm,wep,obj;
    seteuid(getuid(TO));

    arm = clone_object("/d/Shire/common/trollsh/arm/troll_torso");
    arm -> move(TO);
    arm = clone_object("/d/Shire/common/trollsh/arm/troll_helm_steel");
    arm -> move(TO);
    arm = clone_object("/d/Shire/common/trollsh/arm/greaves_steel");
    arm -> move(TO);

    switch(random(5))
   {
        case 0 :  wep = clone_unique("/d/Shire/common/trollsh/weapon/gem_axe", MAX_UNIQUE_ITEMS, "/d/Shire/common/trollsh/weapon/nastyclub");

                  break;

        case 1 :  wep = clone_unique("/d/Shire/common/trollsh/weapon/gem_sword", MAX_UNIQUE_ITEMS, "/d/Shire/common/trollsh/weapon/nastyclub");
	
                  break;
        case 2 :  wep = clone_unique("/d/Shire/common/trollsh/weapon/gem_flail", MAX_UNIQUE_ITEMS, "/d/Shire/common/trollsh/weapon/nastyclub");
                  break;

        case 3 :  wep = clone_unique("/d/Shire/common/trollsh/weapon/gem_halberd", MAX_UNIQUE_ITEMS, "/d/Shire/common/trollsh/weapon/nastyclub");
                  break;

        case 4: wep = clone_unique("/d/Shire/common/trollsh/weapon/gem_bow", MAX_UNIQUE_ITEMS, "/d/Shire/moria/wep/longbow");
                clone_object("/d/Shire/moria/wep/quiver_black")->move(this_object());
                clone_object("/d/Shire/moria/wep/arrow_lblack")->move(this_object());
                clone_object("/d/Shire/moria/wep/arrow_lblack")->move(this_object());
                clone_object("/d/Shire/moria/wep/arrow_lblack")->move(this_object());
                clone_object("/d/Shire/moria/obj/bowstring")->move(this_object());
                command("put arrows in quiver");
                  break;
		  		  
    }

    wep -> move(TO);

    command("wield weapons");
    command("wear all");
}


void help_friend (object ob)
{
    if (!ob->query_wiz_level() && ob && !query_attack() && present(ob, environment()))
    {
        command("shout Kill that intruder!");
    }
    command("assist");
}


int special_attack (object enemy)
{
    object me;
    mixed* hitresult;
    string how;
    me = TO;
    if (random(5))
        return 0;
    hitresult = enemy->hit_me(400 + random(400), W_BLUDGEON, me, -1);
    how = " without effect";
    if (hitresult[0] > 0)
        how == "";
    if (hitresult[0] > 5)
        how = " hard";
    if (hitresult[0] > 10)
        how = " very hard";
    if (hitresult[0] > 15)
        how = " extremely hard";
    if (hitresult[0] > 20)
        how = " tremendously hard";
    if (hitresult[0] > 25)
        how = " so hard, that the sickening sound of bones cracking is heard";
    if (hitresult[0] > 30)
        how = " so incredibly hard, that broken bones and blood fly everywhere";

    enemy -> catch_msg(QCTNAME(me) + " hammers you" + how + ".\n");
    tell_watcher(QCTNAME(me) + " hammers " + QTNAME(enemy) + " hard!\n"+
        capitalize(enemy->query_pronoun()) + " is hammered"+
        how + ".\n", enemy);
    if (enemy->query_hp() <= 0)
        enemy->do_die(me);

    return 1;
}


init_living ()
{
   ::init_living();
   if (TP->query_alignment() > 100)
        set_alarm (2.0,0.0,"attack_enemy",TP);
}


attack_enemy (ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        if (s_is_bouncer (ob))
        {
          command ("say You again! Think you can mess with me?");
        }
        else
        {
	  if (!ob->query_wiz_level())
              command("say Kill that "+ ob->query_race_name()+"!");
        }
        set_alarm (1.0,0.0,"do_attack",ob);
    }
    return;
}


do_attack (object ob)
{
    int i;
    object *friends;
    if (!ob || !present(ob, E(TO))) return;
        friends = FILTER_LIVE(all_inventory(E(TO)));
    for (i=0; i<sizeof(friends); i++)
    {
        if (friends[i]->query_name()=="Troll" ||
            friends[i]->query_name()=="_shire_troll")
        {
            friends[i]->command("kill "+lower_case(ob->query_real_name()));
        }
    }
}


void attacked_by (object ob)
{
    object *arr;
    int    i;

    ::attacked_by(ob);
    TELL_ADMIN("Grothaur was attacked by " + ob->query_cap_name() + 
        " ("+ob->query_average_stat()+") at " + ctime(time()));


    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(TO,ob);
        
    s_got_attacked (ob);
}


void notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;
    if (random(3))
        set_alarm(1.0, 0.0, &help_friend(attacker));
}


public void
do_die(object killer)
{
   ::do_die(killer);
   killer->add_prop("_i_killed_trollshaw_trolls",killer->query_prop("_i_killed_trollshaw_trolls") + 1);
}
