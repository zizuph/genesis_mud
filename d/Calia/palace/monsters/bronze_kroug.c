/*      This is a kroug in the dark crystalline palace.

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
create_kroug()
{
    if (!IS_CLONE)
        return;

    set_race_name("kroug");
    set_title("the Bronze Kroug");
    set_long(BS(
        "This charred black-skinned humanoid is contemplating your " +
        "destruction.  " +
        "He has vaguely dwarven features.  " +
        "\n"));
    set_base_stat(SS_INT, 55);
    set_base_stat(SS_WIS, 55);
    set_base_stat(SS_DIS, 55);
    set_base_stat(SS_STR, 55);
    set_base_stat(SS_DEX, 55);
    set_base_stat(SS_CON, 55);
    set_base_stat(SS_OCCUP, 55);
    set_skill(SS_WEP_AXE, 55);
    set_skill(SS_PARRY, 55);
    set_skill(SS_DEFENCE, 55);
    set_hp(10000);
    set_alignment(-50);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
    call_out("equip_me", 1);
}