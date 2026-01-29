/*  An inexperienced Calian in the crystalline palace.

    coder(s):   Glykron
    history:
                29/9/95     upgraded again                  Maniac
                15.6.95     upgraded                        Maniac
                29. 8.93    calian object inherited         Glykron
                25. 2.93    recovery added                  Glykron
                25. 2.93    header added                    Glykron
*/

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <money.h>
#include "defs.h"
#include RANDOM_HEADER
#pragma save_binary

inherit CALIAN;

void
arm_me()
{
    object this = this_object();
    string type;

    seteuid(getuid(this));
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
    set_base_stat(SS_INT, 45);
    set_base_stat(SS_WIS, 45);
    set_base_stat(SS_DIS, 95);
    set_base_stat(SS_STR, 45);
    set_base_stat(SS_DEX, 45);
    set_base_stat(SS_CON, 45);
    set_base_stat(SS_OCCUP, 45);
    set_skill(SS_WEP_POLEARM, 45);
    set_skill(SS_DEFENCE, 45);
    set_skill(SS_PARRY, 45);
    set_all_hitloc_unarmed(query_average_stat()/4);
    set_hp(10000);
    set_alignment(45);
    set_calian_title(0);
    set_alarm(1.0, 0.0, "arm_me");
}
