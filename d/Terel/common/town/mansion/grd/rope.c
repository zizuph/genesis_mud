/*
 * An example rope
 *
 * By Nick
 */

inherit "/std/object";
#include "/d/Terel/common/terel_std_rec.h"
#include <stdproperties.h>

create_object()
{
    set_name("rope");
    set_adj("brown");
    set_long("A frayed brown rope.\n");
    add_prop(OBJ_I_VALUE, 25);
}

