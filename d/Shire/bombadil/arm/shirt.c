/*
 * Tom Bombadill's Shirt
 * By Finwe, January 2002
 */

inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void
create_armour()
{
    set_name("shirt");
    set_short("bright orange shirt");
    add_adj("bright");
    add_adj("orange");
    set_long("This is a bright orange shirt. Its quality is very " +
        "good and looks like it was once owned by a happy fellow. \n");
    set_ac(4);
    set_am(({2,1,1,}));
    set_at(A_BODY);
   
    add_prop(OBJ_I_VALUE, 9);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 100);
}
