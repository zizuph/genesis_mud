/*
    gardener.c
    
    Code by Sarr,
    Recoded by Fysix, Feb 1998
 */

inherit "/d/Kalad/std/monster";

#include "default.h"

void
create_kalad_monster()
{
    set_name("gardener");
    set_adj("tired");
    add_adj("sweaty");
    set_race_name("human");
    set_gender(random(2));
    set_short("tired sweaty gardener");
    set_long("This poor soul toils in the garden with worn out hands. "+
        "It looks like "+HE(TO)+" rarely gets a break.\n");
    set_alignment(400);
    set_knight_prestige(-100);
    add_speak("Its so nice to talk to you about trivial matters.\n");
    set_stats(({70,50,60,40,50,30}));
    set_skill(SS_DEFENSE,30);

    set_act_time(5);
    add_act("emote digs a hole.");
    add_act("emote trims the bushes.");
    add_act("emote waters the flowers.");

    add_prop(LIVE_I_NEVERKNOWN,1);

    add_equipment(({
        NOBLE + "arm/stained_pants",
        NOBLE + "arm/soiled_tunic",
        NOBLE + "wep/hand-shovel",
        }));
}
