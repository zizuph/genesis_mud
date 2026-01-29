/*      This is a calian in the crystal palace.

    coder(s):   Glykron

    history:   29/9/95     upgraded again                 Maniac
               15.6.95     upgraded                       Maniac
              17.11.94    title typo removed              Maniac
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
    add_name("guardian");
    set_long("@@calian_long");
    set_base_stat(SS_INT, 60);
    set_base_stat(SS_WIS, 60);
    set_base_stat(SS_DIS, 110);
    set_base_stat(SS_STR, 60);
    set_base_stat(SS_DEX, 60);
    set_base_stat(SS_CON, 60);
    set_base_stat(SS_OCCUP, 60);
    set_skill(SS_WEP_POLEARM, 60);
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    set_hp(10000);
    set_alignment(60);
    set_calian_title("Guardian");
    set_alarm(1.0, 0.0, "equip_me");
    set_all_hitloc_unarmed(query_average_stat() / 4);
}
