inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void
create_armour()
{
    set_name("cloak");
    set_short("brown cloak");
    set_long("This is a dark brown, standard military issue cloak. It is made "+
             "of a heavier weave of wool to ward the soldiers against the "+
             "harsh elements. It looks like it could provide needed warmth "+
             "in the cold winds.\n");
    set_adj("brown");

    set_default_armour(8, A_ROBE,  30,  30);
    add_prop(OBJ_I_WEIGHT, 546); 
    add_prop(OBJ_I_VOLUME,  341); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8) + random(60) - 43);
   }

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
