inherit "/std/rope";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

create_rope()
{
    set_name("rope");
    set_pname("ropes");
    add_adj(({"long", "very", "light", "elven" }));

    set_short("very long but light elven rope");
    set_long(
	"This is a very long rope made by elves. It is amazingly light, "+
	"and seems very strong.\n");

    add_prop(OBJ_I_VALUE, 40);
    add_prop(OBJ_I_WEIGHT, 2300);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop("_rope_i_length", 200*100);
}

void init_recover(string s) { }
string query_recover() { return MASTER+":"; }
