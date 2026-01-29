inherit "/std/monster";

#include "/sys/ss_types.h"

create_monster()
{
   set_name(({"orion","man"}));
   set_race_name("human");
   set_short("sad man");
   set_stats(({1,1,1,1,1,1}));
   set_long("This man is in misery.\n");
   set_adj("sad");


   set_gender(0);
   set_act_time(15);
   add_act(({"sigh","say I know all there is to know of the crying game.",
   		"emote looks at his wrists.","emote lets small clear drops of tear drop to the floor."}));

   set_cact_time(15);
   add_cact(({"emote looks at you in the eyes and you see all the sorry in his heart.",
	      "say Don't want more.. ", "say Of the crying game"}));
   set_skill(SS_DEFENCE,50);
   set_skill(SS_PARRY,50);
}
