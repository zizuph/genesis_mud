
inherit "/std/object";

#include "/d/Avenir/common/common.h"

#define BEAST_HORN  "_beast_horn"

void
create_object()
{
    set_name("horn");
    add_name("beast horn");
    add_name(BEAST_HORN);
    set_adj("ivory");
    add_adj(({"ivory", "spiral", "creamy", "broken"}));
    set_short("horn of the beast");
    set_pshort("horns of the beast");

    set_long("This horn broke off the sinister beast during combat. It "+
        "is as long as your hand and the creamy colour of ivory. It is "+
        "ridged with a single spiral that starts at the base and goes "+
        "all the way to the narrow point at its tip.\n");

    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VALUE,  2000);
}

string
query_recover()
{
    return MASTER;
}

string
query_auto_load()
{
    return MASTER;
}