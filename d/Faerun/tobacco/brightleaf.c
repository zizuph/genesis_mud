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
    set_short("brightleaf tobacco");
    add_name("tobacco");
    add_name("leaf");
    add_name("brightleaf");
    add_name("brightleaf tobacco");
    set_adj("brightleaf");
    set_long("This is Brightleaf tobacco. It has been fire cured and " +
        "smells slightly sweet.\n");
   
    add_prop(OBJ_I_VALUE,(36 + random(14)));
}

string
query_flavour()
{

//   return "longbottom leaf";
    return "sweet flavored";
}