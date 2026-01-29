// file name:    ~Avenir/common/dark/obj
// creator(s):    Lilith Nov 2021
// last update:            
// purpose:       The gneiss gnomes have few resources other 
//                than stone, metals, gems, and mushrooms.
//                They make jewelry in their spare time and
//                this is an example. 
// Reviions:
//               Lilith Feb 2022: fixed pshort so it isn't showing wristletses                                        

inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_armour()
{	
    set_short("polished iron wristlets");
    set_pshort("sets of polished iron wristlets");
    set_name("wristlet");
    set_pname("wristlets");
    add_name(({"bracelet", "manacles"}));
    set_adj(({"wide", "iron", "polished", "engraved"}));
    set_long ("This is a set of wide wristlets that are engraved "+
        "with dots and spirals. If they were a bit heavier they "+
        "might pass for manacles. These wristlets were crafted "+
        "by the gniess gnomes.\n");
                                                              
    set_at(A_ANY_WRIST);      
    set_ac(1);
    set_keep(1);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 350);
}
