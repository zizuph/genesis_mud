/* Magical dwarven fullplate. Larger races cannot wear it. */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

void
create_armour()
{
   set_name("fullplate");
   add_name("_theiwar_magic_fullplate");
   set_ac(50);
   set_at(A_TORSO | A_ARMS | A_LEGS);
   set_am( ({ -2, 3, 0 }) );
   set_adj("runed");
   add_adj("dwarven");
   add_adj("metal");
   set_short("runed dwarven fullplate");
   set_long("This is a suit of beautifully crafted fullplate, made from " +
       "rare blue ore referred to as 'star-metal' by ancient alchemists " +
       "- a metal of extraordinary strength and hardness. Dwarven runes " +
       "have been carved over the armour that pulse with a dark " +
       "energy.\n");
   add_prop(OBJ_I_VOLUME, 10000);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(50, A_TORSO) + 
                          F_WEIGHT_DEFAULT_ARMOUR(50, A_ARMS) + 
                          F_WEIGHT_DEFAULT_ARMOUR(50, A_LEGS));
   add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(53) * 3));

   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
   add_prop(OBJ_S_WIZINFO,"This is a magical fullplate that is " +
       "occasionally worn by the dark dwarf chieftain in the Tharkadan " +
       "mountain range caverns, " +
       "/d/Krynn/tharkadan/living/theiwar_chieftain. " +
       "It provides excellent magical protection, however can only be " +
       "worn by the smaller races. Those smaller races that aren't " +
       "dwarves get an AC penalty as it doesn't quite fit them " +
       "perfectly. Being fullplate, it is quite heavy - weighing " +
       "around 30 kilograms. set_likely_cond has also been set from " +
       "3 to 2, reducing the chance somewhat of it wearing down.\n");
   add_prop(MAGIC_AM_ID_INFO,
       ({"This dwarven fullplate is enchanted with dark magicks of " +
       "protection, making it formidable armour to breach. The magic " +
       "also makes it less likely for the fullplate to be worn down " +
       "with use.\n", 30}));

   set_likely_cond(2);
   set_af(TO);

}

mixed
wear(object what)
{
    if(TP->query_race_name() != "dwarf" && TP->query_race() != "gnome" &&
       TP->query_race_name() != "goblin" && TP->query_race() != "hobbit")
	return "The dwarven fullplate is designed to fit a dwarf. You " +
           "are too big to wear this armour.\n";

    if(TP->query_race_name() != "dwarf")
    {
       write("Being designed for a dwarf, the fullplate doesn't quite " +
           "fit you perfectly.\n");
       set_ac(42);
       TP->update_armour(TO);
    }
    else
    {
       write("Being designed for a dwarf, the fullplate armour fits you " +
           "perfectly!\n");
       set_ac(50);
       TP->update_armour(TO);
    }

    return 0;
}
