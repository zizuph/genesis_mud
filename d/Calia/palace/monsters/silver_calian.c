/* 	The silver calian in the crystalline palace.

    coder(s):   Glykron

    history:     31/1/97     added reward                    Maniac 
                 29/9/95     upgraded again                  Maniac
                 15.6.95     upgraded                        Maniac
                 17.11.94    title & descr typos removed     Maniac   
                 1. 9.93    calian object added             Glykron
                 9. 2.93    header added                    Glykron
                 9. 2.93    modified                        Glykron

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
    clone_object(WEAPON("silver_sword"))->move(this);
    command("wield sword");
    clone_object(ARMOUR("silver_chainmail"))->move(this);
    command("wear armour");
    type = RANDOM_ELEMENT( ({ "cloak", "helmet", "boots", "shield", "gloves" })
        );
    clone_object(ARMOUR("silver_" + type))->move(this);
    command("wear " + type);
    MONEY_MAKE_SC(random(30))->move(this);
}

void
create_calian()
{
    if (!IS_CLONE)
        return;

    set_race_name("elf");
    set_long("@@calian_long");
    set_base_stat(SS_INT, 70);
    set_base_stat(SS_WIS, 70);
    set_base_stat(SS_DIS, 120);
    set_base_stat(SS_STR, 70);
    set_base_stat(SS_DEX, 70);
    set_base_stat(SS_CON, 70);
    set_base_stat(SS_OCCUP, 70);
    set_skill(SS_WEP_SWORD, 70);
    set_skill(SS_PARRY, 70);
    set_skill(SS_DEFENCE, 70);
    set_skill(REWARD, 1); 
    set_hp(10000);
    set_alignment(70);
    set_all_hitloc_unarmed(query_average_stat() / 4);
    set_calian_title("Silver Calian");
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_alarm(1.0, 0.0, "equip_me");
}
