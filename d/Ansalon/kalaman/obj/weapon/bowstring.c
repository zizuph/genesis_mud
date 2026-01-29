
inherit "/std/bowstring";
inherit "/lib/keep";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"


string
query_auto_load()
{
    return MASTER_OB(TO) + ":";
}

public string
query_recover()
{
    return 0;
}
