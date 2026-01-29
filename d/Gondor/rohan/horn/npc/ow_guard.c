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
    set_extra_desc("");
    set_guard_type(1);
    ::create_monster();
    set_base_stat(SS_STR,random(25)+40);
    set_base_stat(SS_DEX,random(25)+40);
    set_base_stat(SS_CON,random(25)+40);
    set_base_stat(SS_INT,random(25)+30);
    set_base_stat(SS_WIS,random(25)+30);
    set_base_stat(SS_DIS,random(25)+45);
    set_random_move(15);
    set_restrain_path(({ROH_DIR + "horn/on_walls/o_wall1",
                        ROH_DIR + "horn/on_walls/o_wall2",
                        ROH_DIR + "horn/on_walls/o_wall3",
                        ROH_DIR + "horn/on_walls/o_wall4"}));
    set_monster_home(({ROH_DIR + "horn/on_walls/o_wall2"}));
    set_skill(SS_WEP_POLEARM, random(5)+40);
    set_skill(SS_DEFENCE,40);
    set_skill(SS_PARRY,30);
}
