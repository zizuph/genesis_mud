/*
 *  Evil killing club for the commander in Stonehold
 *  Tomas  -- Jan 2000.
 */
 
#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include <wa_types.h>
#include <stdproperties.h>

public void
create_weapon()
{
    set_name("warhammer");
    add_name(({"club","hammer"}));
    set_adj("mithril");
    set_pname("warhammers");
    set_short("mithril warhammer");
    set_long("The mithril warhammer looks very old. " +
       "The long handle is wrapped in soft rawhide leather. " +
       "The double-headed warhammer is made of pure mithril " +
       "polished to a high sheen. You notice some runes engraved " +
       "on the side of the hammer.\n");

    set_default_weapon( /* See /sys/wa_types.h for maxima */
       40,                     /* 'to hit' value    */
       45,                     /* penetration value */
       W_CLUB,                /* weapon type       */
       W_BLUDGEON,            /* damage type       */
       W_BOTH, TO);                 /* nr of hands       */


   add_prop(OBJ_I_WEIGHT,8000); /* Weighs 39 kg  All chrome */
   add_prop(OBJ_I_VOLUME,4000); /* Volume 5.5 Ltr */
 /* Formula taken from /doc/man/general/weapon:
  * cc = 50 + ((wchit * wcpen * min(wchit,wcpen)) / 4)
 */
    add_prop(OBJ_M_NO_BUY,1);
   add_prop(OBJ_I_VALUE, 2800);
   add_prop(OBJ_S_WIZINFO, "This club is only wieldable by good aligned. If a "+
                   "evil attempts to wield it they will lose 1500 hps. The "+
                   "club is evil slaying and does "+
                   "enemy->heal_hp(- ((random(dam/3)) + dam / 3)) on 5 out "+
                   "of 10 actual hits to evil aligned targets.\n");
   add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO,
        ({"The "+short()+" was crafted to be only wielded by only the pure at heart.\n",20,
           "It was forged to smite evil.\n",60}));

   add_item(({"runes","writing","lettering"}),
      "Maybe you might be able to read them.\n");

   add_cmd_item(({"runes","writing","lettering"}),
                 ({"read"}),"The runes read: BEWARE! Only the " +
                            "good at heart may wield me safely.\n");

   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
}

mixed wield(object obj)
{
    if (TP->query_alignment()  <= 0)
    {
        write("You real in pain as you attempt to wield the "+short()+". " +
            "The warhammer pulses as it burns into your palm!\n");
        say(QCTNAME(TP)+" reals in pain as "+QTNAME(wielder)+" attempts " +
          "to wield the " +short()+".\n");
        TP->heal_hp(-1500);
        if(TP->query_hp() <= 0)
            TP->do_die(TO);
        return -1;
    }

    if (TP->query_alignment() > 0)
    {
        write("Your hand vibrates as you wield the "+short()+".\n");
        say(QCTNAME(TP)+" wields the "+short()+".\n");
        return 1;
    }
    return 0;
}


public varargs int
did_hit (int aid, string hdesc, int phurt, object enemy, int dt,
      int phit, int dam)
{
    object wielder;

    if ((phurt >= 0) && 
        (enemy->query_alignment() <= 0))
    {
        wielder = query_wielded();
        enemy->heal_hp(- ((random(dam/3)) + dam / 3));
        enemy->catch_tell("The "+short()+" vibrates as it " +
           "connects with your body.\n");
        wielder->catch_tell("The "+short()+" vibrates in your hand "+
           "as it connects with " + enemy->query_the_name(wielder) + ".\n");
        wielder->tell_watcher("The "+short()+" smashes into "+
             QTNAME(enemy)+".\n", enemy);    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

