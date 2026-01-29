/* Bear cub wandering Kendermore, Gwyneth June 13, 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/act/domove";
inherit "/std/act/action";
inherit AC_FILE
inherit "/std/act/attack";

string *colour=({"brown", "black"}); /* Random brown or black bear loaded. */

void
create_creature()
{
    set_name("cub");
    add_name("bear");
    add_name("animal");
    set_race_name("cub");
    set_adj(colour[random(2)]);
    set_gender(G_FEMALE);
    set_long("What is a bear cub doing in Kendermore? Perhaps some curious " +
        "kender adopted him. Her fur is healthy and shiny, and she looks " + 
        "friendly enough...\n"); 

    set_stats(({27,27,27,6,6,27}));

    set_hp(3100);
    set_alignment(0);
    set_knight_prestige(-5);

    NEVERKNOWN;

    set_attack_unarmed(1, 15, 10, W_BLUDGEON, 25, "left paw");
    set_attack_unarmed(1, 15, 10, W_BLUDGEON, 25, "right paw");
    set_attack_unarmed(2, 20, 8, W_IMPALE, 20, "teeth");

    set_hitloc_unarmed(1, 4, 80, "body");
    set_hitloc_unarmed(2, 3, 10, "head");

    set_random_move(20);
    set_restrain_path(KROOM);

    set_act_time(15);
    add_act("emote paces around.");
    add_act("emote looks at you with big brown eyes.");
    add_act("emote searches around for food.");

    set_cact_time(15);
    add_cact("emote roars aggressively.");
    add_cact("emote stands on her hind legs.");
    add_cact("emote makes a wide swipe with her claws.");
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(CONT_I_VOLUME, 500);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " doesn't seem to trust you!\n");
}
