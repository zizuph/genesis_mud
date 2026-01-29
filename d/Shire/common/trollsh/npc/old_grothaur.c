/*	Created by:	Antharanos
 *	Purpose:
 *	Modified by:	Toby, 97-09-17 (Made a check if Goliath can see the player,
 *			and if it is dark in the room.
 */

// /d/Shire/common/trollsh/tunnel/ta16

#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/private/shire_admin.h"

inherit "/std/monster";
inherit "/lib/unique";
inherit KILL_LOGGER;

#define ARM "/d/Shire/common/trollsh/arm/"
#define WEP "/d/Shire/common/trollsh/weapon/"
//#define MAX_UNIQUE_ITEMS 0


object axe;

void
create_monster()
{

    int i;
    set_name("grothaur");
    add_name("_trollshaw_troll");
    add_name("_trollshaw_troll");
    set_living_name("grothaur");
    set_race_name("troll");
    set_adj("terrible");
    add_adj("menacing");
    set_long("This is a terrible menacing troll who lives beneath " +
        "the Trollshaws. Like all the other trolls, he has thick " +
        "skin and towers over everyone. He is ugly and stupid " +
        "looking but this one is larger than most trolls, and " +
        "looks unusually strong for one of his kind.\n");
    for(i = 0; i < 3; i++)
        set_base_stat(i, 200 + random(50));
    set_base_stat(3, 200+ random(50));
    set_base_stat(4, 170+ random(50));
    set_base_stat(5, 150+ random(50));

    set_alignment(-700);
    set_skill(SS_WEP_AXE,100);
    set_skill(SS_WEP_KNIFE,100);
    set_skill(SS_2H_COMBAT,100);
    set_skill(SS_WEP_CLUB,100);
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,90);
    set_skill(SS_PARRY,90);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_AWARENESS,75);
    set_skill(SS_SPELLCRAFT,20);
    set_act_time(6);
    add_act("snarl");
    add_act("growl");
    add_act("grin demon");
    add_act(({"smirk","wipe"}));
    add_act(({""}));
    add_act("shave");
    add_act("axelick");
    set_cact_time(3);
    set_title("the Chief of the Trollshaws");
    set_aggressive(1);
    set_alarm(1.0,0.0,"arm_me");

    set_kill_log_name("grothaur");
    set_kill_log_size(30000);
    TELL_ADMIN("Grothaur has been cloned " + ctime(time()));

//   set_knight_prestige(1000);
}
void
arm_me()
{
    object arm,wep;
    seteuid(getuid(TO));

    arm = clone_object("/d/Shire/common/trollsh/arm/troll_torso");
    arm -> move(TO);
    arm = clone_object("/d/Shire/common/trollsh/arm/troll_helm_steel");
    arm -> move(TO);
    arm = clone_object("/d/Shire/common/trollsh/arm/greaves_steel");
    arm -> move(TO);

    wep = clone_unique("/d/Shire/common/trollsh/weapon/newaxe", MAX_UNIQUE_ITEMS,  "/d/Shire/common/trollsh/weapon/nastyclub");
    wep->move(this_object());
    arm = clone_object("/d/Shire/common/trollsh/weapon/trollaxe");
    arm -> move(TO);

    command("wield weapons");
    command("wear all");

}

void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        command("shout Kill that intruder!");
    }
    command("assist");
}

int
special_attack(object enemy)
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

//   me -> catch_msg("You hammer your opponent!\n"+
//      capitalize(enemy->query_pronoun())+" is hammered hard"+
//      how + ".\n");

    enemy -> catch_msg(QCTNAME(me) + " hammers you" + how + ".\n");
    tell_watcher(QCTNAME(me) + " hammers " + QTNAME(enemy) + " hard!\n"+
        capitalize(enemy->query_pronoun()) + " is hammered"+
        how + ".\n", enemy);
    if (enemy->query_hp() <= 0)
        enemy->do_die(me);
//    we check if we still have the axe wielded
//   if (!axe->query_wielded())
//      TO->command("wield dagger");
    return 1;
}

init_living()
{
   ::init_living();
   if (TP->query_alignment() > 100 )
        set_alarm(2.0,0.0,"attack_enemy",TP);
   else
        set_alarm(2.0,0.0,"greet_friend",TP);
}

attack_enemy(ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        command("say Kill that "+ ob->query_race_name()+"!");
        set_alarm(1.0,0.0,"do_attack",ob);
    }
    return;
}

do_attack(object ob)
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

void
attacked_by(object ob)
{
    object *arr;
    int    i;

    ::attacked_by(ob);
    TELL_ADMIN("Grothaur was attacked by " + ob->query_cap_name() + 
        " ("+ob->query_average_stat()+") at " + ctime(time()));


    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(TO,ob);
}

void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;
    if (random(3))
        set_alarm(1.0, 0.0, &help_friend(attacker));
}
/*
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
    	command("kill "+ lower_case(ob->query_real_name()));
    	switch(random(3))
    	{
    	  case 0:
    	      command("emote snarls and attacks with inhuman strength.");
    	      break;
    	  case 1:
    	      command("snarl: You will taste good in a pot!");
    	      break;
    	  case 2:
    	      command("snarl: You should have never attacked us!");
    	      break;
    	}

	command("assist");
    }
}
*/
public void
do_die(object killer)
{
   killer->add_prop("_i_killed_trollshaw_trolls",killer->query_prop("_i_killed_trollshaw_trolls") + 1);

     ::do_die(killer);

}
