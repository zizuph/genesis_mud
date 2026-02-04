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
void dress_me();

void
create_monster()
{
    power = 30+random(70);

    set_name("guard");
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
    seq_new("do_first");
    seq_addfirst("do_first", "@@dress_me");
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(OBJ_M_HAS_MONEY, random(100));
    set_restrain_path(CALATHIN_DIR);
    set_random_move(30);
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
