/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * speed_dagger.c
 *
 * used by Trevin in Last.
 *
 * Cotillion 2015-02-14: QUICKNESS 100 -> 50, Knife req changed to 80+
 */

#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include "/d/Terel/include/recover.h"
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <ss_types.h>

object quickness;

/*
 * Function name: create_weapon
 * Description:   create the weapon. (standard)
 */
public void
create_weapon()
{
    set_name(({"dagger"}));
    add_name("speed");
    set_short("silver dagger");
    set_long("The dagger shines and flickers in the light, as if it's light "+
            "itself. It's well balanced and extremely light. The handle is "+
            "wraped in soft grooved leather to allow for a tight grip.\n");
    set_adj("silver");

    /* Now we want to set the 'to hit' value and 'penetration value' */
    set_hit(38);
    set_pen(33);
    add_prop(OBJ_I_WEIGHT, 450);
    add_prop(OBJ_I_VOLUME, 750);
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(MAGIC_AM_MAGIC,({55,"enchantment"}));
    add_prop(OBJ_S_WIZINFO,"The dagger increases the speed of "+
             "the wielder if the wielder has 100 knife skill. " +
             "Otherwise it is just a very good knife. It's found after" +
             " slaying the giant troll in northern Terel. "+
             "/d/Terel/common/moor/tcaves/monster/gtroll.c.\n");

    add_prop(MAGIC_AM_ID_INFO,({
             "The silver dagger is enchanted to increase the quickness of "+
             "worthy wielders./n",70}));

    
    /* The weapon type and the type of damage done by this weapon */
    set_wt(W_KNIFE);
    set_dt(W_SLASH);
    set_wf(TO);

    /* Last, how shall it be wielded? */
    set_hands(W_ANYH); /* You can wield it in any hand. */
    set_likely_dull(1);
    set_likely_corr(0);
}

mixed
wield(object ob)
{
    if(TP->query_skill(SS_WEP_KNIFE) >= 80)
     {
        TP->add_prop(LIVE_I_QUICKNESS, 
        TP->query_prop(LIVE_I_QUICKNESS)+50);
        quickness = TP;
     }
}

mixed unwield(object wep)
{
  if(objectp(quickness))
  {
    quickness->add_prop(LIVE_I_QUICKNESS, 
                        quickness->query_prop(LIVE_I_QUICKNESS)-50);
    quickness = 0;
  }
  /* If you want special unwield messages put them here */
  /* and return 1 instead of 0.                         */ 
  return 0;
}


