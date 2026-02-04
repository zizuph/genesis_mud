/* A skull. Mortricia 920910 */
inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_object()
{
    set_name("skull");
    set_short("human skull");
    set_long(break_string(
        "It's a skull. Its owner was probably an adult human. " +
	"It looks somewhat scorched.\n", 70));
    set_adj("human");
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}
