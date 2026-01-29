#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../../local.h"

inherit "/lib/unique";
inherit AM_FILE

void arm_me();

void
create_krynn_monster()
{
    set_name("alanna");
    add_adj("pretty");
    add_adj("solamnian");
    set_short("pretty solamnian human");
    set_living_name("Alanna Uth Parreth of Kalaman");
    set_race_name("human");
    set_long("This slave looks as if she has been through a lot. " +
             "Behind the dirty gown, and her bruised body, she still manage "+
             "to hold a certain posture not letting anyone see that she is "+
             "afraid.\n");
    set_gender(G_FEMALE);
    
    set_stats(({50+random(50),
                50+random(40),
                50+random(40),
                50+random(20),
                140+random(20),
                140+random(20)}));
    set_hp(query_max_hp());

    set_skill(SS_AWARENESS, 100);

    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 165);

    set_all_hitloc_unarmed(40);

    set_alignment(1000);
    set_knight_prestige(-100);
    remove_prop(LIVE_I_NEVERKNOWN);
    arm_me();
}

void arm_me()
{
    clone_object(SARM+"dirty_dress")->move(TO, 1);
    command("wear all");
}
