#include "default.h"

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

#define DO_I_TELL_RUMOURS  "_do_i_tell_rumours"

void
create_kalad_monster()
{
    add_prop(DO_I_TELL_RUMOURS, 1);
    set_name("ystof");
    set_race_name("human");
    set_adj("old");
    add_adj("leathery");
    set_long("This man looks so weathered in appearance that he reminds "+
      "you of a saddlebag with eyes, he is actually that leathery-looking!\n");
    set_stats(({25, 50, 25, 90, 90, 25}));
    set_alignment(750);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_TRADING, 100);
    set_title("Olim, the Master Mapmaker");
    set_act_time(3);
    add_act("emote walks around, joints creaking like the planks in an old house.");
    add_act("say Would you care to buy a map?");
    add_act("smile");
    add_act("say I've got the finest quality maps.");
    add_speak("Buy everything I have!\n");
    set_knight_prestige(-750);
    add_prop(OBJ_M_NO_ATTACK, 1);
}
