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

void
create_creature()
{
    set_name("doe");
    add_name("deer");
    set_race_name("doe");
    set_adj("gentle");
    set_gender(G_FEMALE);
    set_long("This is a gentle female deer. She's foraging around the forest " +
        "for some food. Her coat is a beautiful red-brown with white spots.\n");

    set_stats(({30,30,30,6,6,30}));

    set_hp(3400);
    set_alignment(0);
    set_knight_prestige(0);

    NEVERKNOWN;

    set_attack_unarmed(1, 25, 10, W_BLUDGEON, 35, "left hoof");
    set_attack_unarmed(1, 25, 10, W_BLUDGEON, 35, "right hoof");

    set_hitloc_unarmed(1, 4, 80, "body");
    set_hitloc_unarmed(2, 3, 10, "head");

    set_random_move(20);
    set_restrain_path(KROOM);

    set_act_time(15);
    add_act("emote paces around.");
    add_act("emote looks at you with big brown eyes.");
    add_act("emote searches around for food.");

    set_cact_time(30);
    add_cact("emote kicks with her hooves.\n");
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " prances away skittishly as you offer " + 
        "your gift.\n");
}
