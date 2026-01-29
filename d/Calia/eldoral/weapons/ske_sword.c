#pragma strict_types

#include "defs.h"

#define HIT 25
#define PEN 20

inherit "/std/weapon";

public void
create_weapon()
{
    set_name("longsword");
    add_name("sword");
    set_adj("ancient");
    add_adj("grey");
    set_short("ancient grey longsword"); 
    set_pshort("ancient grey longswords"); 
    set_long("A strange sword of ancient design, the quality of " +
        "construction is quite good. The weapon itself " +
        "seems to have somehow taken on an aura of rancor, " +
        "as if exposed to years of unfathomable hatred. " +
        "The sleek steel blade is double-edged, aged and greyed " +
        "by countless years, as is its simple steel cross piece " +
        "and leather-wrapped hilt.\n");
    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_SWORD);
    set_hands(W_ANYH);
    set_dt(W_SLASH | W_IMPALE);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(HIT, W_SWORD));
    add_prop(OBJ_I_VOLUME, 7500 / 5);
}
