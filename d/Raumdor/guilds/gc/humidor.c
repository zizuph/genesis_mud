// Sarr
//////////////////////////////////////
/* added keepable option, 2003-10-12, Dargoth */

inherit "/std/receptacle";
inherit "/lib/keep";

#include <macros.h>
#include "/d/Raumdor/defs.h"

static mixed check_insert();

void
create_receptacle()
{
    set_name("box");
    set_pname("boxes");
    add_name("humidor");
    add_pname("humidors");
    set_adj( ({"small", "wooden" }));
    set_short("small wooden box");
    set_pshort("small wooden boxes");
    set_long("This is a small humidor made of polished redwood. "+
       "There are intricate designs carved on it, and the box "+
       "is re-enforced with polished brass. It could probably fit "+
       "eight cigars.\n");
    add_item(({"intricate designs", "designs"}),
      "The "+ short() +" is covered in intricate designs "+
      "but there is no special pattern to it.\n");
    add_item(({"brass", "polished brass", "brass fittings", "fittings"}),
      "The polished brass fittings re-enforce the box.\n");
    add_prop(CONT_I_WEIGHT, 50);
    add_prop(CONT_I_VOLUME, 100);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_MAX_WEIGHT, 1000);
    add_prop(CONT_I_MAX_VOLUME, 900);
    add_prop(CONT_M_NO_INS, check_insert);
    add_prop(OBJ_I_VALUE, 825);
}



static mixed
check_insert()
{
    object obj;
    int i = 1;
    while(objectp(obj = previous_object(--i)))
    {
        if(this_object() == obj)
            if(previous_object(i-1)->id("cigar"))
                return 0;
            else
                return "You can only put cigars in there.\n";
    }
    return "You can only put cigars in there.\n";
}
