/* 	The bronze knight in the crystalline palace

    coder(s):   Glykron
    history:
                29/9/95     upgraded again                  Maniac
                15.6.95     upgraded                        Maniac
                17.11.94    title & descr typos removed     Maniac
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
#pragma save_binary

inherit CALIAN;

void
equip_me()
{
    object this;
    string type;

    this = THIS;
    clone_object(WEAPON("bronze_axe"))->move(this);
    command("wield axe");
    clone_object(ARMOUR("bronze_chainmail"))->move(this);
    command("wear armour");
    type = RANDOM_ELEMENT( ({ "cloak", "helmet", "boots", "gauntlets" }) );
    clone_object(ARMOUR("bronze_" + type))->move(this);
    command("wear " + type);
    MONEY_MAKE_CC(random(400))->move(this);
}

void
create_calian()
{
    if (!IS_CLONE)
	return;

    set_race_name("dwarf");
    set_long("@@calian_long");
    set_base_stat(SS_INT, 65);
    set_base_stat(SS_WIS, 65);
    set_base_stat(SS_DIS, 115);
    set_base_stat(SS_STR, 65);
    set_base_stat(SS_DEX, 65);
    set_base_stat(SS_CON, 65);
    set_base_stat(SS_OCCUP, 65);
    set_skill(SS_WEP_AXE, 65);
    set_skill(SS_PARRY, 65);
    set_skill(SS_DEFENCE, 65);
    set_hp(10000);
    set_alignment(65);
    set_all_hitloc_unarmed(query_average_stat() / 4);
    set_calian_title("Bronze Calian");
    set_alarm(1.0, 0.0, "equip_me");
}