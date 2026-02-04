/*  A small gem */

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_object()
{
    set_name("gem");
    set_adj(({"small","turqoise","oval"}));
    set_long("Small turqoise oval gem.\n");
    add_prop(OBJ_I_VALUE, random(100)+200);
}

