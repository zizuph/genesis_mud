/* ctower/obj/firegem.c is cloned by ctower/fire1.c */

inherit "/d/Emerald/ctower/obj/gem_base";

#include <stdproperties.h>
#include <ss_types.h>
 
void
create_gem()
{
    set_name("ruby");
    set_long("This is a fiery red ruby gem that tingles when held.\n");
  
    add_prop(OBJ_I_VALUE, 864);

    config_gem("fire", SS_ELEMENT_FIRE);
}

void invoke_msgs()
{
    write("The temperature in the area rises "+
        "dangerously high, but just when you feel faint it cools "+
        "down to normal.\n" );
    say("The temperature in the area rises "+
	"dangerously high, but just when you feel faint it cools "+
	"down to normal.\n" );
}
