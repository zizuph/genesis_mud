/* Darren of Tarsis, Shopkeeper of the Keep by Morrigan 1/97 */
// Navarre October 5th 2008: Changing act to not say he wont buy kalaman stuff.

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE

inherit "/std/act/action";


public void
create_krynn_monster()
{
    set_name("borry");
    set_race_name("human");
    set_title("of Kern, Pawnbroker of Kalaman");
    set_long("This dark-skinned sharp-eyed human is the local pawnbroker " +
      "of Kalaman. He will buy and sell most goods for a good price.\n");
    add_name(({"merchant","shopkeeper","man"}));
    set_adj("dark-skinned");
    add_adj("sharp-eyed");
    set_gender(G_MALE);
    add_prop(NPC_I_NO_LOOKS,1);
    set_introduce(1);
    add_prop(CONT_I_WEIGHT,80000);

    set_stats(({120,80,118,52,69,81}));
    set_skill(SS_DEFENCE,        50);
    set_skill(SS_BLIND_COMBAT,   50);
    set_skill(SS_AWARENESS,      50);
    set_skill(SS_UNARM_COMBAT,   75);

    set_alignment(450);
    set_knight_prestige(-2);

    set_act_time(5);
    add_act("say Without the guards of Kalaman we " +
            "would be overrun by the dragonarmies long ago.");
    add_act("say Please consider my wonderful wares!");

    set_cact_time(4);
    add_cact("fume");
    add_cact("growl");
    add_cact("say I've had my share of fights!");

    set_default_answer("For some reason, you are ignored.\n");
}

