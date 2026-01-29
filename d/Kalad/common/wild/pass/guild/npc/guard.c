inherit "/d/Kalad/std/monster";
#include <macros.h>
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/guild/defs.h"
void
create_monster()
{
set_name("guard");
   set_race_name("drow");
   add_name("guard");
add_adj("wary");
set_long("This is a guard of the Drow Academy. He is very wary of "
	+"intruders, so if you aren't a member do not attempt to pass "
	+"into the school.\n");
   set_stats(({ 75, 100, 75, 60, 60, 60}));
   set_skill(SS_DEFENCE,70);
   set_skill(SS_PARRY, 75);
   set_skill(SS_WEP_POLEARM, 85);
   ::create_monster();
   if (IS_CLONE)
    set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
   seteuid(geteuid(this_object()));
   clone_object("/d/Kalad/common/wild/pass/guild/obj/dhalb")->move(TO);
   clone_object("/d/Kalad/common/wild/pass/guild/obj/dmail")->move(TO);
   command("wield all");
   command("wear all");
   seteuid(getuid(TO));
}
