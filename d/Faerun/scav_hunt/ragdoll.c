/*
 * Random item for the Scavanger hunt
 * Coded by Finwe September 2003
 * Originally coded for the Shire, cleaned up in October 2015
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    seteuid(getuid());
    set_name("doll");
    set_adj("rag");
    set_adj("dirty");
    set_short("dirty rag doll");
    set_long("This is "+short()+". It is made from twisted rolls of fabric. " +
        "Several rolls make up the arms, legs, and body. The head is " +
        "topped with a frayed strands of yarn. The doll is muddy and " +
        "dirty from lots of use, and in many places, the fabrics are " +
        "frayed.\n");

	add_prop(OBJ_I_WEIGHT, 50);
	add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 400);
}
