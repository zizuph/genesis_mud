#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

void
create_kalad_monster()
{
    set_name("gastonn");
    set_race_name("human");
    set_adj("greasy");
    set_long("This man is covered in grease, he seems to literally ooze "+
      "it from his very skin. He looks a bit flustered.\n");
    set_stats(({25, 50, 25, 25, 25, 20}));
    set_alignment(500);
    set_skill(SS_WEP_KNIFE, 30);
    set_title("the Masterful Chef");
    set_act_time(3);
    add_act("emote knocks some pans together, making a terrible racket.");
    add_act("say Now where did I put that screw...");
    add_act("say Damn its hot in here!");
    add_speak("Know any good recipes? I've got to make dinner!\n");
    set_knight_prestige(-500);
    add_ask(({"screw"}), "The chef says: I'll give you something if you "+
      "help me look for it.\n");
    set_default_answer("The chef screams: Quit wasting my time!\n");

    equip(({
                ARM + "tcchat",
                    ARM + "tccapron",
                    WEP + "tccknife"
                    }));
    
    MONEY_MAKE_SC(random(10))->move(TO);
}
