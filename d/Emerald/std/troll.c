/*
 * /d/Emerald/std/troll.c
 * 
 * The standard Emerald troll npc.
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Emerald/std/emerald_monster";

#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Emerald/sys/properties.h"

void
config_troll(int level)
{
    set_stats(({ level * 18 / 10,
                 level *  8 / 10,
                 level * 20 / 10,
                 level *  2 / 10,
                 level *  2 / 10,
                 level *  5 / 10 }));

    set_all_attack_unarmed(min(40, query_stat(SS_DEX) / 3),
                           min(80, query_stat(SS_STR) / 3));

    set_skill(SS_WEP_CLUB, level + random(10));
    set_skill(SS_WEP_SWORD, level * 8 / 10 + random(10));
    set_skill(SS_WEP_POLEARM, level * 8 / 10 + random(10));
    set_skill(SS_WEP_KNIFE, level * 8 / 10 + random(10));
    set_skill(SS_WEP_AXE, level * 9 / 10 + random(10));
    set_skill(SS_UNARM_COMBAT, level + random(10));
    set_skill(SS_DEFENSE, level * 8 / 10 + random(10));
    set_skill(SS_AWARENESS, level / 10 + random(10));
    set_skill(SS_BLIND_COMBAT, max(40, level * 6 / 10 + random(10)));
}

void
create_troll()
{
    config_troll(80);
}

nomask void
create_emerald_monster()
{
    set_name("troll");
    set_race_name("troll");
    set_adj(({ "troll", "trollish" }));

    set_appearance(50 + random(50));
    set_appearance_offset(50); // trolls are ugly to almost everyone

    add_prop(CONT_I_HEIGHT, 300 + random(80));
    add_prop(CONT_I_WEIGHT, 200000 + random(100000));
    add_prop(CONT_I_VOLUME, 150000 + random(50000));
  
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 1);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_ACID, 70);
    add_prop(PRE_OBJ_MAGIC_RES + OBJ_I_RES_COLD, 90);
    add_prop(PRE_OBJ_MAGIC_RES + OBJ_I_RES_ELECTRICITY, 60);
    add_prop(PRE_OBJ_MAGIC_RES + OBJ_I_RES_POISON, 85);
    add_prop(PRE_OBJ_MAGIC_RES + OBJ_I_RES_FIRE, 80);
    add_prop(PRE_OBJ_MAGIC_RES + OBJ_I_RES_DEATH, 60);

    add_prop(NPC_I_NO_FEAR, 1); // Trolls have no fear


    add_prop(LIVE_I_QUICKNESS, -100); // +2 seconds per round

    set_all_hitloc_unarmed(40);      // Skin provides AC 40.
    set_all_attack_unarmed(30, 70);  // Unarmed attacks work at 30/70

    add_prop(LIVE_M_NO_VAMP_DRAIN, "Its skin is too thick and hard!\n");

    create_troll();
}
