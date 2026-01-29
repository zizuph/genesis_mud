
/*
 * house4_guard.c
 * modified Std Calathin Guard
 *
 * Coded by Shinto 10-18-98
 * stolen by Garion 11-17-1999
 */

#pragma strict_types

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;


#include <options.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#define ARM_DIR  CALATHIN_DIR + "armour/"
#define WEP_DIR  CALATHIN_DIR + "weapon/"




int power;
string adj();
string adj2();
string races();
mixed bemean();
void dress_me();


/* sets unarmed combat off, giving more sword attacks! */
int
query_option(int opt)
{
  return (opt == OPT_UNARMED_OFF);
}


void
create_monster()
{
    power = 60+random(60);

    set_name("guard");
    add_name("house_guard");
    set_pname("guards");
    set_gender(MALE);
    set_race_name(races());
    set_adj(adj());
    set_adj(adj2());
    set_long("A private mercenary hired by the lord of the house.\n");
    default_config_npc(power);
    set_skill(SS_WEP_SWORD, power);
    set_skill(SS_WEP_AXE, power);
    set_skill(SS_DEFENCE, power);
    set_skill(SS_PARRY, power);
    set_skill(SS_UNARM_COMBAT, 0);
    set_skill(SS_AWARENESS, power/2);
    set_skill(SS_2H_COMBAT, power);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(OBJ_M_HAS_MONEY, random(100));
    dress_me();
    set_aggressive("@@bemean");
    set_act_time(5 + random(40)); 
    add_act("close door");
    add_act("smirk");
    add_act("say I'm glad I work for Arlenn. I wouldn't want " +
       "to be mixed up with those Calathin idiots.");
    add_act("fidget");
    add_act("emote mumbles something about being hungry.");
    add_act("say I hope to return to the mountains soon. " +
       "City life bores me.\n");
    add_act("say The real money is in killing goblins up on the " +
       "mountain pass. Those RICH Dwarven miners up there " +
       "sure need our help. I hope our lord calls for us soon.\n");

    BRAVE;
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1);

}

void
dress_me()
{
    seteuid(getuid(this_object()));     

    clone_object(ARM_DIR + "stud_armour")->move(TO);
    clone_object(CALATHIN_DIR + "houses/armour/cloak")->move(TO);
    clone_object(ARM_DIR + "stud_greaves")->move(TO);
    clone_object(ARM_DIR + "stud_bracers")->move(TO);
    clone_object(ARM_DIR + "stud_cap")->move(TO);      
    switch(random(3)) {
        case 0 :  clone_object(WEP_DIR + "longsword")->move(TO);
                      clone_object(WEP_DIR + "shortsword")->move(TO);   
                      break;
        case 1 :  clone_object(WEP_DIR + "longsword")->move(TO);
                      break;
        case 2 :  clone_object(WEP_DIR + "battleaxe")->move(TO);
                      break;
    }
    command("wield weapons");
    command("wear armours");
}

string races()
{
    string *races;
    races = ({"elf","half-elf","human"});
    return races[random(sizeof(races))];
}

string adj()
{
    string *adj;
    adj = ({"black-haired","blond-haired","muscular", "swarthy",
               "thick-armed","long-haired","short-haired", "silver-haired",
               "red-haired", "brown-haired", "grey-haired"});
    return adj[random(sizeof(adj))];
}

string adj2()
{
    string *adj2;
    adj2 = ({"blue-eyed", "hazel-eyed", "black-eyed", "brown-eyed",
            "green-eyed","olive-skinned","brown-skinned",
            "tanned","dark-skinned","light-skinned","grey-eyed"});
    return adj2[random(sizeof(adj2))];
}


mixed
bemean()
{
    if(TP->query_race_name() == "goblin" || TP->query_race_name() == "hobgoblin")
    { 
    set_alarm(itof(random(1) + 1), 0.0, "command",
                  "emote shouts Goblins! Defend the house!!");
     
    return 1; 
    }
    return 0;
}

void
attacked_by(object ob)
{
   object *arr;
   int i;
   
   ::attacked_by(ob);
   
   arr = (object *)query_team_others();
   for (i = 0; i < sizeof(arr); i++)
       arr[i]->notify_ob_attacked_me(this_object(), ob);
}



void
notify_ob_attacked_me(object friend, object attacker)
   {
   if (query_attack())
      return;
   
   set_alarmv(1.0, -1.0, "help_friend", ({attacker}));
}

/*
* Function name: help_friend
* Description:   Help my friends by attacking their attacker
* Arguments:     attacker - The person who attacked my friend
*/
void
help_friend(object ob)
{
   
    if (ob && !query_attack() && present(ob, environment())) {
        command("kill " + lower_case(ob->query_real_name()));
        command("kill " + lower_case(ob->query_real_name()));      
    }
}    



    
