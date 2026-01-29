/* Magical dwarven shield. Acts as a tower shield in the 
 * hands of smaller races. 
 */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

void
create_armour()
{
   set_name("shield");
   set_ac(50);
   set_at(A_SHIELD);
   set_am( ({ 1, 3, 3 }) );
   set_adj("reinforced");
   set_adj("star-metal");
   set_short("reinforced star-metal shield");
   set_long("This is a dwarven shield reinforced with bands of the rare " +
            "material referred to by ancient alchemists as 'star metal' " +
            "- a blue ore of extraordinary strength and hardness. " +
            "In the hands of a dwarf or similar sized race this shield " +
            "would provide the protection of a tower shield.\n");
   add_prop(OBJ_I_VOLUME, 3000);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(50, A_SHIELD));
   add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(50));
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
   add_prop(OBJ_S_WIZINFO,"This is a magical dwarven shield that is " +
              "occasionally worn by the dark dwarf chieftain in the " +
              "Tharkadan mountain range caverns, " +
              "/d/Krynn/tharkadan/living/theiwar_chieftain. It " +
              "provides excellent protection as a tower shield for " +
              "the smaller races. set_likely_cond has also been set " +
              "from 3 to 2, reducing the chance somewhat of it wearing " +
              "down.\n");
   add_prop(MAGIC_AM_ID_INFO,
         ({"This shield has been crafted by the smiths of the " +
             "Theiwar clan out of the rare star metal, and enchanted by " +
             "dark dwarf savants to be armour of exceptional strength " +
             "and durability.\n", 30}));

   set_likely_cond(2);
   set_af(TO);
}

int*
query_shield_slots()
{
    if(TP->query_race_name() != "dwarf" && TP->query_race() != "gnome" &&
       TP->query_race_name() != "goblin" && TP->query_race() != "hobbit")
       return (::query_shield_slots());
    else
       return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );

}

