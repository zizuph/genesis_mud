/*
 *
 * Std Calathin Citizen
 *
 * Coded by Shinto 10-18-98
 * updated for use with the Calathin farms  -- Tomas 11/21/1999
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#define ARM_DIR  CALATHIN_DIR + "farms/armour/"
#define WEP_DIR  CALATHIN_DIR + "weapon/"


int power;
string adj();
string adj2();
string races();
void dress_me();

void
create_monster()
{
    power = 30+random(20);

    set_name("farmer");
    set_pname("farmers");
    set_gender(random(1));
    set_race_name(races());
    set_adj(adj());
    set_adj(adj2());
    set_long("A Calathin farmer.\n");
    default_config_npc(power);
    set_alignment(random(500));
    set_skill(SS_WEP_SWORD, power);
    set_skill(SS_WEP_AXE, power);
    set_skill(SS_WEP_KNIFE, power);
    set_skill(SS_DEFENCE, power);
    set_skill(SS_PARRY, power);
    set_skill(SS_UNARM_COMBAT, power);
    set_skill(SS_AWARENESS, power/2);
    set_skill(SS_2H_COMBAT, power);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(OBJ_M_HAS_MONEY, random(100));
    dress_me();
    set_act_time(10);
    add_act("say I hope spring comes early this year.");
    add_act("frown .");
    add_act("shout Make sure dem hogs get their viddles!");
    add_act("emote mutters something about the weather.");
    add_act("say I hear tell dem Gobbos are causing a might " +
       "trouble up north.");
}

void
dress_me()
{
    seteuid(getuid(this_object()));     

    clone_object(ARM_DIR + "gr_breeches")->move(TO);
    clone_object(ARM_DIR + "g_tunic")->move(TO);
    clone_object(ARM_DIR + "gr_boots")->move(TO);
    clone_object(ARM_DIR + "hat")->move(TO);      
    clone_object(ARM_DIR + "belt")->move(TO);      
    clone_object(ARM_DIR + "workgloves")->move(TO);  

    command("wear all");
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
