/* 	a Calian guard in the crystalline palace

    coder(s):   Glykron
    history:
                29/9/95     upgraded again                  Maniac
                15.6.95     updgraded                       Maniac
                17.11.94    title & descr typos removed     Maniac
                31. 8.93    calian object added             Glykron
                25. 2.93    modified                        Glykron
                25. 2.93    header added                    Glykron

*/

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <cmdparse.h>
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
    clone_object(WEAPON("guisarme"))->move(this);
    command("wield guisarme");
    clone_object(ARMOUR("banded_mail"))->move(this);
    command("wear armour");
    type = RANDOM_ELEMENT( ({ "boots", "gauntlets", "helmet" }) );
    clone_object(ARMOUR("banded_" + type))->move(this);
    command("wear " + type);
    MONEY_MAKE_SC(random(11))->move(this);
}


void
create_calian()
{
    if (!IS_CLONE)
	return;

    ::create_calian();
    set_long("@@calian_long");
    set_base_stat(SS_INT, 55);
    set_base_stat(SS_WIS, 55);
    set_base_stat(SS_DIS, 105);
    set_base_stat(SS_STR, 55);
    set_base_stat(SS_DEX, 55);
    set_base_stat(SS_CON, 55);
    set_base_stat(SS_OCCUP, 55);
    set_skill(SS_WEP_POLEARM, 55);
    set_skill(SS_PARRY, 55);
    set_skill(SS_DEFENCE, 55);
    set_hp(10000);
    set_alignment(55);
    set_calian_title(0);
    set_alarm(1.0, 0.0, "equip_me");
    set_all_hitloc_unarmed(query_average_stat() / 2);
}
