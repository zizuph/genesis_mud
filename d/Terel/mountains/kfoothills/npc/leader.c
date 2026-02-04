#include "/d/Terel/include/Terel.h"
#include "../include/hills_defs.h"
#include <ss_types.h>
#include <money.h>
#include <options.h>

inherit STDMONSTER;
inherit "/std/act/domove";

void arm_me();

int
query_option(int opt)
{
    return (opt == OPT_UNARMED_OFF);
}

void
create_monster()
{
    set_race_name("kobold");
    set_name("leader");
    set_adj("tough-looking");
    add_adj("ragged");
    set_gender(MALE);
    set_long("A small dog-faced creature with dark grey scaly skin. " +
        "Large red-black eyes stare back at you with hatred as you notice " +
        "very sharp teeth hanging from its snarled mouth. " +
        "He looks well prepared for the extreme environment above ground " +
        "and prepared to enter battle at any moment.\n");

    set_stats(({ (40 + random(10)), (40 + random(5)), (40 + random(10)),
                (20 + random(5)), (20 + random(5)), (20 + random(5)) }));
    set_alignment(-250 - random(100) );


    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_HEIGHT, 30000);
    add_prop(CONT_I_VOLUME, 25000);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(NPC_I_NO_FEAR, 1);

    set_restrain_path(HILLS_PATH);
    set_random_move(60);
    set_aggressive(0);
    set_all_hitloc_unarmed(20);

    set_skill(SS_WEP_SWORD, 40 + random(10) );
    set_skill(SS_DEFENCE, 40 + random(10) );
    set_skill(SS_AWARENESS, 25 + random(5) );
    set_skill(SS_PARRY, 35 + random(15) );
    arm_me();
}

void
arm_me()
{
    FIX_EUID;
    MONEY_MAKE( random(3), "gold")->move(TO);
    MONEY_MAKE( 3 + random(3), "silver")->move(TO);

    clone_object("/d/Terel/common/swamp/dirty_sword")->move(TO);
    clone_object(HILLS_PATH + "armour/ragged_fur")->move(TO);

    command("wear all");
    command("wield all");
    return;
}
