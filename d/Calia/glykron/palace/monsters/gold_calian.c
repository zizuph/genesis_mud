/* 	The gold calian in the crystalline palace.

    coder(s):   Glykron

    history:     31/1/97     added reward :)                 Maniac 
                 29/9/95     upgraded again                  Maniac
                 15.6.95     upgraded                        Maniac
                17.11.94    title typo removed              Maniac        
                 1. 9.93    calian object added             Glykron
                25. 2.93    modified                        Glykron
                 9. 2.93    header added                    Glykron

*/

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "defs.h"
#include RANDOM_HEADER
#include COUNCIL_HEADER
#pragma save_binary

inherit CALIAN;

void
equip_me()
{
    object this;
    string type;

    this = THIS;
    clone_object(WEAPON("gold_halberd"))->move(this);
    command("wield halberd");
    clone_object(ARMOUR("gold_platemail"))->move(this);
    command("wear armour");
    type = RANDOM_ELEMENT( ({ "cloak", "helmet", "boots", "shield", "gauntlets"
        }) );
    clone_object(ARMOUR("gold_" + type))->move(this);
    command("wear " + type);
    MONEY_MAKE_GC(3)->move(this);
}

void
create_calian()
{
    if (!IS_CLONE)
        return;

    set_race_name("human");
    set_long("@@calian_long");
    set_base_stat(SS_INT, 85);
    set_base_stat(SS_WIS, 85);
    set_base_stat(SS_DIS, 125);
    set_base_stat(SS_STR, 85);
    set_base_stat(SS_DEX, 85);
    set_base_stat(SS_CON, 85);
    set_base_stat(SS_OCCUP, 85);
    set_skill(SS_WEP_POLEARM, 85);
    set_skill(SS_PARRY, 85);
    set_skill(SS_DEFENCE, 85);
    set_skill(REWARD, 2); 
    set_hp(10000);
    set_alignment(150);
    set_all_hitloc_unarmed(query_average_stat() / 4);
    set_whimpy(0);
    set_calian_title("Gold Calian");
    set_alarm(1.0, 0.0, "equip_me");
}

