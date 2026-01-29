inherit "/d/Shire/common/obj/perfume";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"

void
create_perfume()
{
    set_name("cologne");
    add_name("flask");
    add_adj(({"thin","brass","relentless"}));
    set_pname("flasks");
    set_short("thin brass flask");
    set_pshort("thin brass flasks");
    set_long("This flask contains the most powerful masculine "+
	     "scent known to exist. Combining the musk oils of "+
	     "seven different species, it brings out the animal in you! "+
	     "Dabble it on, and relentless will be your scent.\n");

    set_charges(8);
    set_perfume_name("relentless cologne");
    set_perfume_file(BREE_DIR + "obj/relentless");
    
    add_prop(OBJ_I_WEIGHT, 199);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 15);
}

