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
    set_short("hammered gold anklet");
    set_name("anklet");
    add_name(({"ankle bracelet"}));
    set_adj(({"hammered", "gold"}));
    set_long ("An anklet made of some metal, probably iron, with gold "+
        "hammered into it. It is beautifully done and glitters whenever "+
        "the light catches on the indentations. It was crafted by the "+
		"gneiss gnomes.\n");
                                                              
    set_at(A_ANY_ANKLE);      
    set_ac(1);
    set_keep(1);
    add_prop(OBJ_I_VALUE, 400);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
