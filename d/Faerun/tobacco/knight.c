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
    set_short("knight tobacco");
    add_name("tobacco");
    add_name("leaf");
    add_name("knight");
    add_name("knight tobacco");
    set_adj("knight");
    set_long("This is Knight tobacco. It is made from a blend of light " +
        "and dark leaves. The aroma is strong and smells like incense.\n");
   
    add_prop(OBJ_I_VALUE,(36 + random(14)));
}

string
query_flavour()
{
    return "incense flavored";
}