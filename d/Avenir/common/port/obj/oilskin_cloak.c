// file name:   /d/Avenir/common/port/obj/oilskin_cloak.c
// creator(s):  Ibun Mars 04
// last update:
// purpose:     Armour for ~Avenir/common/port/mon/sailor
// note:        The cloak prevent the wearer from beeing grabbed and 
// not e:       entangeled by the octopus
// bug(s):
// to-do:     

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"

inherit "/std/armour";

void
create_armour()
{
    set_name("cloak");
    set_name("_oilskin_cloak_");
    set_short("oilskin cloak");
    set_adj("oilskin");
    set_long("This is a seamans cloak, made by some slippery " +
            "material that protects the wearer from water. When " +
            "you take the cloak between your fingers you " +
            "have problems getting a good grip because of its " +
            "slippery fabric.\n");
    set_at(A_ROBE);
    set_ac(10);
  
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
}

