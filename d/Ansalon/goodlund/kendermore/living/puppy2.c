/* Puppy in Kendermore, Gwyneth, June 12, 1999 */

#include "../local.h"
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/act/action";
inherit AC_FILE
inherit "/std/act/attack";
inherit "/std/act/domove";

void
create_creature()
{
    set_name("puppy");
    set_race_name("puppy");
    add_name("animal");
    set_short("glow in the dark puppy");
    set_adj("glowing");
    set_gender(random(2));
    set_long("This puppy has boundless energy, a perfect companion for " + 
        "a kender! Chasing "+HIS(TO)+" tail and barking seems to be "+HIS(TO)+" favoured " + 
        "activities. "+HE(TO)+" seems to be glowing with a pale light, " + 
        "as if "+HE(TO)+" had gotten slightly too close to Paladine.\n");

    set_stats(({17,17,17,6,6,17}));

    set_hp(2100);
    set_alignment(0);
    set_knight_prestige(-5);

    NEVERKNOWN;

    set_act_time(15);
    add_act("emote wags "+HIS(TO)+" tail.");
    add_act("emote barks playfully.");
    add_act("emote bites at your heels.");
    add_act("emote looks at you, hoping for a scrap of food.");

    set_attack_unarmed(1, 15, 10, W_BLUDGEON, 25, "left paw");
    set_attack_unarmed(1, 15, 10, W_BLUDGEON, 25, "right paw");
    set_attack_unarmed(2, 20, 8, W_IMPALE, 20, "teeth");

    set_hitloc_unarmed(1, 4, 80, "body");
    set_hitloc_unarmed(2, 3, 10, "head");

    set_random_move(20);
    set_restrain_path(KROOM);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_M_NO_GET, 0); /* Can be picked up */
    add_prop(OBJ_M_NO_DROP, 0);
    add_prop(CONT_I_WEIGHT, 700);
    add_prop(OBJ_I_WEIGHT, 700);
    add_prop(CONT_I_VOLUME, 700);
    add_prop(OBJ_I_VOLUME, 700);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " barks loudly and chases "+HIS(TO)+" tail. "+HE(TO)+" " + 
        "seems more interested in chasing "+HIS(TO)+" tail than anything else!\n");
}
