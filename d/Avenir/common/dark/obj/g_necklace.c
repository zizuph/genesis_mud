// file name:    ~Avenir/common/dark/obj
// creator(s):    Lilith Nov 2021
// last update:            
// purpose:       The gneiss gnomes have few resources other 
//                than stone, metals, gems, and mushrooms.
//                They make jewelry in their spare time and
//                this is an example. 
// note:                   
// bug(s):                 
// to-do:                                           

inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_armour()
{	
    set_short("red garnet on a gold chain");
    set_name("necklace");
    add_name(({"chain", }));
    set_adj(({"garnet", "gold"}));
    set_long ("This is a large garnet. It is still mostly raw and "+
        "unpolished, but there is a faceted section that captures "+
        "the light and directs it inwards, toward the reddish heart "+
        "of the gemstone. The chain is fairly short, which means the "+
		"garnet lies in the hollow at the base of the throat. "+
		"It was crafted by the gniess gnomes.\n");
                                                              
    set_at(A_NECK);      
    set_ac(1);
    set_keep(1);
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 250);
}
