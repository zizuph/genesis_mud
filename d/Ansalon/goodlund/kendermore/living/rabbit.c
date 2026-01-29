/* Rabbit in the forest outside Kendermore, Gwyneth, June 14, 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/act/action";
inherit AC_FILE
inherit "/std/act/attack";

/* Randomizes the colour of the rabbit */

string *colour=({"brown", "grey", "cotton-tailed", "black", "white", "spotted"});

void
create_creature()
{
    set_name("this_rabbit");
    add_name("rabbit");
    add_name("animal");
    set_race_name("rabbit");
    set_adj(colour[random(6)]);
    set_gender(random(2));
    set_long("This is a small fluffy rabbit. It's whiskers twitch as it " + 
        "looks at you nervously.\n");

    set_stats(({5,5,5,2,2,5}));

    set_hp(400);
    set_alignment(0);
    set_knight_prestige(0);

    NEVERKNOWN;

    set_act_time(10);
    add_act("emote twitches its whiskers.");
    add_act("emote hops a bit closer.");
    add_act("emote nibbles on a piece of food.");

    set_attack_unarmed(1, 11, 8, W_SLASH, 25, "left paw");
    set_attack_unarmed(1, 11, 8, W_SLASH, 25, "right paw");
    set_attack_unarmed(2, 15, 6, W_IMPALE, 20, "teeth");

    set_hitloc_unarmed(1, 4, 80, "body");
    set_hitloc_unarmed(2, 3, 10, "head");
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(CONT_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(CONT_I_VOLUME, 300);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " hops further away from your " + 
        "outstretched hand.\n");
}
