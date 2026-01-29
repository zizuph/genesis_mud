/* Takeable kitten from Kendermore, Gwyneth, June 1999 */

#include "/d/Ansalon/goodlund/kendermore/local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

inherit "/std/act/action";
inherit AC_FILE
inherit "/std/act/attack";

/* Randomly loads a different colour kitten */

string *colour=({"brown", "grey", "calico", "black", "white", "orange"});

void
create_creature()
{
    set_name("this_kitten");
    add_name("kitten");
    set_race_name("kitten");
    set_adj(colour[random(6)]);
    set_gender(random(2));

    set_long("A small fluffy kitten. It looks healthy and loved.\n");

    set_stats(({5,5,5,2,2,5}));

    set_hp(400);
    set_alignment(50);
    set_knight_prestige(-5);

    NEVERKNOWN;

    set_act_time(10);
    add_act("emote chases after a butterfly.");
    add_act("emote meows loudly.");
    add_act("emote plays with a bug on the ground.");
    add_act("emote pounces on an invisible prey.");

    set_attack_unarmed(1, 11, 8, W_SLASH, 25, "left claw");
    set_attack_unarmed(1, 11, 8, W_SLASH, 25, "right claw");
    set_attack_unarmed(2, 15, 6, W_IMPALE, 20, "teeth");

    set_hitloc_unarmed(1, 4, 80, "body");
    set_hitloc_unarmed(2, 3, 10, "head");
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_M_NO_GET, 0); /* Can be picked up */
    add_prop(OBJ_M_NO_DROP, 0);
    add_prop(CONT_I_WEIGHT, 350);
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 350);
    add_prop(CONT_I_VOLUME, 350);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " haughtily ignores you.\n");
}
