/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * sword.c
 *
 * The famous darkness sword of the orcchief.  The idea with this sword
 * is that it should become dark when it it is wielded.
 *
 * The original code for this sword has been worked on by Commander,
 * Vader and Olorin.
 * Updated by Shinto 9-27-98
 * -added undead check
 * -raised hit and pen to 45
 */

#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

/*
 * Function name: create_weapon
 * Description:   create the weapon. (standard)
 */
create_weapon()
{
    ::create_weapon();

    set_wf(TO);   /* Will force call of wield() and unwield() */
    set_name("longsword");
    add_name("sword");
    set_adj(({"black","obsidian"}));
    set_adj("darkness");
    set_short("obsidian longsword");
    set_long("It is made of black obsidian.  This sword brings darkness " +
      "and death.\n");
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VALUE, 8640);
    add_prop(OBJ_S_WIZINFO, "This sword adds darkness for undead and "+
                   "for those with adequate death spells > 20.\n");
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,
        ({"The obsidian is such that it will adsorb light---when mastered or "+
          "held by the dead.\n",20}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    set_hit(45);
    set_pen(45);
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_RIGHT);
    add_prop(OBJ_I_WEIGHT, 7900);
    add_prop(OBJ_I_VOLUME, 1000);
}

public mixed
wield(object wep)
{
    if (ETO->query_skill(SS_ELEMENT_DEATH) > 20 || 
                                     ETO->query_prop(LIVE_I_UNDEAD)) {
        add_prop(OBJ_I_LIGHT, -1);
        ETO->update_light(1);
        // Previous line fix by Wisk. 6/13/97
        write("The sword gets cold as ice as the light is absorbed by it.\n");
    }
    return 0;                   /* Do not affect rest of wield sequence */
}

public mixed
unwield(object wep)
{
    if (query_prop(OBJ_I_LIGHT) == -1) {
        add_prop(OBJ_I_LIGHT, 0);
        ETO->update_light(1);
        write("The darkness surrounding the blade disappears.\n");
    }
    return 0;                   /* Do not affect rest of unwield sequence */
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    
    if (from && living(from) && query_prop(OBJ_I_LIGHT) == -1) {
        add_prop(OBJ_I_LIGHT, 0);
        ETO->update_light(1);
    }
}
