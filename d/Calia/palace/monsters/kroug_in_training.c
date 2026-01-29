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
create_kroug()
{
    if (!IS_CLONE)
	return;

    ::create_kroug();
    set_title("the Kroug in Training");
    set_long(BS(
	"This charred black humanoid is practicing committing evil deeds.  " +
	"\n"));
    set_base_stat(SS_INT, 30);
    set_base_stat(SS_WIS, 30);
    set_base_stat(SS_DIS, 30);
    set_base_stat(SS_STR, 30);
    set_base_stat(SS_DEX, 30);
    set_base_stat(SS_CON, 30);
    set_base_stat(SS_OCCUP, 30);
    set_skill(SS_WEP_POLEARM, 30);
    set_skill(SS_PARRY, 30);
    set_skill(SS_DEFENCE, 30);
    set_hp(10000);
    set_alignment(-20);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    call_out("equip_me", 1);
    set_all_hitloc_unarmed(query_average_stat() / 2);
}