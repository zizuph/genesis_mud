/*
 *
 * Std Calathin Citizen
 *
 * Coded by Shinto 10-18-98
 * updated for use as the traveller   -- Tomas 11/21/1999
 */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#define ARM_DIR  MOUNTAIN_DIR + "elderwood/armour/"
#define WEP_DIR  MOUNTAIN_DIR + "elderwood/weapon/"


int power;
string races();
void dress_me();

public string
reply_quest()
{
   command("say Huh? OH! you want a task!");
   command("think");
   command("say Nothing comes to mind. Try me later perhaps?");
   return "";
}

void
create_monster()
{
    power = 30+random(20);

    set_name("traveller");
    set_pname("travellers");
    set_gender(random(1));
    set_race_name(races());
    set_adj("scruffy");
    set_adj("long-haired");
    set_long("A simple traveller.\n");
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
    set_fatigue(0);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(OBJ_M_HAS_MONEY, random(100));
    dress_me();
    set_act_time(10);
    add_act("splash water on face");
    add_act("frown\n");
    add_act("say I hope to get through the pass unhindered.\n");
    add_act("say welcome stranger. You come for a drink of water too?\n");
    add_act("drink water from stream");

    add_ask(({"quest","task"}), reply_quest, 1);
   

}




void
dress_me()
{
    seteuid(getuid(this_object()));     

//    clone_unique(TEREL_DIR + "weapon/ddagger",5,TEREL_DIR + "weapon/short")->move(TO);

    switch(random(6)) 
    {
        case 0 :  clone_object(ARM_DIR + "refugee_tunic")->move(TO);
                  clone_object(ARM_DIR + "refugee_pants")->move(TO);
                  clone_object(ARM_DIR + "refugee_cloak")->move(TO);
                  clone_object(ARM_DIR + "refugee_boots")->move(TO);
                  clone_object(ARM_DIR + "refugee_hat")->move(TO);
                  clone_object(WEP_DIR + "refugee_axe")->move(TO);
                      break;
        case 1 :  clone_object(ARM_DIR + "refugee_tunic")->move(TO);
                  clone_object(ARM_DIR + "refugee_pants")->move(TO);
                  clone_object(ARM_DIR + "refugee_cloak")->move(TO);
                  clone_object(ARM_DIR + "refugee_boots")->move(TO);
                  clone_object(ARM_DIR + "refugee_hat")->move(TO);
                  clone_object(WEP_DIR + "refugee_knife")->move(TO);
 //                 clone_object(CALATHIN_DIR + "obj/backpack")->move(TO);
                      break;
        case 2 :  clone_object(ARM_DIR + "refugee_tunic")->move(TO);
                  clone_object(ARM_DIR + "refugee_pants")->move(TO);
                  clone_object(ARM_DIR + "refugee_cloak")->move(TO);
                  clone_object(ARM_DIR + "refugee_boots")->move(TO);
                  clone_object(ARM_DIR + "refugee_hat")->move(TO);
 //                 clone_object(CALATHIN_DIR + "obj/backpack")->move(TO);
                  clone_object(WEP_DIR + "refugee_pickaxe")->move(TO);
                      break;
        case 3 :  clone_object(ARM_DIR + "refugee_tunic")->move(TO);
                  clone_object(ARM_DIR + "refugee_pants")->move(TO);
                  clone_object(ARM_DIR + "refugee_cloak")->move(TO);
                  clone_object(ARM_DIR + "refugee_boots")->move(TO);
                  clone_object(ARM_DIR + "refugee_hat")->move(TO);
                  clone_object(WEP_DIR + "refugee_hoe")->move(TO);
                      break;
        case 4 :  clone_object(ARM_DIR + "refugee_tunic")->move(TO);
                  clone_object(ARM_DIR + "refugee_pants")->move(TO);
                  clone_object(ARM_DIR + "refugee_cloak")->move(TO);
                  clone_object(ARM_DIR + "refugee_boots")->move(TO);
                  clone_object(ARM_DIR + "refugee_hat")->move(TO);
                  clone_object(WEP_DIR + "refugee_shovel")->move(TO);
                      break;
        case 5 :  clone_object(ARM_DIR + "refugee_tunic")->move(TO);
                  clone_object(ARM_DIR + "refugee_pants")->move(TO);
                  clone_object(ARM_DIR + "refugee_cloak")->move(TO);
                  clone_object(ARM_DIR + "refugee_boots")->move(TO);
                  clone_object(ARM_DIR + "refugee_hat")->move(TO);
                  clone_object(WEP_DIR + "refugee_polearm")->move(TO);
 //                 clone_object(CALATHIN_DIR + "obj/backpack")->move(TO);
                      break;
    }

    command("wield weapons");
    command("wear all");
}



string races()
{
    string *races;
    races = ({"elf","half-elf","human"});
    return races[random(sizeof(races))];
}
