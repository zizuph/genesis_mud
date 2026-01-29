/*      This is a calian in the crystal palace.

    coder(s):   Glykron

    history:    29/9/95     upgraded again                  Maniac
                15.6.95     upgraded                        Maniac
                31. 8.93    calian object added             Glykron

    purpose:    to guard stairs
    objects:    none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
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
    clone_object(WEAPON("glaive"))->move(this);
    command("wield glaive");
    clone_object(ARMOUR("splint_mail"))->move(this);
    command("wear armour");
    type = RANDOM_ELEMENT( ({ "boots", "helmet" }) );
    clone_object(ARMOUR("splint_" + type))->move(this);
    command("wear " + type);
    MONEY_MAKE_SC(5)->move(this);
}

void
create_calian()
{
    if (!IS_CLONE)
	return;

    ::create_calian();
    set_long("@@calian_long");
    set_base_stat(SS_INT, 50);
    set_base_stat(SS_WIS, 50);
    set_base_stat(SS_DIS, 100);
    set_base_stat(SS_STR, 50);
    set_base_stat(SS_DEX, 50);
    set_base_stat(SS_CON, 50);
    set_base_stat(SS_OCCUP, 50);
    set_skill(SS_WEP_POLEARM, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_DEFENCE, 50);
    set_hp(10000);
    set_alignment(50);
    set_calian_title(0);
    set_alarm(1.0, 0.0, "equip_me");
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
