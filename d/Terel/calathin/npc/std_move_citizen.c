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
inherit "/std/act/action";
inherit "/std/act/seqaction";
#include "/d/Terel/clubs/explorer/include/explorer.h"

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
string boots();
string breeches();
string tunics();
void dress_me();

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
    dress_me();
    trig_new("%w 'arrives' %s", "react_enter");

}

void
dress_me()
{
    seteuid(getuid(this_object()));     

    clone_object(ARM_DIR + "hat")->move(TO);
    clone_object(ARM_DIR + boots())->move(TO);
    clone_object(ARM_DIR + breeches())->move(TO);
    clone_object(ARM_DIR + tunics())->move(TO);      
    command("wear all");
}

string boots()
{
    string *boot_list;
    boot_list = ({"b_boots","bro_boots","gr_boots","t_boots"});
    return boot_list[random(sizeof(boot_list))];
}

string breeches()
{
    string *breeches_list;
    breeches_list = ({"bl_breeches","g_breeches","gr_breeches","t_breeches"});
    return breeches_list[random(sizeof(breeches_list))];
}

string tunics()
{
    string *tunics_list;
    tunics_list = ({"b_tunic","g_tunic","t_tunic"});
    return tunics_list[random(sizeof(tunics_list))];
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
                           enemies[i]->query_prop(KILLS_CAL) + 1);
    }
    if(killer->query_prop(KILLS_CAL) > 6)
    {
        object kill_logger = find_object(CALATHIN_DIR+"obj/kill_logger");
        kill_logger->add_killer(killer->query_name());
    }
    killer->add_prop(KILLS_CAL,
                       killer->query_prop(KILLS_CAL) + 1);
    ::do_die(killer);
}


