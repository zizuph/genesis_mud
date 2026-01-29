inherit "/std/object";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>
#include <macros.h>
/* by Antharanos */

create_object()
{
    set_short("puddle of gore");
    set_pshort("puddles of gore");
    set_name("gore");
    add_name("puddle");
    set_long("A puddle of human blood with bits and pieces of flesh.\n");
    add_prop(OBJ_I_WEIGHT,300);
    add_prop(OBJ_I_VOLUME,300);
    add_prop(OBJ_I_NO_GET,"You can't pick that up! Its spread all over the floor!\n");
}
