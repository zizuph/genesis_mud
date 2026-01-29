/* reward for jousting */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
	set_name("feather");
	set_short("small golden feather");
	set_adj("small");
	add_adj("golden");
	set_long("It is small replica of gryfon feather, made of pure gold." +
		"At the top you see black diamond set into it.\n");
	add_item(({"diamond", "black diamond" }), "The large gem is set " +
		"in \"the eye\" of the feather creating sort of magnifying "+
		"glass.\n");
        add_prop(OBJ_I_NO_DROP,1);
        add_prop(OBJ_I_NO_STEAL,1);
        add_prop(OBJ_I_NO_SELL,1);
        add_prop(OBJ_I_NO_BUY,1);
        add_prop(OBJ_I_NO_DROP,1);
        seteuid(getuid(this_object()));

}

public string
query_auto_load()
{
    setuid();
    seteuid( getuid() );
    return MASTER + ":";
}

