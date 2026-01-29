inherit "/d/Shire/common/obj/perfume";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

void
create_perfume()
{
    set_name("perfume");
    add_name("bottle");
    add_adj(({"small","black","outrageous"}));
    set_pname("bottles");
    set_short("small black bottle");
    set_pshort("small black bottles");
    set_long("This is a bottle of the finest blend of scents "+
	     "available. It has been delicately cultivated and "+
	     "aged to ensure an excellent richness and flavor. "+
	     "Its aroma will last a good long time, if you dabble it on.\n");

    set_charges(3);
    set_perfume_name("outrageous perfume",
		     "expensive-smelling perfume");
    set_perfume_file(BREE_DIR + "obj/outrageous");

    add_prop(OBJ_I_WEIGHT, 199);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 15);
    
    add_prop(OBJ_M_NO_SELL,1);
}
