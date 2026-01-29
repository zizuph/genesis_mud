/*
 *      Updates:
 *       Zizuph, 2021-12-25:
 *         Turn into a spell enhancer, power 30.
*/
#include "/d/Ansalon/common/defs.h"
inherit "/std/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define WEAPON_HIT 32
#define WEAPON_PEN 28

void
create_weapon()
{
   set_name("dagger");
   set_pname("daggers");
   add_pname("weapons");
   set_adj("blackened-steel");
   set_short("blackened-steel dagger");
   set_pshort("blackened-steel daggers");
   set_long(break_string("Over a foot long, this " +
         "blackened-steel dagger is carved into the shape of " +
         "a sinister looking dragon, hence it is often referred to " +
         "as the dagger of Draco. The pommel of the dagger is " +
         "wrapped in serpent skin, and its edges are extremely sharp. " +
         "It seems quite a deadly weapon.",75) + "\n");
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(MAGIC_AM_MAGIC,({ 50, "enchantment"}));
   add_prop(MAGIC_AM_ID_INFO,({"This dagger has " +
            "been enchanted by evil priests of Takhisis so as " +
            "to pierce the hardest of armours with ease. More than " +
            "one noble knight has underestimated this blade, falling " +
            "prey to its magical enchantments. \n",15}));
   
   set_hit(WEAPON_HIT);
   set_pen(WEAPON_PEN);
   set_wt(W_KNIFE);
   set_dt(W_IMPALE | W_SLASH);
   set_hands(W_ANYH);
   set_wf(TO);
   
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN));
   
    // This value will affect spell damage for spellcasters.
    set_magic_spellpower(30);       
}

mixed
wield(object what)
{
   return 0;
}

mixed
unwield(object what)
{
   if ((E(TO)->id("gakhan")) && (E(TO)->query_hp() > 0))
      {
      tell_room(E(E(TO)), "The " + short() + " stays firmly in "
         + "the hand of " + QCTNAME(E(TO)) + ".\n", E(TO));
      
      return "No!\n";
   }
   
   return 0;
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
