/* created by Aridor 07/06/93 */

inherit "/std/object";

#include "../local.h"
#include <stdproperties.h>

create_object()
{
    set_name("invitation");
    add_name("letter");
    add_name("iletter");
    set_adj("golden");
    set_short("golden invitation");
    set_long(BS("A noble looking letter.",SL));
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 40);

}

