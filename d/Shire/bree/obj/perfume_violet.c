/*
 * Violet perfume from Bree
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
    add_name("_shire_perfume_violot_");
    add_adj(({"tall","purple","violet"}));
    set_pname("bottles");
    set_short("tall purple bottle");
    set_pshort("tall purple bottles");
    set_long("This is a bottle of the finest violet perfume "+
	     "available. It has been delicately cultivated and "+
	     "aged to ensure an excellent richness and flavor. "+
	     "Its aroma will last a good long time, if you dabble it on.\n");

    set_charges(8);
    set_perfume_name("violet perfume");
    set_perfume_file(OBJ_DIR + "perfume_violet_scent");
    
    add_prop(OBJ_I_WEIGHT, 199);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 15);
    add_prop(OBJ_M_NO_SELL,1);
}
