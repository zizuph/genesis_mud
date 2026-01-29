/* ctower/obj/airgem.c is cloned by ctower/air1.c */

inherit "/d/Emerald/ctower/obj/gem_base";

#include <stdproperties.h>
#include <ss_types.h>
 
void
create_gem()
{
    set_name("diamond");
    set_long("This is a crystal clear diamond gem that tingles when held.\n");

    add_prop(OBJ_I_VALUE, 1728);

    config_gem("air", SS_ELEMENT_AIR);
}

void
invoke_msgs()
{
    write("The winds start to pick up speed, but "+
        "just before they reach dangerous levels they stop.\n");
    say("The winds start to pick up speed, but "+
       "just before they reach dangerous levels they stop.\n");
}
