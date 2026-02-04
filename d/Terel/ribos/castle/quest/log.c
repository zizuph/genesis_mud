inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

create_object()
{
    set_name("log");
    set_short("log");
    set_long("It's a log!  It rolls down the stairs, and into the yard, and over "+
	     "the neighbors dog.  Everyone loves a log!\n");

    add_prop(OBJ_I_VALUE,  10);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 300);
}
