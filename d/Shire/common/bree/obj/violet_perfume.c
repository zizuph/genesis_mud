inherit "/d/Shire/common/obj/perfume";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

void
create_perfume()
{
    set_name("perfume");
    add_name("bottle");
    add_adj(({"tall","purple","voilet"}));
    set_pname("bottles");
    set_short("tall purple bottle");
    set_pshort("tall purple bottles");
    set_long("This is a bottle of the finest violet perfume "+
	     "available. It has been delicately cultivated and "+
	     "aged to ensure an excellent richness and flavor. "+
	     "Its aroma will last a good long time, if you dabble it on.\n");

    set_charges(8);
    set_perfume_name("violet perfume");
    set_perfume_file(BREE_DIR + "obj/violet");
    
    add_prop(OBJ_I_WEIGHT, 199);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 15);
    add_prop(OBJ_M_NO_SELL,1);
}
