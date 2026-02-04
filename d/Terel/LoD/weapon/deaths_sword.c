//This weapon was ILLEGAL.
//Have it follow the weapon rules.
//Notify Tepisch or Rastlin when it is fixed.
/* This comment tells emacs to use c++-mode  -*- C++ -*- */
/*
 * /d/Terel/LoD/weapon/deaths_sword.c
 *
 * Used by deaths knights and master knights in LoD.
 *
 * Copyright (C) by: Redhawk 92 09 24
 * 
 * Revision history:
 * modified by Sorgum 941025
 * Balance work by Boron 13/Aug/1996
 *
 *  Modified: 3 May 2003, by Bleys
 *      - fixed a typo in the long desc
 *
 */

#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include "/d/Terel/include/recover.h"
#include <wa_types.h>
#include <formulas.h>

/*
 * Function name: create_weapon
 * Description:   create the weapon. (standard)
 */
public void
create_weapon()
{
    set_name(({"longsword","sword"}));
    set_pname(({"longswords","swords"}));
    add_pname("weapons");
    set_short("black steel longsword");
    set_long("A real deadly sword that looks like it belongs " +
	     "to Death himself. The blade radiates a very evil aura. When you " +
	     "examine the blade, you think you see the tormented souls " +
	     "that occupy Death's kingdom. Perhaps you are just imagining " +
	     "things.\n");
    set_adj(({"black","steel","death's", "deaths"}));

    /* 
     * Now we want to set the 'to hit' value and 'penetration value' 
     * * * * * * * * * * * * 
     * We know that this don't follow the rules regarding weapon_guide
     * for one handed swords, how ever the weapon manual allows up to
     * 35/35 for weapons so due to the monster size and the area, we
     * allow this. We add wiz_info for the same reasson!
     *        Sir Boron
     * * * * * * * * * * * * 
     */
    set_hit(33);
    set_pen(33);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);

    add_prop(OBJ_S_WIZINFO, "This weapon do not follow the rules "
            + "regarding \"man weapon_guide\"  however due to the "
            + "monster wielding it, the areas charecter and the fact "
            + "that one handed weapons can be up to 35/35 the 33/33 "
            + "is allowed for this weapon. ->Boron, for the AoB");
             
    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE); /* You can both 'slash' and 'impale' with it */

    /* Last, how shall it be wielded? */
    set_hands(W_RIGHT); /* You can wield it in the RIGHT hand. */
}
