/*
 * Gwyneth 4 November 2000 - Replaced ~elessar/lib/goodkill.h with
 *                           /d/Gondor/common/lib/logkill.c
 */
inherit "/d/Gondor/rohan/horn/npc/guard.c";

#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/logkill.c"

create_monster()
{
    if (!IS_CLONE)
        return;
    set_extra_desc("He has the look of an experienced warrior.");
    set_guard_type(2);
    ::create_monster();
    add_name("haderd");
    set_base_stat(SS_STR,random(10)+65);
    set_base_stat(SS_CON,random(10)+60);
    set_base_stat(SS_DEX,random(10)+60);
    set_base_stat(SS_INT,random(5)+45);
    set_base_stat(SS_WIS,random(5)+45);
    set_base_stat(SS_DIS,random(5)+55);
    set_random_move(12);
    set_restrain_path(({ROH_DIR + "horn/on_walls/i_wall1",
                        ROH_DIR + "horn/on_walls/i_wall2",
                        ROH_DIR + "horn/on_walls/i_wall3",
                        ROH_DIR + "horn/on_walls/i_wall4",
                        ROH_DIR + "horn/on_walls/i_wall5",
                        ROH_DIR + "horn/on_walls/i_wall6"}));
    set_monster_home(({ROH_DIR + "horn/on_walls/i_wall3"}));
    set_skill(SS_WEP_SWORD, random(5)+65);
    set_skill(SS_WEP_POLEARM, random(5)+65);
    set_skill(SS_DEFENCE,62);
    set_skill(SS_PARRY,41);
    set_skill(SS_AWARENESS,50);
}

