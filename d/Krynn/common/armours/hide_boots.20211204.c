/* 
 * File: hide_boots.c
 * Red dragon-hide boots, with a kicking special. :)
 *
 * Blizzard, 8.06.2003
 * Cotillion, 2004-10-13
 * - Fixed ::got_hit call.
 */

/* Navarre Feb 2007, changed to use F_WIGHT_DEFAULT_ARMOUR and F_VALUE_ARMOUR */

#pragma strict_types

inherit "/std/armour.c";
inherit "/lib/keep";

#include <formulas.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Krynn/common/defs.h"

int                ready_to_kick = 1;  // We are redy to kick at start! ;)
object             wearer;
private string     color = "uncolored";   // default.

public string      query_color();

public void
create_armour()
{
    set_name("boots");
    add_name("armour");
    set_adj("dragon-hide");
    add_adj(query_color());
    add_adj(({ "pair", "of" }));
    set_short("pair of @@query_color@@ dragon-hide boots");
    set_long("This is a pair of skillfully crafted boots, made from the " +
        "@@query_color@@ hide of a dragon. They come up almost to the " +
        "knee and are warm to the touch. Built for protection they are also " +
        "form-fitting and very comfortable.\n");
    set_default_armour(28, A_LEGS | A_ANKLES | A_FEET, (({ -1, 1, 0})), 0);
  
    set_af(TO);
    set_keep(1);
    
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }) );
    add_prop(MAGIC_AM_ID_INFO, ({
        "These boots have been made of the dragon hide and they " +
        "provide good protection to the wearer.\n", 10,
        "The dragon hide offers some protecton against fire.\n", 40,
        "If you know how to kick your enemies, you may find this pair " +
        "of boots to be helpful in combat.\n", 70 }) );
    add_prop(OBJ_S_WIZINFO, "The pair of boots made from the " + color + 
        " dragon hide. They have been enchanted and from time to time, " +
        "depending on the SS_UNARM_COMBAT of the wearer, will make him " +
        "kick his enemy. This will work only the ther UNARMED_COMBAT_OFF " +
        "option has been disabled. The boots will provide also a little " +
        "protection agaist fire to the wearer ( 15 ).\n");
        
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(28, A_LEGS));  
    add_prop(OBJ_I_VOLUME, 450);  
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(28));

}

public void
set_color(string new_color)
{
    remove_adj(color);
    color = new_color;
    set_short(0);
    set_adj(color);
    set_short("pair of " + color + " dragon-hide boots");
}

public string
query_color()
{
    if ( color != "uncolored" )
        return color;
    else
        return "uncolored";
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + color;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_color(a[1]);
    init_arm_recover(a[0]);
}

public void
ready_again()
{
    ready_to_kick = 1;   
}

public int
query_ready()
{
    return ready_to_kick;
}

public int
got_hit(int hid, int phurt, object attacker, int dt, int dam)
{
    int      penet, time;
    mixed    hitres;
    string   how_hard;

    ::got_hit(hid, phurt, attacker, dt, dam);
    
    wearer = TO->query_worn();
    
    if (wearer->query_option(OPT_UNARMED_OFF))
        return 0;               // We do not want to kick!
        
    if ( dt != 0 )              // We did not dodge.
        return 0;
        
    if ( hid != A_LEGS )        // Works only if the legs are hit...
        return 0;

    if ( ready_to_kick == 0 )   // We are not ready to kick.
        return 0;

 /* The special will not work while the wearer is mounted... */
    if ( wearer->query_steed() )
        return 0;
        
 /* ...but it will not work if the attacker is mounted, either. */   
    if ( attacker->query_steed() )
        return 0;
    
    penet = 100 + wearer->query_skill(SS_UNARM_COMBAT);
        
    hitres = attacker->hit_me(penet, W_BLUDGEON, wearer, -1);

    if(typeof(hitres) != T_ARRAY)
    {
      how_hard = "weak";
    }
    else
    {
      if (hitres[0] < 0)
          hitres[0] = 0;
      
      switch ( hitres[0] )
      {
          case 0..5:
              how_hard = "weak";
              break;
          case 6..30:
              how_hard = "hard";
              break;
          case 31..70:
              how_hard = "devastating";
              break;
          default:
              how_hard = "bone crushing";
      }
    }
    
    if(wearer && attacker)
    {
      wearer->catch_msg("You make a sudden dodge and skillfully deliver a " + 
        how_hard + " kick into the legs of " + QTNAME(attacker) + ".\n");
      attacker->catch_msg(QCTNAME(wearer) + " makes a sudden dodge and " +
        "skillfully delivers a " + how_hard + " kick into your legs.\n");
      wearer->tell_watcher(QCTNAME(wearer) + " makes a sudden dodge and " +
        "skillfully delivers a " + how_hard + " kick into the legs of " + 
        QTNAME(attacker) + ".\n", attacker);
        
            
      if ( attacker->query_hp() <= 0 )
      {
        wearer->catch_msg(QCTNAME(attacker) + " seems to be unable to keep " +
            HIS(attacker) + " footing and collapses to the ground.\n");
        attacker->catch_msg("You collapse to the ground, as you " +
            "are unable to keep your footing.\n");
        wearer->tell_watcher(QCTNAME(attacker) + " seems to be unable to " +
            "keep " + HIS(attacker) + " footing and collapses to the " +
            "ground.\n");
             
        attacker->do_die(wearer);
      }
      time = 15 + random(40 - (wearer->query_skill(SS_UNARM_COMBAT) / 5));
    }
    else
    {
      time = 15 + random(40);
    }    

    ready_to_kick = 0;

    set_alarm(itof(time), 0.0, &ready_again());
            
    return 1;    
}

varargs mixed
query_magic_protection(string prop, object what)
{
    if ( what == query_worn() && prop == MAGIC_I_RES_FIRE )
        return ({ 10, 1 });
        
    return ::query_magic_protection(prop, what);
}

public mixed
wear(object ob)
{
    TP->catch_msg("You slip your feet into the " + short() + ". They feel " +
        "very comfortable.\n");
    tell_room(E(TP), QCTNAME(TP) + " slips " + HIS(TP) + " feet into the " +
        short() + ".\n", TP);

    TP->add_magic_effect(TO);

    return 1;
}

public int
remove(object ob)
{
    query_worn()->remove_magic_effect(TO);
    return 0;
}
