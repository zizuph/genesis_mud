inherit "/std/object";
#include <stdproperties.h>

create_object()
{
    set_name("shell");
    add_name("_eclipsia_turtle_shell");
    set_adj( ({"spotted", "turtle"}) );
    set_short("spotted turtle shell");
    set_long("This beautiful spotted turtle shell looks like it's "+
	"experienced a fair amount of trauma judging from the scratches "+
	"and chip-marks on it. It's size is immense, and it looks like "+
	"you could fit an average hobbit in it.\n");

    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_I_VOLUME, 15000);
}
