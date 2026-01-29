/* 
 * /d/Emerald/std/orc.c
 * 
 * The standard Emerald orc npc.
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Emerald/std/emerald_monster";

#include <ss_types.h>
#include <stdproperties.h>

void
config_orc(int level)
{
    set_stats(({ level * 11 / 10 + random(10),
                 level * 10 / 10 + random(10),
                 level * 11 / 10 + random(10),
                 level *  9 / 10 + random(10),
                 level *  6 / 10 + random(10),
                 level *  7 / 10 + random(10)}));

    set_skill(SS_WEP_CLUB, level + random(10));
    set_skill(SS_WEP_SWORD, level + random(10));
    set_skill(SS_WEP_POLEARM, level + random(10));
    set_skill(SS_WEP_KNIFE, level + random(10));
    set_skill(SS_WEP_AXE, level + random(10));
    set_skill(SS_UNARM_COMBAT, level * 8 / 10 + random(10));
    set_skill(SS_DEFENSE, level * 9 / 10 + random(10));
    set_skill(SS_PARRY, level * 7 / 10 + random(10)); 
    set_skill(SS_AWARENESS, level * 3 /10 + 20 + random(10));
    set_skill(SS_BLIND_COMBAT, max(60, level * 6 / 10 + random(10)));
}

void
create_orc()
{
    config_orc(50);
}

nomask void
create_emerald_monster()
{
    set_name("orc");
    set_race_name("orc");
    set_adj(({ "orc", "orcish" }));

    set_appearance(50 + random(50));
    set_appearance_offset(-20);

    add_prop(CONT_I_HEIGHT, 140 + random(40));
    add_prop(CONT_I_WEIGHT, 75000 + random(50000));
    add_prop(CONT_I_VOLUME, 75000 + random(50000));
  
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 5);
 
    create_orc();
}
