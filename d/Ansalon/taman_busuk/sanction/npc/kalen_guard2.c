#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE
inherit AUTO_TEAM

void
create_krynn_monster()
{
    set_pick_up_team(({"_kalen_guard"}));
    set_max_team_size_auto_join(3);

    set_name("human");
    add_name("_kalen_guard2");
    add_name("_kalen_guard");
    add_adj("short");
    add_adj("fat");
    set_short("short fat human");
    set_race_name("human");
    set_gender("G_MALE");
    set_long("Before you stands a fat human. He looks like he has been " +
             "travelling the world, the experience showing in his eyes. " +
             "Somehow he doesn't quite fit in with this type of people, "+
             "you sense that there is still some good in him.\n");
        
    set_stats(({140+random(50),
                120+random(40),
                80+random(40),
                140+random(20),
                140+random(20),
                140+random(20)}));
    set_hp(query_max_hp());

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_UNARM_COMBAT, 100);

    add_prop(CONT_I_WEIGHT, 120000);
    add_prop(CONT_I_HEIGHT, 185);

    set_all_hitloc_unarmed(40);

    set_alignment(450);
    set_knight_prestige(-10);
}

void
arm_me()
{
    seteuid(getuid(this_object()));

    clone_object(SOBJ+"weapon/big_sabre")->move(this_object(), 1);
    clone_object(SOBJ+"armour/black_chain")->move(this_object(), 1);
    command("wear all");
    command("wield all");
}
