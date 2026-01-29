/*
 *	/d/Gondor/common/dunedain/npc/atarauta.c
 *
 *	The shop keeper in the Houses of the Dunedain.
 *
 *	Copyright (c) 1996 by Christian Markus
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/dunedain/npc/npc_dunadan";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_dunadan() 
{
    set_name("atarauta");

    set_dunedain_house("Haladin");

    add_name(({"shopkeeper","owner","shopowner", "weapon master",
               "weaponmaster", }));

    set_race_name("human");
    set_adj(({"skinny", "dark-haired"}));

    set_long(BSN(
        "The Weaponmaster of the House of the Dunedain is in charge "
      + "of the armoury. He supplies members of the Houses with weapons "
      + "and armour out of the armoury's stock."));

    default_config_npc(65);
    set_base_stat(SS_STR, 55);
    set_base_stat(SS_CON, 75);
    set_base_stat(SS_INT, 75);

    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_DEFENCE,   90);
    set_skill(SS_PARRY,     90);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_APPR_MON, 90);
    set_skill(SS_APPR_OBJ, 90);
    set_skill(SS_APPR_VAL, 90);
    set_skill(SS_TRADING,   90);

    set_alignment(120);

    set_chat_time(12);
}

public varargs void
arm_me(int mt_equip = 0)
{
    object  wep, arm;

    ::arm_me(0);

    seteuid(getuid(TO));

    wep = clone_object(MINAS_DIR + "obj/mt_weapon");
    wep->set_weapon_type("two-handed sword");
    wep->move(TO);
    command("wield sword");
    arm = clone_object(MINAS_DIR + "obj/mtarmour");
    arm->set_armtype(0);
    arm->set_const(3+random(5));
    arm->set_metal(3+random(5));
    arm->move(TO);
    arm = clone_object(MINAS_DIR + "obj/mtarmour");
    arm->set_armtype(2);
    arm->set_const(2+random(4));
    arm->set_metal(3+random(5));
    arm->move(TO);
    command("wear all");
}

// solamnian prestige
int query_knight_prestige() { return -5; }

