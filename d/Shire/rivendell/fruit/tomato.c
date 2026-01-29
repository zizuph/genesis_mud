/*
 * Vegetables from Garden
 * Coded by Finwe, February 1998
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"
 
 
create_food()
{
    set_name("tomato");
    set_pname("tomatoes");
    set_pshort("tomatoes");
    set_adj(({"large", "ripe"}));
    set_short("large ripe tomato");
    set_long("This large ripe tomato looks like it is bursting " +
        "with flavor. It is one of the largest tomatoes you " +
        "have ever seen.\n");
    add_name("fruit");
    set_amount(150);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 150);
}                             
