inherit "/d/Shire/common/obj/perfume";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

void
create_perfume()
{
    set_name("perfume");
    add_name("bottle");
    add_adj(({"sandalwood","brown"}));
    set_pname("bottles");
    set_short("brown bottle");
    set_pshort("brown bottles");
    set_long("This is a bottle of the finest sandalwood perfume "+
	     "available. It has been delicately developed and "+
	     "aged to ensure an excellent richness and flavor. "+
	     "Its aroma will last a good long time, if you dabble it on.\n");
    
    set_charges(4);
    set_perfume_name("sandalwood perfume");
    set_perfume_file(BREE_DIR + "obj/sandalwood");
    
    add_prop(OBJ_I_WEIGHT, 199);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 15);
    
    add_prop(OBJ_M_NO_SELL,1);
}
