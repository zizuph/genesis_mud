inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "defs.h"


int ac = 20;
#define COLOURS  (({ "red", "green", "purple",\
"red-striped", "orange", "white", "yellow",\
"purple-polkadotted",\
}))

void
create_armour()
{

    string colour = COLOURS[random(sizeof(COLOURS))];

    set_name("bandanna");
    set_adj(colour);
    set_short(colour + " bandanna");
    set_long(break_string("A bright " + colour + " bandanna, "+
	"typically worn around the neck by sailors.\n", 70));
    set_at(A_NECK);
    set_ac(ac);
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 35);
}
