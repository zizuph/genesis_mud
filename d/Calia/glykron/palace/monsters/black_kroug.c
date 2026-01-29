/*      This is the black kroug in the dark crystalline palace.

    coder(s):   Glykron
    history:
                 3. 9.93    kroug object added              Glykron

    purpose:    to guard stairs
    objects:    none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include RANDOM_HEADER
#pragma save_binary

inherit KROUG;

void
arm_me()
{
    object this;
    string type;

    this = THIS;
    clone_object(WEAPON("sword_of_darkness"))->move(this);
    command("wield sword");
    clone_object(ARMOUR("mithril_platemail"))->move(this);
    command("wear armour");
    type = RANDOM_ELEMENT( ({ "shield", "gauntlets", "helmet", "boots", "cloak"
        }) );
    if (type == "cloak")
        clone_object(ARMOUR("white_" + type))->move(this);
    else
        clone_object(ARMOUR("mithril_" + type))->move(this);
    command("wear " + type);
}

void
create_kroug()
{
    if (!IS_CLONE)
        return;

    set_race_name("kroug");
    set_title("the Black Kroug");
    set_long(BS(
        "He is a charred-black skinned humanoid who is scribling some " +
        "strange runes at his desk.  " +
        "I wouldn't disturb him if I were you, as he looks like a match for " +
        "just about anybody.  " +
        "\n"));
    set_base_stat(SS_INT, 100);
    set_base_stat(SS_WIS, 100);
    set_base_stat(SS_DIS, 100);
    set_base_stat(SS_STR, 100);
    set_base_stat(SS_DEX, 100);
    set_base_stat(SS_CON, 100);
    set_base_stat(SS_OCCUP, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
    set_hp(10000);
    set_alignment(-400);
    set_all_hitloc_unarmed(query_average_stat() / 4);
    set_aggressive(1);
    set_attack_chance(90);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    call_out("arm_me", 1);
}