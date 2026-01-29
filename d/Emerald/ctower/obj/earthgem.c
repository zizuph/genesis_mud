/* ctower/obj/earthgem.c is cloned by ctower/earth1.c */

inherit "/d/Emerald/ctower/obj/gem_base.c";

#include <stdproperties.h>
#include <ss_types.h>
 
void
create_gem()
{
    set_name("tourmaline");
    set_long("This is a dark brown tourmaline gem that tingles when held.\n");
  
    add_prop(OBJ_I_VALUE, 144);

    config_gem("earth", SS_ELEMENT_EARTH);
}

void invoke_msgs()
{
    write("The ground rumbles ominously for "+
	"a moment but then quickly subsides back to normal.\n" );
    say("The ground rumbles ominously for "+
	"a moment but then quickly subsides back to normal.\n" );
}
