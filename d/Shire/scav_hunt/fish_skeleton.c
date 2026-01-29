/* 
 * Fish skeleton
 * -- Finwe, September 2003
 */
  
inherit "/std/object";
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    seteuid(getuid());
    set_name("skeleton");
    add_name("_shire_fish_skeleton_");
    set_adj("fish");
    set_adj("dirty");
    set_short("dirty fish skeleton");
    set_long("This is "+short()+". It is dried and hideous looking, " +
        "with lots of teeth marks on it, with all the flesh picked " +
        "from the bones. The skeleton is quite large, but many of " +
        "the bones are broken.\n");

	add_prop(OBJ_I_WEIGHT, 50);
//check volumes
	add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 400);
}
