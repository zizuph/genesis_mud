/*
 * dagger.c
 *
 * This dagger is used by the Seer and the Lord Quest. It is a weapon
 * used by the seer to murder the lord of Castle Chimera years ago, and
 * serves as evidence of this murder. It is randomly placed in different
 * locations outside the ruins, and changes every time the quest resets.
 *
 * Coded by Khail, Jan 4/97.
 */
#pragma strict_types

#include "defs.h"

#define HIT 5
#define PEN 5

inherit "/std/weapon";

public void
create_weapon()
{
    set_name("dagger");
    add_name("knife");
    add_name("blade");
    add_name(ELDORAL_DAGGER_NAME);
    set_adj("old");
    add_adj("tarnished");
    set_short("old tarnished dagger"); 
    set_pshort("old tarnished daggers"); 
    set_long("This dagger is rather vicious-looking, even considering " +
        "how badly rusted and tarnished it is. The blade is serpentine " +
        "in shape. Long, but covered in rust pits. The hilt is made " +
        "from brass and leather, but the brass is covered in a thick " +
        "layer of green tarnish, and the leather has almost entirely " +
        "rotted away from the tang of the blade.\n");
    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_KNIFE);
    set_hands(W_ANYH);
    set_dt(W_SLASH);


    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 10);
}
