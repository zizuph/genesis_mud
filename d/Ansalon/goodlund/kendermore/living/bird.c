/* Birds in Kendermore, Gwyneth, June 12, 1999 */
#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/act/action";
inherit AC_FILE
inherit "/std/act/attack";

/* Randomly loads different colour birds. */

string *colour=({"red", "blue", "black", "white", "brown", "yellow"});

void
create_creature()
{
    set_name("bird");
    set_race_name("bird");
    set_adj(colour[random(6)]);
    set_gender(G_NEUTER);
    set_long("This little bird is singing a sweet bird song. Its feathers " +
        "are sleek and shiny, and its eyes are bright.\n");

    set_stats(({2,2,2,2,2,2}));

    set_hp(10);
    set_alignment(0);
    set_knight_prestige(-2);

    NEVERKNOWN;

    set_act_time(10);
    add_act("emote flaps its wings.");
    add_act("emote hops around on the ground, looking for worms.");
    add_act("emote bursts into song.");
    add_act(({"emote flies into the air and lands on your shoulder briefly",
        "emote is startled by a sudden movement and flies to a safe " + 
        "distance again."}));
    add_act("emote pecks at the ground.");

    set_cact_time(10);
    add_cact("emote swoops down, aiming for the eyes.");

    set_attack_unarmed(1, 15, 10, W_SLASH, 25, "left claw");
    set_attack_unarmed(1, 15, 10, W_SLASH, 25, "right claw");
    set_attack_unarmed(2, 20, 8, W_IMPALE, 20, "beak");

    set_hitloc_unarmed(1, 2, 70, "body");
    set_hitloc_unarmed(2, 1, 10, "head");
    set_hitloc_unarmed(4, 1, 5, "right wing");
    set_hitloc_unarmed(5, 1, 5, "left wing");
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(CONT_I_VOLUME, 300);
    add_prop(CONT_I_WEIGHT, 300);
    add_prop(NPC_I_NO_LOOKS,1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, " is too small to take anything!\n");
}
