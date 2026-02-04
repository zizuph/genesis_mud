/* This comment tells emacs to use c++-mode  -*- C++ -*- */
/*
 * /d/Terel/LoD/weapon/devils_stiltto.c
 *
 * Used by devil's knights in LoD.  This stiletto is magical.
 *
 * Revision history:
 * modified by Sorgum 941025
 * Lilith, Dec 2021: fixed typo in magic ID info.
 * Lilith, Feb 2022: made a spell enhancer lvl 40.
 */
#define MY_HIT 18
#define MY_PEN 35

#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

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
    set_name(({"stiletto"}));
    set_short("blackened-steel stiletto");
    set_long("A very deadly slender stiletto looks like it belongs " +
	     "to the devil himself. It radiates evil magic and " +
	     "you think you see the fire from hell reflecting in the " +
	     "blade. This blade doesn't seem to have been " +
	     "made by mortal hands.  It's probably a very powerful weapon.\n");
    set_adj(({"blackened-steel", "steel"}));

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(MY_HIT);
    set_pen(MY_PEN);
    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 45, "enchantment" }) );
    add_prop(MAGIC_AM_ID_INFO,
     ({"This blade has been enchanted to strike deep and "+
       "lethal blows.\n", 45}));
    add_prop(OBJ_S_WIZINFO,
      "It's been enchanted to do damage, but still remains "+
      "hard to hit with.\n");
    
    /* This is a knife, not a sword! */
    set_wt(W_KNIFE);
    set_dt(W_IMPALE); // weapon guide says only impale with 
                      // a stiletto 
    set_wf(TO);

    /* Last, how shall it be wielded? */
    set_hands(W_LEFT); /* You can wield it in your LEFT hand. */

    /* spell enhancer lvl 40 */
    set_magic_spellpower(40); 
}

int
wield(object ob)
{
    if (TP->query_prop("_LoD_NPC"))
    {
        set_hit(27);
        TP->update_weapon(TO);
    }
}

int
unwield(object ob)
{
    if (query_hit() > MY_HIT)
        set_hit(MY_HIT);
    if (query_pen() > MY_PEN)
        set_pen(MY_PEN);
    if (query_wielded())
        query_wielded()->update_weapon(TO);
}
