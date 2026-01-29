/***************************************************************
 * Name: Bone-handled waraxe.                                  *
 * Found: Mithas Forest.                                       *
 * By: Elmore.                                                 *
 * Date: 19/3-2001                                             *
 * Description: A very strange axe :) It doesn't really do     *
 * much damage, but it has an ability that improves the longer *
 * you wield the axe. This ability adds X speed to the player, *
 * where X <= 300.                                             *
 * Restricted to: 3 pr Armageddon.                             *
 * Cotillion 2015-02-14:    LIVE_I_QUICKNESS MAX 300 -> 100    *
 ***************************************************************/

inherit "/std/weapon";
inherit "/lib/keep";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include <options.h>
#include <ss_types.h>
#include <filter_funs.h>
#include "/d/Ansalon/common/defs.h"

#define WEAPON_HIT 35
#define WEAPON_PEN 15
#define QUICKNESS_MAX 100

object wielder;
int speed_power;

void
create_weapon()
{
    set_name("waraxe");
    add_name("axe");
    set_adj("bone-handled");
    set_short("bone-handled waraxe");
    set_long("This strange axe has a circular blade connected to a long bone handle. "+
             "The handle itself has been wrapped with a thick skin from a boar, and this "+
             "gives the wielder a very good grip around the axe. The circular blade is "+
             "completely flawless and smoothe, however it seems to be a bit dull.\n");

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_wt(W_AXE);
    set_likely_dull(0);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    set_wf(TO);
    add_prop(OBJ_M_NO_SELL,"The shopkeeper backs away from you "+
        "as you try to sell the axe, he obviously doesn't want to "+
        "buy it.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({30,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This strange weapon was forged "+
       "by a troll blacksmith and enchanted by the shamans in his "+
       "village. This weapon has the ability to give the wielder "+
       "immense speed, if he has the patience to keep wielding it.\n",1}));

    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 3400);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN));
}


mixed
wield(object what)
{
    speed_power = 0;
    return 0;
}

mixed
unwield()
{
    wielder->change_prop(LIVE_I_QUICKNESS,wielder->query_prop(LIVE_I_QUICKNESS)-speed_power);
    return 0;
}

public mixed
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
  if(!random(10))
  {
    if(phurt > 0)
    {
      if (speed_power <= QUICKNESS_MAX)
      {
        wielder->catch_msg("Your "+short()+" hums briefly.\n");
        wielder->change_prop(LIVE_I_QUICKNESS,wielder->query_prop(LIVE_I_QUICKNESS)-speed_power);
        speed_power = min(speed_power + (random(10)+5), QUICKNESS_MAX);
        wielder->change_prop(LIVE_I_QUICKNESS,wielder->query_prop(LIVE_I_QUICKNESS)+speed_power);
      }
    }
  }
  return ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);
}

