/*
    sama.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"

void
create_kalad_monster()
{
    set_name("samantha");
    set_adj("sexy");
    add_adj("dark-eyed");
    add_name("woman");
    set_gender(1);
    set_race_name("human");
    set_short("sexy dark-eyed woman");
    set_long("This sexy woman stares at you with dark eyes as black "+
        "as night. Her eyes contrast with her soft blond hair that flows "+
        "down her back. She is half-submerged in the water, but you can "+
        "see that she is naked, and her beautiful skin gleams in the "+    
        "soft light.\n");
    set_alignment(400);
    set_knight_prestige(-100);
    set_stats(({50,80,50,40,50,70}));
    set_skill(SS_DEFENSE,60);
    set_skill(SS_UNARM_COMBAT,60);
    set_act_time(5);

    add_act("moan");
    add_act("lick erotic");
    add_act("say Ooooh...yes, right there.....mmmmm...");
    add_act("emote breaths heavily.");
    add_act("emote strokes the hair of one of her slaves.");
    add_act("sigh");
    add_act("emote runs her hands over her curvy body.");
    add_prop(LIVE_I_NEVERKNOWN,1);
}
