// file name:    ~Avenir/common/dark/obj/earring.c
// creator(s):    Lilith Nov 2021
// last update:            
// purpose:       The gneiss gnomes make these to wear
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
		
    set_short("cluster of small silver rings");
    set_name("earring");
    add_name(({"cluster", "earrings", "rings"}));
    set_adj(({"small","silver"}));
    set_long("A cluster of silver rings all worn together on one "+
        "ear. They collide against each other when worn, making "+
        "pleasant tinkling sounds when you move. This piece of "+
		"jewelry was crafted by the gneiss gnomes, who honed their "+
		"art in isolation.\n");
                            
    set_at(A_ANY_EAR);      
    set_ac(1);
    set_keep(1);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}

