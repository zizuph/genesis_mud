#pragma strict_types

#include "defs.h"

#define HIT 25
#define PEN 30

inherit "/std/weapon";

public void
create_weapon()
{
    set_name("claymore");
    add_name("sword");
    set_adj("black");
    add_adj("runed");
    set_short("black runed claymore"); 
    set_pshort("black runed claymores"); 
    set_long("The old claymore is a massive weapon, " +
        "wielded in two hands, its overall length is " +
        "almost up to an average human's shoulders. " +
        "The blade is most of the length, double-edged " +
        "and covered in undecipherable runes. The " +
        "cross-guards angle sharply towards the blade, " +
        "forming a V-shape. The handle itself is long " +
        "enough to be grasped with both hands and still " +
        "have room left over, and is made from steel-studded " +
        "wood, stained black with time and blood.\n");
    set_hit(HIT);
    set_pen(PEN);
    set_wt(W_SWORD);
    set_hands(W_BOTH);
    set_dt(W_SLASH | W_IMPALE);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(HIT, W_SWORD));
    add_prop(OBJ_I_VOLUME, 7500 / 5);
}
