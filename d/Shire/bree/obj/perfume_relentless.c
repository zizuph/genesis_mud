/*
 * Relentless perfume from Bree
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
    add_name( ({ "flask", "cologne" }) );
    add_name("_shire_perfume_relentless_");
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
    set_perfume_file(OBJ_DIR + "perfume_relentless_scent");
    
    add_prop(OBJ_I_WEIGHT, 199);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 15);
}

