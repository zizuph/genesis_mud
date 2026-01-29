/*      This is a silver kroug in the dark crystalline palace.

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
    clone_object(WEAPON("silver_sword"))->move(this);
    command("wield sword");
    clone_object(ARMOUR("silver_chainmail"))->move(this);
    command("wear armour");
    type = RANDOM_ELEMENT( ({ "cloak", "helmet", "boots", "shield", "gloves" })
        );
    clone_object(ARMOUR("silver_" + type))->move(this);
    command("wear " + type);
    MONEY_MAKE_SC(random(30))->move(this);
}

void
create_kroug()
{
    if (!IS_CLONE)
        return;

    set_race_name("kroug");
    set_title("the Silver Kroug");
    set_long("This charred-black kroug with elven features looks ready to " +
	"kill you.\n");
    set_base_stat(SS_INT, 70);
    set_base_stat(SS_WIS, 70);
    set_base_stat(SS_DIS, 70);
    set_base_stat(SS_STR, 70);
    set_base_stat(SS_DEX, 70);
    set_base_stat(SS_CON, 70);
    set_base_stat(SS_OCCUP, 70);
    set_skill(SS_WEP_SWORD, 70);
    set_skill(SS_PARRY, 70);
    set_skill(SS_DEFENCE, 70);
    set_hp(10000);
    set_alignment(-100);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
    call_out("equip_me", 1);
}