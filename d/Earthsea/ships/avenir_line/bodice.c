inherit "/std/armour";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "defs.h"

void
create_armour()
{
    set_name("bodice");
    set_adj(({"white", "lacey", "low-cut"}));
    set_short("lacey white low-cut bodice");
    set_long(break_string("This is a tight-fitting low-cut "+
	"lacey bodice, which is made to hug a woman's figure, showing "+
	"it to best advantage.\n", 70));
    set_at(A_TORSO);
    set_ac(30);
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 350);
}
