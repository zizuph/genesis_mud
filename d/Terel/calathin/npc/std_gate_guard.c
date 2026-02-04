/*
 *
 * Std Calathin Guard
 *
 * Coded by Shinto 10-18-98
 *
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "guard.h"
#define ARM_DIR  CALATHIN_DIR + "armour/"
#define WEP_DIR  CALATHIN_DIR + "weapon/"
#define KILL_LOGGER CALATHIN_DIR + "obj/kill_logger"
#define OIL CALATHIN_DIR + "obj/burning_oil"
#define OIL_NUM "_oil_num"




int power;
string adj();
string adj2();
string races();
void dress_me();
void reset_oil();


void
create_monster()
{
    power = 90+random(70);

    set_name("guard");
    add_name("cal_guard");
    add_name("_cal_gate_guard");
    set_pname("guards");
    set_gender(MALE);
    set_race_name(races());
    set_adj(adj());
    set_adj(adj2());
    set_long("A guard of the town of Calathin. He looks like an able "+
                  "warrior.\n");
    default_config_npc(power);
    set_alignment(random(500));
    set_skill(SS_WEP_SWORD, power);
    set_skill(SS_WEP_AXE, power);
    set_skill(SS_DEFENCE, power);
    set_skill(SS_PARRY, power);
    set_skill(SS_UNARM_COMBAT, 0);
    set_skill(SS_AWARENESS, power/2);
    set_skill(SS_2H_COMBAT, power);
    set_aggressive("@@enemy_check");
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(OBJ_M_HAS_MONEY, random(100));
    dress_me();
 
    setuid();
    seteuid(getuid());
    GUARD_MANAGER->register_guard(this_object());


}

void
dress_me()
{
    seteuid(getuid(this_object()));     

    clone_object(ARM_DIR + "stud_armour")->move(TO);
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

int
enemy_check()
{
    
    
    object kill_logger = find_object(KILL_LOGGER);
    if(kill_logger->query_killer(TP->query_name()))
    {
       TO->command("shout Leave here Enemy of Calathin!");
       return 1;
    }
    return 0;

    {
    setuid();
    seteuid(getuid());
    GUARD_MANAGER->register_guard(this_object());
    }

}

void
reset_oil()
{
    ETO->remove_prop(OIL_NUM);
    return;
}


int
special_attack(object enemy)
{


    object *all, oil;
    int i;
    if(ETO->query_prop(OIL_NUM) > 1)
    {
        set_alarm(1800.0, -1.0, "reset_oil");
        return 0;
    }

    all = query_my_enemies();

    if(random(9) < 1) 
    {

        write(TO->short()+ " raises his hand, signaling the guards above.\n");
        say(TO->short() + " raises his hand signaling the guards above.\n");
        TO->command("shout Now!");
        
            
        write("The guards leap back away from you against the gate.\n");
        say("The guards leap back away from their attackers.\n");
            
        write("The guards above tilt a large black cauldron of hot "+
                  "burning oil.\n");
        say("The guards above tilt a large black cauldron of hot "+
              "burning oil.\n");
            
        write("The oil pours down from the top of the gates.\n");
        say("The oil pours down from the top of the gates.\n");

        ETO->add_prop(OIL_NUM, ETO->query_prop(OIL_NUM) + 1);

        for (i=0; i<sizeof(all); i++) 
        {
            oil=clone_object(OIL);
            oil->move(all[i]);

        }
     return 1;
    }

    return 0;
}

#define KILLS_CAL "_kills_cal"


void
do_die(object killer)
{
    int i;
    object *enemies;

    if (query_hp() > 0) return;
    enemies = query_my_enemies();
    for (i=0; i<sizeof(enemies); i++)
    {
        if(enemies[i]->query_prop(KILLS_CAL) > 6)
        {
            object kill_logger = find_object(CALATHIN_DIR+"obj/kill_logger");
            kill_logger->add_killer(enemies[i]->query_name());
        }
        enemies[i]->add_prop(KILLS_CAL,
                           enemies[i]->query_prop(KILLS_CAL) + 2);
    }
    if(killer->query_prop(KILLS_CAL) > 6)
    {
        object kill_logger = find_object(CALATHIN_DIR+"obj/kill_logger");
        kill_logger->add_killer(killer->query_name());
    }
    killer->add_prop(KILLS_CAL,
                       killer->query_prop(KILLS_CAL) + 2);
    ::do_die(killer);
}
