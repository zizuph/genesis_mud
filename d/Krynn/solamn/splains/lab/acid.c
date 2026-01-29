/* glass bottle for black dragon quest by percy */


inherit "/std/object";

#include <stdproperties.h>
#define SELECT_ACID ({"dragon","formic","citric","hydrochloric",\
                      "nitric","silicic","sulphuric"})[random(7)]

void
create_object()
{
    string acid = SELECT_ACID;
    set_name("flask");
    set_adj("glass");
    add_name("acid");
    add_name(acid + "_acid");
    add_adj(acid);
    set_short("glass flask with acid");
    set_pshort("glass flasks with acid");
    set_long("This is a glass flask with what you assume to be " +
	     acid + " acid in it.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
