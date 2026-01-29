/* 	The white calian in the crystalline palace.

    coder(s):   Glykron

    history:    31/1/97     added reward :)                Maniac
                15.6.95     upgraded                       Maniac
               14.12.94    No more auto-attack            Maniac
                17.11.94    title typo removed             Maniac
                25. 2.92    modified                       Glykron
                9. 2.92    header added                    Glykron

*/

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "defs.h"
#include RANDOM_HEADER
#include CALIAN_HEADER
#include COUNCIL_HEADER
#pragma save_binary

inherit CALIAN;

int
is_calian(object living)
{
    return living->query_guild_member(GUILD_NAME);
}


void
equip_me()
{
    object this;
    string type;

    seteuid(getuid());
    this = THIS;
    clone_object(WEAPON("sword_of_light"))->move(this);
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
    MONEY_MAKE_PC(random(2))->move(this);
}

void
create_calian()
{
    if (!IS_CLONE)
	return;

/*   set_race_name("human"); */
    set_gender(G_MALE); 
    set_long("@@calian_long");
    set_base_stat(SS_INT, 100);
    set_base_stat(SS_WIS, 100);
    set_base_stat(SS_DIS, 130);
    set_base_stat(SS_STR, 100);
    set_base_stat(SS_DEX, 100);
    set_base_stat(SS_CON, 100);
    set_base_stat(SS_OCCUP, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(REWARD, 3); 
    set_hp(10000);
    set_all_hitloc_unarmed(query_average_stat() / 4);
    set_alignment(300);
    set_aggressive(0);
    set_calian_title("White Calian");
    set_alarm(1.0, 0.0, "equip_me");
}

