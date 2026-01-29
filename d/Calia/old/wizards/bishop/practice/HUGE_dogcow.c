inherit "/std/monster.c";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define BS(message)     break_string(message, 75)

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_race_name("dogcow");
    set_adj("huge");
    set_gender(G_NEUTER);

    set_long(BS("This dogcow is 30 feet tall. Now, you truly know fear.\n"));

    set_stats(({ 200, 150, 200, 5, 5, 200 }));
    set_hp(10000);

    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_PARRY, 80);
    set_skill(SS_WEP_CLUB, 100);

    add_prop(CONT_I_WEIGHT, 850000);
    add_prop(CONT_I_VOLUME, 850000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
}
