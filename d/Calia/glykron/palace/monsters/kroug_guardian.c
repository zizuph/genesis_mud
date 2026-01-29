/*      This is a guardian kroug in the dark crystalline palace.

    coder(s):   Glykron
    history:
                 2. 9.93    kroug object added              Glykron

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

inherit KROUG;

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
create_kroug()
{
    ::create_kroug();
    add_name("guardian");
    set_title("the Guardian Kroug");
    set_long("He is guarding the gear stairs.\n");
    set_base_stat(SS_INT, 40);
    set_base_stat(SS_WIS, 40);
    set_base_stat(SS_DIS, 40);
    set_base_stat(SS_STR, 40);
    set_base_stat(SS_DEX, 40);
    set_base_stat(SS_CON, 40);
    set_base_stat(SS_OCCUP, 40);
    set_skill(SS_WEP_POLEARM, 40);
    set_skill(SS_PARRY, 40);
    set_skill(SS_DEFENCE, 40);
    set_hp(10000);
    set_alignment(-30);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    call_out("equip_me", 1);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}