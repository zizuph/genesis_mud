/*
 *
 * Std Calathin Citizen
 *
 * Coded by Shinto 10-18-98
 *
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
inherit "/std/act/domove";

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

#define HUNTING_TREVIN "_i_hunting_trevin"


public string
reply_assassin()
{
    if(TP->query_prop(HUNTING_TREVIN))
    {
        command("say Ahh, the dark ominous fellow.");
        command("say He headed south with quite a determined step.");
        return "";
    }
    return "";
}


void
create_monster()
{
    power = 30+random(70);

    set_name("citizen");
    set_pname("citizens");
    set_gender(random(1));
    set_race_name(races());
    set_adj(adj());
    set_adj(adj2());
    set_long("A citizen of the town of Calathin walking through the town.\n");
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
    set_restrain_path(CALATHIN_DIR);
    set_random_move(30);
    add_ask("tall wiry male human", reply_assassin, 1);

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
