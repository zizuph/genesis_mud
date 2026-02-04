/*
 *  Axe for gorges (the potion salesman) body guard, Grimrock.
 */
 
#include "/d/Terel/include/Terel.h"

inherit STDWEAPON;

#include <wa_types.h>
#include <stdproperties.h>
#define GOBLIN_POISON "/d/Terel/poison/goblin_poison"

public void
create_weapon()
{
    set_name("battleaxe");
    add_name("axe");
    set_adj("long-handled");
    set_adj("mithril");
    set_short("long-handled mithril battleaxe");
    set_long("The battleaxe has a long sturdy wooden handle "+
                   "connected to a mithril axe head. The axe head "+
                   "has two crossed axes embossed on it. The axe "+
                   "is fairly light weight and a quite formidable "+
                   "weapon.\n");

    set_default_weapon( /* See /sys/wa_types.h for maxima */
       45,                     /* 'to hit' value    */
       45,                     /* penetration value */
       W_AXE,                /* weapon type       */
       W_IMPALE | W_SLASH,     /* damage type       */
       W_ANYH, TO);                 /* nr of hands       */


   add_prop(OBJ_I_WEIGHT,10000); /* Weighs 39 kg  All chrome */
   add_prop(OBJ_I_VOLUME,5521); /* Volume 5.5 Ltr */
 /* Formula taken from /doc/man/general/weapon:
  * cc = 50 + ((wchit * wcpen * min(wchit,wcpen)) / 4)
 */
    add_prop(OBJ_M_NO_BUY,1);
   add_prop(OBJ_I_VALUE, 3200);
   add_prop(OBJ_S_WIZINFO, "This axe is only wieldable by dwarves. If a "+
                   "goblin attempts to wield it they will lose 1500 hps. The "+
                   "axe is goblin slaying and does "+
                   "enemy->heal_hp(- ((random(dam/2)) + dam / 2)) on 5 out "+
                   "of 10 actual hits to goblins.\n");
   add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO,
        ({"The "+short()+" was crafted to be only wielded by dwarves.\n",20,
           "It was forged to destroy goblins\n",60}));
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
}

mixed wield(object obj)
{
    object poison;
    if (TP->query_race_name() == "goblin")
    {
        write("As you grasp the handle of the "+short()+" the handle"+
                  "cuts into your skin!\n");
        say(QCTNAME(TP)+" grasps the handle of the "+short()+" and "+
               "blood begins to fall to the ground.\n");
        FIX_EUID;
        poison = clone_object(GOBLIN_POISON);
        poison->move(TP);
        poison->start_poison();
        return -1;
    }

    if (TP->query_race_name() != "dwarf")
    {
        write("The "+short()+" pulses with an eerie green glow.\n");
        say(QCTNAME(TP)+" tries to wield the "+short()+" but fails as "+
              "the "+short()+" glows with an eerie green glow.\n");
        return -1;
    }
    return 0;
}


public varargs int
did_hit (int aid, string hdesc, int phurt, object enemy, int dt,
      int phit, int dam)
{
    object wielder;

    if ((phurt >= 0) && 
        (enemy->query_race_name() == "goblin"))
    {
        wielder = query_wielded();
        enemy->heal_hp(- ((random(dam/2)) + dam / 3));
        enemy->catch_tell("The "+short()+" pulses green as it "+
                     "connects with your body.\n");
        wielder->catch_tell("The "+short()+" pulses with "+
            "an eerie green glow as it connects with "+
            enemy->query_the_name(wielder) + ".\n");
        wielder->tell_watcher("The "+short()+" pulses green as it connects "+
             "with "+QTNAME(enemy)+".\n", enemy);
    }

    return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

