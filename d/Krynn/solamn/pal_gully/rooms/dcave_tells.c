#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
string
get_tells()
{
    string cavtell;
    cavtell = one_of_list(({"You hear the trickle of oil refilling "
    +"the lanterns.",
      "Loud cursing can be heard in the distance.",
      "A dewar dwarf rushes past carrying an aghar prisoner.",
      "A crashing noise can be heard in the distance.",
      "Shouting erupts in the distance.",
      "You hear someone pleading in the distance and then it cuts off.", 
      "A dewar dwarf walks past you carrying a sack dripping with blood."}));
    return cavtell;
}