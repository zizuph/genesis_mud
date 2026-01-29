/*
 *  /d/Emerald/north_shore/outpost/wep/woodaxe.c
 *
 *  The axe used by woodcutters for the outpost on the North Shore of
 *  lake Telberin.
 *
 *  Created April 2007, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
inherit "std/weapon.c";

#include <wa_types.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_weapon();


/*
 * Function name:        create_weapon
 * Description  :        constructor for the weapon
 */
public void
create_weapon()
{
    set_name("axe");
    add_name("woodaxe");
    set_short("heavy woodaxe");
    add_adj( ({ "sturdy", "wood", "woodcutters", "iron" }) );
    set_long("Sturdy wood comprises the shaft upon which the sharpened"
      + " iron blade of this woodcutters axe is fixed.\n");

    set_hit(25);
    set_pen(30);
    set_pm(({ -2, 1, 0 }));
    add_prop(OBJ_I_WEIGHT, 2400); 
    add_prop(OBJ_I_VOLUME,  550);
    set_wt(W_AXE);
    set_dt(W_IMPALE|W_SLASH);
    set_hands(W_BOTH);
} /* create_weapon */