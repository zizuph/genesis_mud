inherit "/std/container";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>

object food;

create_container()
{
    seteuid(getuid(TO));
    set_name("tree");
     set_adj(({"lovely","apple"}));
    set_pshort("trees");
    set_long("This is one of the many beautiful trees in Shire. Old and proud "
    	    +"where is stands, with green leaves and strong thick branches. Trees here "
    	    +"are usually full of apples at this time of year, but this looks like "
    	    +"one that recently have been harvested. Not a single tiny bit of apple left.\n");
    	    
    add_prop(CONT_I_VOLUME, 4000000);
    add_prop(CONT_I_WEIGHT, 5000000); 
    add_prop(CONT_I_MAX_VOLUME, 1200*1000);
    add_prop(CONT_I_MAX_WEIGHT, 1000*1000);
    add_prop(OBJ_M_NO_GET,1);
    add_prop(OBJ_M_NO_GIVE,1);    
    food = clone_object(BREE_DIR + "obj/fruit");
    food->move(TO);
}
    
