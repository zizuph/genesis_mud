/* 
 * Rag doll
 * -- Finwe, September 2003
 */
  
inherit "/std/object";
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("doll");
    set_adj("rag");
    set_adj("dirty");
    set_short("dirty rag doll");
    set_long("This is "+short()+". It is made from twisted rolls of fabric. " +
        "Several rolls make up the arms, legs, and body. The head is " +
        "topped with a frayed strands of yarn. The doll is muddy and " +
        "dirty from lots of use, and in many places, the fabrics are " +
        "frayed and ready to rip apart.\n");

	add_prop(OBJ_I_WEIGHT, 50);
//check volumes
	add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 400);
}
