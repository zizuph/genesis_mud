/*
 *
 * Based off Std Calathin Citizen
 * Updated for use as the traveller -- Tomas 11/21/1999
 *
 * Lilith Dec 2021: moving from Sorgums dir to the common/moor/* dir
 *                  +general updates to current code standards
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
    add_act("frown");
    add_act("say I hope to get through the pass unhindered.");
    add_act("say welcome stranger. You come for a drink of water too?");
    add_act("drink water from stream");

    add_ask(({"quest","task"}), reply_quest, 1);
	 
    equip(({ARM_DIR + "refugee_tunic", 
        ARM_DIR + "refugee_pants", 	
        ARM_DIR + "refugee_cloak",
        ARM_DIR + "refugee_boots",
    	ARM_DIR + "refugee_hat"}));		

}




void
dress_me()
{
//    Looks like this was taken out in 2001.
//    clone_unique(TEREL_DIR + "weapon/ddagger",5,TEREL_DIR + "weapon/short")->move(TO);

    switch(random(6)) 
    {
        case 0 : add_weapon(WEP_DIR + "refugee_axe");
                 break;
        case 1 : add_weapon(WEP_DIR + "refugee_knife");
                 break;
        case 2 : add_weapon(WEP_DIR + "refugee_pickaxe");
                 break;
        case 3 : add_weapon(WEP_DIR + "refugee_hoe");
                 break;
        case 4 : add_weapon(WEP_DIR + "refugee_shovel");
                 break;
        case 5 : add_weapon(WEP_DIR + "refugee_polearm");
                 break;
    }
}


string races()
{
    string *races;
    races = ({"elf","half-elf","human"});
    return races[random(sizeof(races))];
}
