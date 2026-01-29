#include "default.h"

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#define DO_I_TELL_RUMOURS  "_do_i_tell_rumours"

void
create_kalad_monster()
{
    add_prop(DO_I_TELL_RUMOURS, 1);
    set_name("pendras");
    add_name("dealer");
    set_race_name("human");
    set_adj("decrepit");
    add_adj("old");
    set_long("This old man looks like he's been stingy all his life, "+
      "always saving every coin he can get his grubby hands on.\n");
    set_stats(({50, 50, 25, 100, 100, 25}));
    set_alignment(100);
    set_skill(SS_AWARENESS, 100);
    set_title("the Master Dealer");
    set_act_time(3);
    add_act("emote looks impatiently at you.");
    add_act("say Hurry up and buy something.");
    add_act("tap");
    add_act("emote greedily rubs his hands in anticipation of some money.");
    add_speak("Buy everything I have!\n");
    set_knight_prestige(-100);
    add_prop(OBJ_M_NO_ATTACK, 1);
}
