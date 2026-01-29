/*
 * /d/Emerald/std/elf.c
 *
 * This is the standard file for elves in Emerald.
 *
 * Copyright (c) 2000, by Shiva (?)
 *
 * Modification History:
 *   - June 9, 2000 : commented out add_adj("elven") to avoid seeing
 *                    "elven elves". Is it necessary? If not, please
 *                    just delete the line. (Gorboth)
 */
inherit "/d/Emerald/std/emerald_monster";

#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Genesis/login/login.h"

#define STATMOD(stat, lvl) (lvl * RACESTATMOD["elf"][stat] / 10)

public void
config_elf(int level)
{
    set_stats(({ STATMOD(SS_STR, level),
                 STATMOD(SS_DEX, level),
                 STATMOD(SS_CON, level),
                 STATMOD(SS_INT, level),
                 STATMOD(SS_WIS, level),
                 STATMOD(SS_DIS, level), }));

    set_skill(SS_WEP_KNIFE,    level * 7 / 10 + random(10));
    set_skill(SS_AWARENESS,    level * 9 / 10 + random(10));
    set_skill(SS_LANGUAGE,     level * 9 / 10 + random(10));
    set_skill(SS_DEFENSE,      level / 2 + random(10));
    set_skill(SS_PARRY,        level / 5 + random(10));
    set_skill(SS_UNARM_COMBAT, level / 2 + random(10));
    set_skill(SS_BLIND_COMBAT, max(40, level * 3 / 10 + random(10)));
}

public void
create_elf()
{
    /* The average elf is relatively old and experienced */
    config_elf(80);
}

nomask void
create_emerald_monster()
{
    set_race_name("elf");
//  set_adj("elven");

    add_prop(OBJ_I_RES_POISON, 30);
    add_prop(OBJ_I_RES_MAGIC,  20);
    add_prop(LIVE_I_QUICKNESS, 50);

    add_prop(CONT_I_HEIGHT, 210);
    add_prop(CONT_I_WEIGHT, 65000);
    add_prop(CONT_I_VOLUME, 60000);


    set_appearance(random(50));
    set_appearance_offset(-20);

    create_elf();
}
