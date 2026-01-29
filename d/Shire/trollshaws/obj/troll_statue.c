#include "../defs.h"

inherit "/std/object";

void
create_object()
{
    set_short("stone troll statue");
    set_name("statue");
    set_adj(({"stone","troll"}));

    add_prop(OBJ_I_WEIGHT,100000);
    add_prop(OBJ_I_VOLUME, 70000);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
}

varargs void
configure(mixed thing)
{
    string str;

    if (stringp(thing))
	str = thing;
    else
    {
	str = thing->query_long();
	str += thing->show_sublocs();
	SHAWS_MASTER->add_statue(file_name(ENV(TO)), str);
    }
    set_long("This is a stone statue of a troll which was outside "+
      "when the sun rose.\n\n"+str+"\n");
}
