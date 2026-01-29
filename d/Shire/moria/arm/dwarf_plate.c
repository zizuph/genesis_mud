//   Added keepability functionality   -Igneous

#include "defs.h"

inherit BASE_ARMOUR;
inherit "/lib/keep";

#include <wa_types.h>

CONSTRUCT_ARMOUR
{
   set_name(({"armour", "fullplate", "plate"}));
   set_short("dwarven fullplate");
   set_adj(({"dwarven", "full"}));
   set_long(
      "You are looking at a magnificient dwarven fullplate. " +
      "It seems to be made of perfect steel plates, adorned " +
      "with the typical ornaments of beasts and dragons, while " +
      "yet remaining practical.\n" +
      "   The fullplate is actually a full plate. It consists " +
      "of leg protection, arm protection and body protection. " +
      "In addition, the helmet stands upon its shoulders, whereby " +
      "protecting your whole body.\n" +
      "   Needless to say, dwarven - and specially from Khazad - " +
      "design of armours are known to stand up against the most " +
      "worthy foe. You notice that whereas normal elven and human " +
      "armours use different parts upon a chain mail coat " +
      "to provide flexibility and maneuverability, this armour " +
      "is designed to be in one piece consisting only of interlocking " +
      "pieces, sliding on some materials - soft and rubbery - yet " +
      "looking very strong.\n" +
      "   I would guess that you would have to remove all other armours " +
      "to wear this one, but the total protection against arms and " +
      "deadly fire would be quite some.\n");
   
   set_ac(25);
   set_at(A_BODY | A_ARMS | A_LEGS | A_HEAD);
   
   add_prop(OBJ_I_WEIGHT, 35000);
   add_prop(OBJ_I_VALUE, 3*12*12);
   add_prop(OBJ_I_VOLUME, 10000);
}

string
query_recover()
{
   return MASTER+":"+ query_arm_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
   init_arm_recover(arg);
   
   init_keep_recover(arg);
}
