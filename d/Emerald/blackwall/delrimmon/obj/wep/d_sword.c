/*
 *  /d/Emerald/blackwall/delrimmon/obj/wep/d_sword.c
 *
 *  This is one of the weapons from the very old Emerald domain. I
 *  have included it in a list of such weapons which are wielded at
 *  random by the orc captain in the caves at Del Rimmon. I figure
 *  that these weapons, while pretty lame, will warm a few old players
 *  hearts, and that isn't such a bad thing.
 *
 *  Resurrected by Gorboth - Fall 2001. Original Coder unknown.
 */
inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>

#define TP this_player()

public mixed        steal_check();


void
create_weapon()
{
   set_name("katana");
   set_short("sardonyx katana");
   add_name( ({ "sword" }) );
   set_long(break_string("The curved surface of this beautiful blade "+
        "is synonymous with a katana, the perfect blade of the warrior. "+
        "This one has no markings on its surface and it completely "+
        "black, made of sardonyx, one of the rarest materials to find "+
        "in the world.\n", 76));
   set_adj("sardonyx");
   
   set_default_weapon(44, 52, W_SWORD, W_SLASH | W_IMPALE,  
      W_LEFT,  this_object());
   add_prop(OBJ_I_WEIGHT, 14560); 
   add_prop(OBJ_I_VOLUME,  1600); 
    add_prop(OBJ_M_NO_STEAL, steal_check);
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(44, 52) + random(137) + 41);

   add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO, ({ "A " +
        "glittering black blade, curved slightly is this weapon of "+
        "warriors. No mark adorns it, nor rune, yet you feel that a "+
       "magical presence is within.\n", 10 }));
   add_prop(OBJ_S_WIZINFO, 
        "This sword was originally wielded by the daemonlord in the"
      + " old Emerald mines. It is one of the most famous weapons"
      + " in the history of Genesis, but didn't see the light of day"
      + " for about 5 years. I've brought it back with the new"
      + " Emerald, but only randomly. - Gorboth.\n");
}

public int
wield(object wep)
{
   if(TP->query_skill(SS_WEP_SWORD) < 70)
      {
      write("The sword stings you a little, you cannot wield it.\n");
      TP->heal_hp(-50);
      return -1;
   }
   return 0;
}


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
