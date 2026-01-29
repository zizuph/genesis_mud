/* 	A very young kroug in the dark crystalline palace.

    coder(s):   Glykron
    history:
                 2. 9.93    kroug object added              Glykron
                25. 2.93    recovery added                  Glykron
                25. 2.93    header added                    Glykron

*/

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"
#include RANDOM_HEADER
#pragma save_binary

inherit KROUG;

void
arm_me()
{
    object this;

    this = THIS;
    clone_object(WEAPON("small_sword"))->move(this);
    command("wield sword");
    clone_object(ARMOUR("leather_shirt"))->move(this);
    command("wear armour");

    if (!random(4))
    {
	string type;

	type = RANDOM_ELEMENT( ({ "cap", "shield", "shoes" }) );
        if (type == "shield")
            clone_object(ARMOUR("stone_" + "shield"))->move(this);
        else
            clone_object(ARMOUR("leather_" + type))->move(this);
	command("wear " + type);
    }
}

void
create_kroug()
{
    if (!IS_CLONE)
	return;

    ::create_kroug();
    set_long("He is a charred black-skinned humanoid.\n");
    set_base_stat(SS_INT, 10);
    set_base_stat(SS_WIS, 10);
    set_base_stat(SS_DIS, 10);
    set_base_stat(SS_STR, 10);
    set_base_stat(SS_DEX, 10);
    set_base_stat(SS_CON, 10);
    set_skill(SS_WEP_SWORD, 10);
    set_skill(SS_PARRY, 10);
    set_skill(SS_DEFENCE, 10);
    set_hp(10000);
    set_alignment(-2);
    add_prop(CONT_I_WEIGHT, 50000);
    add_prop(CONT_I_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 60000);
    add_prop(CONT_I_MAX_VOLUME, 60000);
    call_out("arm_me", 1);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}