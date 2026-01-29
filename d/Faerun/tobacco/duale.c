/*
 * Faerun Tobacco
 * Based on the tobaccos from the Shire
 * -- Finwe, November 2015
 *
 * Updated by Shanoga, 20200921
 *   Added value so that it can be smoked
 *   Value is 25% of cost + random(10%) for variation
 */

inherit "/d/Faerun/tobacco/base_tobacco.c";

#include "/d/Faerun/defs.h"

void
create_object()
{
    ::create_object();
    set_short("duale tobacco");
    add_name("tobacco");
    add_name("leaf");
    add_name("duale");
    add_name("duale tobacco");
    set_adj("duale");
    set_long("This is Duale tobacco. The leaves are a light brown. They " +
        "were air cured then finely shredded. The tobacco has a light " +
        "earthy smell.\n");
   
    add_prop(OBJ_I_VALUE,(36 + random(14)));
}

string
query_flavour()
{
    return "light, earthy, flavored";
}