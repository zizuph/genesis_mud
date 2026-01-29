/*
 *  npc Cadorna quest-giver dagger
 *  Tharizdun, 2021
 */

#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;

int hit = 23+random(5),
    pen = 19+random(5);

void create_faerun_weapon()
{
    set_name("dagger");
    add_name("knife");
    set_adj("intricate");
    set_adj("raindrop-damascus");
    set_short("intricate raindrop-damascus dagger"); 
    set_long("This dagger has a foot long blade of raindrop damascus."
        +" The layers of steel are exposed and highlighted in irregular"
        +" cocentric circles creating an intricate pattern that is pleasing"
        +" to the eye. The blade is sharpened along both edges and tapers"
        +" to a point. The edge is razor sharp and will cut through most"
        +" non-metallic armours with ease. The handle is made of layered"
        +" linen in a resin that is hardened to an amber-like consistency."
        +" The crossguard is gold, shaped like a flax stalk with an unopened"
        +" blue flower at the end, actually a small sapphire. The pommel is"
        +" capped with a yet larger sapphire.\n");

    set_hit(hit);
    set_pen(pen);
    set_wt(W_KNIFE); 
    set_dt(W_SLASH || W_IMPALE); 

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(pen,W_SWORD)+random(50)-25);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(hit, pen)+random(20)-10);

    set_hands(W_ANYH); 
}

void
init()
{
    ::init();
}
