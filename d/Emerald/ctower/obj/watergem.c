/* ctower/obj/watergem.c is cloned by ctower/water1.c */

inherit "/d/Emerald/ctower/obj/gem_base";
 
#include <stdproperties.h>
#include <ss_types.h>
 
void
create_gem()
{
    set_name("spinel");

    set_long("This is a deep blue spinel gem that tingles when held.\n");

    add_prop(OBJ_I_VALUE, 288);

    config_gem("water", SS_ELEMENT_WATER);
}
 
void invoke_msgs()
{
    write("It starts raining, which quickly turns into "+
        "a torential downpour, but then stops just as quickly as it "+
        "began.\n" );
    say("It starts raining, which quickly turns into "+
        "a torential downpour, but then stops just as quickly as it "+
        "began.\n" );
}
