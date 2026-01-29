/* 
 * chipped ewar
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
    set_name("ewar");
    add_name("_shire_ewar_");
    set_adj("tall");
    set_adj("chipped");
    set_short("tall chipped ewar");
    set_long("This is "+short()+". It was made from white clay, and " +
        "looks elegant. It is tall with a narrow opening. There is a " +
        "flared lip which enables water, wine, or anything to be " +
        "poured from it. An elegant scroll handle is on the side of " +
        "the ewar to allow it to be held. Chips and small marks are " +
        "scattered across the surface of the container.\n");

	add_prop(OBJ_I_WEIGHT, 2000);
//check volumes
	add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 400);
}
