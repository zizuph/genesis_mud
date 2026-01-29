/* Dwarven shield. Acts as a tower shield in the hands of smaller races */

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
   set_ac(40);
   set_at(A_SHIELD);
   set_am( ({ 1, 3, 3 }) );
   set_adj("reinforced");
   set_adj("steel");
   set_short("reinforced steel shield");
   set_long("This is a dwarven shield reinforced with bands of fine " +
       "steel. In the hands of a dwarf or similar sized race this " +
       "shield would provide the protection of a tower shield.\n");
   add_prop(OBJ_I_VOLUME, 3000);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(40, A_SHIELD));
   add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(40));

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

