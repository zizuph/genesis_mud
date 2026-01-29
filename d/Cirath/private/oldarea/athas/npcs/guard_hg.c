/* guard_hg.c: A simple poorly armed guard to be a pest here and
               there.  Created by Milashk.
               Made slightly more efficient by Serpine.
*/
inherit "/std/monster";
#include "defs.h"

void
create_monster()
{
   set_name("guard");
   add_name("giant");
   set_race_name("half-giant");
   set_adj("towering");
   add_adj("massive");
   set_long("This is an enormous creature. It stands over 10 feet "
        +"tall and must weigh a ton. A simple guard, he lacks the "
        +"brainpower for complex thinking.\n");
   set_stats(({150,120,150,35,35,70}));
   set_skill(SS_DEFENCE, 80);
   set_skill(SS_WEP_CLUB, 70);
   set_skill(SS_PARRY, 60);
   set_act_time(6);
   add_act("grin");
   add_act("emote flexes his powerful muscles.");
   add_act("sigh");
   add_act("emote leans on his club.");
   set_cact_time(3);
   add_cact("chuckle");
   add_cact("poke all eye");
   set_chat_time(6);
   add_chat("I get bored standing here all day.\n");
   add_chat("I get paid well for this job.\n");
   add_chat("Don't try anything funny, or i'll squash you.\n");
   set_cchat_time(3);
   add_cchat("You are a pitiful fool.\n");
   add_cchat("Why do you even try?\n");
   add_cchat("I like to destroy puny fools like you.\n");
   add_prop(LIVE_I_NEVERKNOWN, 1);
}

void
arm_me()
{
    clone_object(ATH_WEAPON+"club_hge.c")->move(TO);
    command("wield all");
}
