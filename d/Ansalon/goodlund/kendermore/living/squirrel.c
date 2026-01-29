/* Squirrel in the forest outside of Kendermore, Gwyneth, June 14, 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/act/action";
inherit AC_FILE
inherit "/std/act/attack";

void
create_creature()
{
    set_name("this_squirrel");
    add_name("squirrel");
    add_name("animal");
    set_race_name("squirrel");
    set_adj("curious");
    set_gender(G_MALE);
    set_long("This is a small grey squirrel. His tail is bushy and curls " + 
        "up over his back. He stands on his hind legs every once in a " + 
        "while to eat some food, usually a nut.\n");

    set_stats(({5,5,5,2,2,5}));

    set_hp(400);
    set_alignment(0);
    set_knight_prestige(0);

    NEVERKNOWN;

    set_act_time(10);
    add_act("emote twitches its whiskers.");
    add_act("emote stuffs a nut into his cheek pouches.");
    add_act("emote chatters noisily.");
    add_act("emote stands on his hind legs.");

    set_attack_unarmed(1, 11, 8, W_SLASH, 25, "left paw");
    set_attack_unarmed(1, 11, 8, W_SLASH, 25, "right paw");
    set_attack_unarmed(2, 15, 6, W_IMPALE, 20, "teeth");

    set_hitloc_unarmed(1, 4, 80, "body");
    set_hitloc_unarmed(2, 3, 10, "head");
    add_prop(OBJ_I_WEIGHT, 275);
    add_prop(CONT_I_WEIGHT, 275);
    add_prop(OBJ_I_VOLUME, 275);
    add_prop(CONT_I_VOLUME, 275);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " chatters at you, but refuses your " + 
        "gifts.\n");
}
