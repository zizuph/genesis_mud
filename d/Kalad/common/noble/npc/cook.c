/*
    cook.c
    
    Code by Sarr,
    recoded by Fysix, Feb 1998
 */

inherit "/d/Kalad/std/monster";

#include "default.h"

void
create_kalad_monster()
{
    set_name("cook");
    set_adj("happy");
    add_adj("fat");
    set_race_name("human");
    set_short("happy fat cook");
    set_long("This guy is busy working to cook meals for the noble "+
        "family. Unlike the rest of the servants here, he looks like he "+
        "enjoys his work. He walks around, dipping his finger in the "+
        "pots testing out food.\n");
    set_stats(({50,50,50,50,50,50}));
    set_skill(SS_DEFENCE,30);
    set_alignment(700);
    set_knight_prestige(-500);

    set_act_time(5);
    add_act("say Where is my garlic!?");
    add_act("say The beef stew is too hot!");
    add_act("emote kicks some rats that were on the ground out of his way.");
    add_act("emote move some pots around.");
    add_act("say I think we shall make pizza tonight!");
    add_act("sweat");

    add_equipment(({
        NOBLE + "arm/apron",
        NOBLE + "arm/stained_pants",
        }));
}

