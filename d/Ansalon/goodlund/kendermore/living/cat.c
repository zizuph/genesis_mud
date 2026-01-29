/* Wandering cat for Kendermore, Gwyneth, June 12, 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>

inherit AUTO_TEAM
inherit "/std/act/action";
inherit AC_FILE
inherit "/std/act/attack";

/* Randomly loads different colour cats. */
string *colour=({"brown", "grey", "calico", "black", "white", "orange"});

void
create_creature()
{
    set_name("this_cat");
    add_name("cat");
    add_name("animal");
    set_race_name("cat");
    set_adj(colour[random(6)]);
    set_gender(G_FEMALE);
    set_long("A large sleek looking cat. You can tell she has no trouble " + 
        "finding food.\n");

    set_pick_up_team(({"kitten"}));

    set_stats(({15,15,15,5,5,15}));

    set_hp(2000);
    set_alignment(0);
    set_knight_prestige(-5);

    NEVERKNOWN;

    set_act_time(10);
    add_act("emote licks her fur.");
    add_act("emote meows loudly.");
    add_act("emote plays with a bug on the ground.");
    add_act("emote pounces on an invisible prey.");

    start_patrol();
    set_patrol_time(30);

    /* Makes a wide loop around Kendermore, starting and ending at fountain */

    set_patrol_path(({"e","se","ne","n","n","nw","ne","n","ne","e","ne","n",
        "w","nw","sw","w","n","ne","nw","sw","se","s","nw","w","nw","s","w",
        "sw","s","sw","se","s","ne","se","s"}));

    set_attack_unarmed(1, 15, 10, W_SLASH, 25, "left claw");
    set_attack_unarmed(1, 15, 10, W_SLASH, 25, "right claw");
    set_attack_unarmed(2, 20, 8, W_IMPALE, 20, "teeth");

    set_hitloc_unarmed(1, 4, 80, "body");
    set_hitloc_unarmed(2, 3, 10, "head");
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " pointedly ignores your gifts, and " + 
        "instead starts to clean her fur.\n");
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}
