inherit "/d/Genesis/race/shapeshift/shapeshift_creature";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define A_BITE  0                /* method of attack */

#define H_HEAD 0                 /* hit locations */
#define H_BODY 1
#define H_TAIL 2


void
create_shapeshift_creature()
{
    set_race_name("bear");
    set_adj(({"small", "white"}));
    set_short("small white bear");
    set_long("This is a small white bear, that's actually a mouse. While it looks cute, you sense "
        + "that there's more to him as meets the eye.\n");

    if (!IS_CLONE)
        return;

    set_gender(G_MALE);
    set_stats(({ 1, 3, 2, 1, 1, 2}));

    add_prop(CONT_I_WEIGHT, 1000); /* weight = 1 kilogram */
    add_prop(CONT_I_HEIGHT, 60); /* height = 6 centimeters */
    add_prop(CONT_I_VOLUME, 220); /* volume = 220 milliliters */

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE,   2, 3, W_IMPALE, 80, "sharp teeth");

    /* Hit_loc, *Ac against (impale/slash/bludgeon/magic), %hit, hit_desc */
    set_hitloc_unarmed(H_HEAD, ({ 5, 7, 3, 2 }), 30, "head");

    /* Hit_loc, *Ac against (impale/slash/bludgeon/magic), %hit, hit_desc */
    set_hitloc_unarmed(H_HEAD, ({ 5, 7, 3, 2 }), 30, "head");
    set_hitloc_unarmed(H_BODY, ({ 2, 4, 8, 0 }), 60, "body");
    set_hitloc_unarmed(H_TAIL, ({ 3, 0, 1, 0 }), 10, "tail");

    set_shapeshift_duration(300);
}