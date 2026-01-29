/*      This is the gold kroug in the dark crystalline palace.

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
create_kroug()
{
    if (!IS_CLONE)
        return;

    set_race_name("kroug");
    set_title("the Gold Kroug");
    set_long("This charred-black kroug with vaguely human features is " +
        "guarding the northern doorway.\n");
    set_base_stat(SS_INT, 85);
    set_base_stat(SS_WIS, 85);
    set_base_stat(SS_DIS, 85);
    set_base_stat(SS_STR, 85);
    set_base_stat(SS_DEX, 85);
    set_base_stat(SS_CON, 85);
    set_base_stat(SS_OCCUP, 85);
    set_skill(SS_WEP_POLEARM, 85);
    set_skill(SS_PARRY, 85);
    set_skill(SS_DEFENCE, 85);
    set_hp(10000);
    set_alignment(-200);
    set_whimpy(0);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    call_out("equip_me", 1);
    set_all_hitloc_unarmed(query_average_stat() / 4);
}