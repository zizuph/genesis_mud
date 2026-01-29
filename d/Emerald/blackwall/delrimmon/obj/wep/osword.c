/*
 *  /d/Emerald/blackwall/delrimmon/obj/wep/osword.c
 *
 *  This is the Onyx Sword, one of the favorite weapons of Emerald's
 *  past. It is one of the various weapons wielded by the orc
 *  captain at Del Rimmon.
 *
 *  Slight modifications to bring up to standards:
 *    Gorboth - September 2001
 *
 *  Added OBJ_I_IS_MAGIC_WEAPON - Malus 2017-10-27
 *  Made into spell enhancer - Ckrik 2022-02-06
 */
#pragma strict_types
inherit "/std/weapon";
inherit "/lib/keep";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>


public mixed        steal_check();

/* 
 * Function name:        create_weapon
 * Description  :        set up the weapon
 */ 
public void
create_weapon()
{
   set_name("sword");
   set_short("onyx sword");
   set_long("This glittering black sword, is made of a magical "+
      "material found only in a few places in the world, onyx. "+
      "It's glittering black blade twinkles like the night sky.\n");
   set_adj("onyx");
   
   set_default_weapon(40, 50, W_SWORD, W_SLASH | W_IMPALE,  
      W_RIGHT,  this_object());
   // This value will affect spell damage for spellcasters.
   set_magic_spellpower(40);
   set_spellpower_elements(({
      SS_ELEMENT_DEATH, SS_ELEMENT_EARTH
   }));
   add_prop(OBJ_M_NO_STEAL, steal_check);
   add_prop(OBJ_I_WEIGHT, 13560); 
   add_prop(OBJ_I_VOLUME,  1100); 
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(40, 50) + random(123) + 57);
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1); 
} /* create_weapon */


/*
 * Function name:        wield
 * Description  :        we only allow players with sufficient
 *                       sword skill to wield this weapon
 * Arguments    :        object wep - this object
 * Returns      :        -1 : cannot wield
 *                        0 : okay to wield
 */
public int
wield(object wep)
{
   if(this_player()->query_skill(SS_WEP_SWORD) < 70)
      {
      write("Something within the sword resists you.\n");
      return -1;
   }
   return 0;
} /* wield */



/*
 * Function name:        steal_check
 * Description  :        this sword cannot be stolen from Akugla
 * Returns      :        string - can't steal msg, 0 - can steal
 */
public mixed
steal_check()
{
    if (environment(this_object())->id("del_rimmon_akugla"))
    {
        return "As you reach for the weapon, the fearsome orc"
          + " captain turns upon you and with a single glance,"
          + " stops you cold.\n";
    }

    return 0;
} /* steal_check */

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
    init_keep_recover(arg);
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}
