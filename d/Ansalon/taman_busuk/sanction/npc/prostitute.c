#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <money.h>

inherit AM_FILE

#include "pro_reaction.h"

string *gAdj1 = ({"beautiful","comely","pretty","fair",
  "ordinary","cute","homely"});

string *gAdj2 = ({"young","sly","busty","long-legged",
  "blond-haired","voluptuous","plump"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("courtesan");
    set_adj(ONE_OF(gAdj1));
    add_adj(ONE_OF(gAdj2));
    set_short(implode(query_adjs()," ") + " courtesan");
    set_race_name("human");
    set_gender(1);  /*female for the idiots */
    set_long("This is one of the many prostitutes that work " +
      "in the Naked Sylph, a brothel in Sanction. She is dressed " +
      "in a skimpy silk gown which does little to hide her " +
      "sensual body.\n");

    set_stats(({20,20,20,20,20,20}));
    set_hp(10000);

    set_alignment(0);
    set_knight_prestige(-3);
    set_skill(SS_WEP_SWORD, 20 + random(20));
    set_skill(SS_DEFENCE, 5 + random(20));
    set_skill(SS_AWARENESS, 10 + random(25));
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_HEIGHT, 180 + random(10));
    add_prop(CONT_I_WEIGHT, 49000 + random(5000));

    set_act_time(50);
    add_act("emote runs her hands down her skimpy silk gown.");
    add_act("fondle all");
    add_act("emote smiles at you slyly.");
    add_act("emote sits down on the bed and crosses her legs sensually.");


    seteuid(getuid(TO));
}

void
init_living()
{
    set_alarm(1.0, 0.0, "greet_func1",TP);
    ::init_living();
}
