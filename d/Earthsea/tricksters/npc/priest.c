inherit "/std/monster";

#include <stdproperties.h>

#include "../defs.h"

void create_monster()
{
 object shadow;

 set_name("Dark Priest");
 set_race_name("priest");
 set_adj("dark");
 add_adj("hooded");
 set_long("This is Dark Priest of Kina , you can't see his face , "+
   "since he wears the hood. He looks very stern and coldhearted , "+
   "you feel creeps when you look at him.\n");

 add_prop(LIVE_S_EXTRA_SHORT," of Kina");
 add_prop(LIVE_I_NEVERKNOWN,1);

 set_stats(({300,300,300,300,300,300}));

 shadow = clone_object(TRICKSTERS_SHADOW);
 if (shadow->add_trick_shadow(TO)!=1)
   shadow->remove_shadow();

 set_skill(SS_KILL_POINTS,1056000);
 set_skill(SS_STRANGLE,100);
}

