/*  A large gem */

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_object()
{
    set_name("ruby");
    set_adj(({"large","red","eggshaped"}));
    set_long("Large red eggshaped gem.\n");
    add_prop(OBJ_I_VALUE, random(500)+1200);
}

