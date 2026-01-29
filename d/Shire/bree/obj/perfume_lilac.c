/*
 * Lilac perfume from Bree
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
    add_name("_shire_perfume_lilac_");
    add_adj(({"square","red"}));
    set_pname("bottles");
    set_short("square red bottle");
    set_pshort("square red bottles");
    set_long("This is a bottle of the finest lilac perfume "+
	     "to be found anywhere. This bottle, however has "+
	     "Bree stamped on the bottom. "+
	     "To wear the scent, just dabble it on.\n");
    
    set_charges(10);
    set_perfume_name("lilac perfume");
    set_perfume_file(OBJ_DIR + "perfume_lilac_scent");
    
    add_prop(OBJ_I_WEIGHT, 199);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 15);
    add_prop(OBJ_M_NO_SELL, 1);
}

