#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#define DO_I_TELL_RUMOURS "_do_i_tell_rumours"

void
create_kalad_monster()
{
    add_prop(DO_I_TELL_RUMOURS, 1);
    set_name("amey");
    set_race_name("human");
    set_adj("effeminite");
    add_adj("slender");
    set_long("An obviously feminine and gracefully slender woman, looking "+
      "to be in her late twenties. Gazing at her you seem to have forgotten "+
      "what exactly you are doing here...The arousing smell of perfume "+
      "emanating from her seems to jolt you back into alertness.\n");
    set_stats(({60, 70, 50, 40, 40, 35}));
    set_alignment(750);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_TRADING, 100);
    set_gender(G_FEMALE);
    set_title("Avondale, Perfumist and Lover of Flowers");
    set_act_time(3);
    add_act("emote sways from side to side as she walks about the room.");
    add_act("say A bottle of perfume would do wonders for you.");
    add_act("smile sweetly");
    add_act("say My perfumes are the best in all of Kabal.");
    add_act("say I've got colognes, as well as perfumes. Both are equally "+
      "wonderful.");
    add_speak("Would you care to look at my wares?\n");
    set_knight_prestige(-750);
    add_prop(OBJ_M_NO_ATTACK, "Now why would you want to do that?\n");
}
