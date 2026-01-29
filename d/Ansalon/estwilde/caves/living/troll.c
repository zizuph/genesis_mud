#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

inherit AC_FILE
inherit "/std/combat/unarmed"; 

void
create_creature()
{
    set_race_name("troll");
    set_short("giant two-headed troll");
    set_adj("two-headed");
    set_adj("giant");

    set_long("This hunched creature is about ten feet tall. He has " + 
             "mottled, greenish brown skin and writhing, dirty hair. " +
             "His long arms end in wide hands with very sharp looking " +
             "claws. Neck of this monster bears two giant heads, which " +
             "are grinning evilly with dangerous glint in their dull, " +
             "black eyes.\n");

    set_gender(G_MALE);
 
    set_stats(({220, 100, 200, 40, 40, 100}));
    set_hp(9000);

    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_alignment(-700);

    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_AWARENESS, 80);

    set_attack_unarmed(0, 35, 45, W_SLASH, 50, "right claw");
    set_attack_unarmed(1, 35, 45, W_SLASH, 50, "left claw");

    set_hitloc_unarmed(0, ({ 40, 40, 40,}), 11, "left head");
    set_hitloc_unarmed(1, ({ 40, 40, 40,}), 11, "right head");
    set_hitloc_unarmed(2, ({ 40, 40, 40,}), 38, "body");
    set_hitloc_unarmed(3, ({ 40, 40, 40,}), 10, "right leg");
    set_hitloc_unarmed(4, ({ 40, 40, 40,}), 10, "left leg");
    set_hitloc_unarmed(5, ({ 40, 40, 40,}), 10, "right arm");
    set_hitloc_unarmed(6, ({ 40, 40, 40,}), 10, "left arm");
}