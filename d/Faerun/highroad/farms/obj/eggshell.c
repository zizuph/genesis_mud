/*
 * eggshell for egg quest
 * By Finwe, August 2006
 */
 
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/object";

void
create_object()
{

    add_adj("broken");
    add_adj("jagged");

    set_name("eggshell");
    add_name("_faerun_eggshell");
    set_short("broken eggshell");
    set_long("This is a "+short()+". It is the remains of a whole egg " +
        "that was crushed accidentally.\n");

    add_prop(OBJ_I_VALUE, 50+random(50));
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_WEIGHT, 500);

}
