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
    add_name(({ "sentinel", "_stopping_npc" }));
    set_base_stat(SS_STR,random(10)+50);
    set_base_stat(SS_DEX,random(10)+50);
    set_base_stat(SS_CON,random(10)+50);
    set_base_stat(SS_INT,random(5)+40);
    set_base_stat(SS_WIS,random(5)+40);
    set_base_stat(SS_DIS,random(5)+55);
    set_skill(SS_WEP_SWORD, random(5)+50);
    set_skill(SS_WEP_POLEARM, random(5)+50);
    set_skill(SS_DEFENCE,45);
    set_skill(SS_PARRY,30);
}
