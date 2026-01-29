#include "default.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";

void
create_kalad_monster()
{
    set_name("duny");
    set_race_name("human");
    set_adj("young");
    add_adj("dirty");
    set_long("This boy looks like he's been working too hard. He is covered "+
      "with animal refuse, apparently because he's been in this tent for "+
      "hours, feeding and cleaning the animals.\n");
    set_stats(({50, 30, 30, 40, 40, 30}));
    set_alignment(750);
    set_act_time(6);
    add_act("give hay to horse");
    add_act("give hay to ox");
    add_act("give hay to camel");
    add_act("sigh");
    add_speak("I've been working here all day!\n");
    set_knight_prestige(-8);
    set_title("the Stablehand");
    MONEY_MAKE_CC(random(30))->move(this_object(), 1);
}
