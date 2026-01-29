#pragma strict_types
inherit "/std/monster";
#include <ss_types.h>
#include <stdproperties.h>
#include <ss_types.h>

void
create_monster()
{
    set_name("monster");
    set_race_name("goblin");
    set_short("weak goblin");
    set_adj(({"small","weak"}));
    set_long("test monster with special skills and stats. \n");
    set_stats(({20,20,20,650,650,50}));
    set_skill(SS_HUNTING,1000);
    set_skill(SS_TRACKING,1000);
    set_skill(SS_TRADING,10000);
    set_skill(SS_HIDE,10000);
    set_skill(SS_SPELLCRAFT,10000);
    set_skill(SS_SWIM,100);
    set_skill(SS_2H_COMBAT,100);
    set_skill(SS_CLIMB,100);
    set_random_move(50);
    set_aggressive(1);
}
