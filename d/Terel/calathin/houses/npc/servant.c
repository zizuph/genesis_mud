/*
 * house4 servant.c 
 * Modification of: Std Calathin Citizen
 *
 * Coded by Shinto 10-18-98
 * Revised by Tomas 11-17-1999
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

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

void
create_monster()
{
    power = 30+random(70);

    set_name("servant");
    set_pname("servants");
    set_gender(random(1));
    set_race_name(races());
    set_adj(adj());
    set_adj(adj2());
    set_long("A house servant.\n");
    default_config_npc(power);
    set_alignment(random(500));
    set_skill(SS_WEP_SWORD, power);
    set_skill(SS_WEP_AXE, power);
    set_skill(SS_WEP_KNIFE, power);
    set_skill(SS_DEFENCE, power);
    set_skill(SS_PARRY, power);
    set_skill(SS_UNARM_COMBAT, 0);
    set_skill(SS_AWARENESS, power/2);
    set_skill(SS_2H_COMBAT, power);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(OBJ_M_HAS_MONEY, random(100));
    set_act_time(1);
    add_act("close door");
    add_act("emote dusts a piece of furniture.");
    add_act("emote glances at you cautiously.");
    
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

