inherit "/std/object";

#include <stdproperties.h>


create_object(){

	set_name("eye");
	set_adj("citric");
	set_adj("sparkling");
	set_long("This looks like an eye, and it sparkles, maybe it's valuable?\n");

	add_prop(OBJ_I_VALUE, 10000);
}
