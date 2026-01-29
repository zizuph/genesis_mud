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
    set_short("rattray tobacco");
    add_name("tobacco");
    add_name("leaf");
    add_name("rattray");
    add_name("rattray tobacco");
    set_adj("rattray");
    set_long("This is some Rattray tobacco. It is a blend of nut-brown " +
        "and golden colored tobacco leaves. It is cut into flakes and " +
        "smells like honey and grass.\n");
   
    add_prop(OBJ_I_VALUE,(36 + random(14)));
}

string
query_flavour()
{
    return "honey flavored";
}