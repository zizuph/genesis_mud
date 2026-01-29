/* 	A young kroug in the crystalline palace.

    coder(s):   Glykron

    history:    25. 2.92    recovery added                  Glykron
                25. 2.92    header added                    Glykron

*/

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "defs.h"
#include RANDOM_HEADER
#pragma save_binary

inherit KROUG;

void
equip_me()
{
    object this;
    string type;

    this = THIS;
    seteuid(getuid(this));
    clone_object(WEAPON("iron_sword"))->move(this);
    command("wield sword");
    clone_object(ARMOUR("iron_chainmail"))->move(this);
    command("wear armour");

    type = RANDOM_ELEMENT( ({ "boots", "helmet", "shield" }) );
    clone_object(ARMOUR("iron_" + type))->move(this);
    command("wear " + type);

    MONEY_MAKE_CC(20)->move(this_object());
}

void
create_kroug()
{
    if (!IS_CLONE)
	return;

    ::create_kroug();
    set_long("He is a young charred black-skinned being.\n");
    set_base_stat(SS_INT, 20);
    set_base_stat(SS_WIS, 20);
    set_base_stat(SS_DIS, 20);
    set_base_stat(SS_STR, 20);
    set_base_stat(SS_DEX, 20);
    set_base_stat(SS_CON, 20);
    set_skill(SS_WEP_SWORD, 20);
    set_skill(SS_PARRY, 20);
    set_skill(SS_DEFENCE, 20);
    set_hp(10000);
    set_alignment(-10);
    add_prop(CONT_I_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME, 75000);
    call_out("equip_me", 1);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}