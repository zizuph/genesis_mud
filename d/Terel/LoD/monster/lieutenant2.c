/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * lieutenant2.c
 *
 * a lieutenant of the legion 921111 redhawk
 * Modified by Sorgum 941029
 */

#include "/d/Terel/include/Terel.h"
inherit "/lib/unique";
inherit LOD_DIR + "monster/legion_soldier";

#include <ss_types.h>

void arm_me();
/*
 * Function name: create_monster
 * Description:   Create the monster. (standard)
 */
public void
create_monster()
{
    ::create_monster();
    set_name ("lieutenant");
    set_name ("lieutenant2");    
    set_short("legion second lieutenant");
    set_long("A second lieutenant in the legion army, they who have " +
	     "sworn not to rest until they have spread darkness all " +
	     "over the world.\n");
    set_adj("lieutenant");
    set_race_name("elf");
    set_gender(MALE);
    set_alignment(-300);

    set_stats(({65, 65, 60, 90, 90, 90}));
    SET_MAX_HP;
    set_skill(SS_DEFENCE,      55 + random(11));
    set_skill(SS_UNARM_COMBAT, 40 + random(11));
    set_skill(SS_PARRY,        55 + random(11));
    set_skill(SS_WEP_SWORD,    90 + random(5));
    set_skill(SS_BLIND_COMBAT, 30);
    set_skill(SS_AWARENESS,    40);
    
    AGGRESSIVE;
    add_prop(LIVE_I_QUICKNESS, 90);
    arm_me();
}

void
arm_me()
{
    FIX_EUID;
    clone_unique(LOD_DIR + "armour/battle_chainmail",10,LOD_DIR +
                 "armour/steel_chainmail",50)->move(TO);
    clone_object(LOD_DIR + "armour/battle_helmet")->move(TO);
    clone_object(LOD_DIR + "weapon/battle_sword")->move(TO);
    command("wear all");
    command("wield sword");
    return;
}
