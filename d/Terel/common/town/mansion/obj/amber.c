inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>


create_object()
{
    set_name("amber");
    set_adj("orange");
    set_long(break_string("This big amber looks transparent. " +
	"You can see something included in it. It looks quite " +
	"precious!\n",70));
    add_prop(OBJ_I_VALUE, 2000);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 150);
}
