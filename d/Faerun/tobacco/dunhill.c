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
    set_short("dunhill tobacco");
    add_name("tobacco");
    add_name("dunhill");
    add_name("leaf");
    add_name("dunhill tobacco");
    set_adj("dunhill");
    add_name("dunhill tobacco");
    set_long("This is some Dunhill tobacco. It is made from a blend of " +
        "medium brown and dark leaves. The leaves are shredded and " +
        "have a dark, sweet and peppery aroma.\n");
   
    add_prop(OBJ_I_VALUE,(36 + random(14)));
}

string
query_flavour()
{
    return "dark, sweet, and peppery flavored";
}