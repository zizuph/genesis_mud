inherit "/d/Shire/common/obj/perfume";

#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

void
create_perfume()
{
    set_name("perfume");
    add_name("bottle");
    add_adj(({"round","clear"}));
    set_pname("bottles");
    set_short("round clear bottle");
    set_pshort("round clear bottles");
    set_long("This is a bottle of sweet wildflowers perfume. "+
	     "The liquid is clear an the bottle has a stamp on the " +
         "bottom that says Bree. To wear the scent, just dabble " +
         "it on.\n");
    
    set_charges(10);
    set_perfume_name("wildflower perfume");
    set_perfume_file(BREE_DIR + "obj/wildflower");
    
    add_prop(OBJ_I_WEIGHT, 199);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 15);
    add_prop(OBJ_M_NO_SELL, 1);
}

