#pragma strict_types
#pragma save_binary

inherit "/d/Emerald/std/emerald_monster";

#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Genesis/login/login.h"

#define STATMOD(stat, lvl) (lvl * RACESTATMOD["goblin"][stat] / 10)

public void
config_goblin(int level)
{
    set_stats(({ STATMOD(SS_STR, level),
                 STATMOD(SS_DEX, level),
                 STATMOD(SS_CON, level),
                 STATMOD(SS_INT, level),
                 STATMOD(SS_WIS, level),
                 STATMOD(SS_DIS, level) }));

    set_skill(SS_WEP_SWORD,    level * 9 / 10 + random(10));
    set_skill(SS_WEP_POLEARM,  level * 9 / 10 + random(10));
    set_skill(SS_WEP_KNIFE,    level + random(10));
    set_skill(SS_WEP_CLUB,     level + random(10));
    set_skill(SS_WEP_AXE,      level * 9 / 10 + random(10));
    set_skill(SS_UNARM_COMBAT, level + random(10));
    set_skill(SS_BLIND_COMBAT, max(40, level * 6 / 10 + random(10)));
    set_skill(SS_AWARENESS,    level / 2 + random(10));
    set_skill(SS_DEFENSE,      level + random(10));
    set_skill(SS_PARRY,        level / 3 + random(10));
}

    
public void
create_goblin()
{
    /* The average goblin is pretty weak */
    config_goblin(20);
}

nomask void
create_emerald_monster()
{
    set_name("goblin");
    set_race_name("goblin");
    set_adj(({ "goblin", "goblinish" }));

    set_appearance(50 + random(50));
    set_appearance_offset(-20); // goblins are pretty ugly

    add_prop(CONT_I_HEIGHT, 90 + random(30));
    add_prop(CONT_I_WEIGHT, 25000 + random(20000));
    add_prop(CONT_I_VOLUME, 25000 + random(20000));

    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(PRE_OBJ_MAGIC_RES + MAGIC_I_RES_POISON, 20);

    create_goblin();
}
