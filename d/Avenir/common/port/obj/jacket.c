// file name:   /d/Avenir/common/port/obj/jacket.c
// creator(s):  Boriska Aug 95
// last update:
// purpose:     Armour for ~Avenir/common/port/mon/sailor
// note:
// bug(s):
// to-do:     

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"

inherit "/std/armour";

void
create_armour()
{
    set_name("jacket");
    set_short("seaman's jacket");
    set_adj("seaman's");
    set_long("This worn jacket made of hard cloth should provide good " +
	     "protection against elements.\n");
    set_ac(10);
  
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 1000);
}

