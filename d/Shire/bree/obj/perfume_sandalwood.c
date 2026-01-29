/*
 * Sandalwood perfume from Bree
 * Converted and updated by Finwe, October 2005
 */

inherit "/d/Shire/bree/obj/perfume";

#include <stdproperties.h>
#include "/d/Shire/sys/defs.h"
#include "defs.h"

void
create_perfume()
{
    set_name("perfume");
    add_name("bottle");
    add_name("_shire_perfume_sandalwood_");
    add_adj(({"sandalwood","brown"}));
    set_pname("bottles");
    set_short("small brown bottle");
    set_pshort("small brown bottles");
    set_long("This is a bottle of the finest sandalwood perfume "+
	     "available. It has been delicately developed and "+
	     "aged to ensure an excellent richness and flavor. "+
	     "Its aroma will last a good long time, if you dabble it on.\n");
    
    set_charges(4);
    set_perfume_name("sandalwood perfume");
    set_perfume_file(OBJ_DIR + "perfume_sandalwood_scent");
    
    add_prop(OBJ_I_WEIGHT, 199);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 15);
    add_prop(OBJ_M_NO_SELL,1);
}
