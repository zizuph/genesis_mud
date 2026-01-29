/*
 * honeysuckle perfume from Bree
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
    add_name("_shire_perfume_honeysuckle_");
    add_adj(({"round","clear"}));
    set_pname("bottles");
    set_short("round clear bottle");
    set_pshort("round clear bottles");
    set_long("This is a bottle of sweet honeysuckle perfume. "+
	     "The liquid is clear an the bottle has a stamp on the " +
         "bottom that says Bree. To wear the scent, just dabble " +
         "it on.\n");
    
    set_charges(10);
    set_perfume_name("honeysuckle perfume");
    set_perfume_file(OBJ_DIR + "perfume_honeysuckle_scent");
    
    add_prop(OBJ_I_WEIGHT, 199);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 15);
    add_prop(OBJ_M_NO_SELL, 1);
}

