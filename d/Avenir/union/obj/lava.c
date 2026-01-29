/* One of the objects that can be used to restart the fire in the
 * Union guild hall.
 *   Cirion, May 12 1996
 */
#pragma strict_types

inherit "/std/object";
#include <stdproperties.h>

#define FIRESTARTER   "union_is_a_firestarter"

public void
create_object()
{
    set_name("rock");
    add_name(({"lava","quantity"}));
    add_name(FIRESTARTER);
    set_adj(({"hot","molten"}));
    set_short("quantity of molten rock");
    set_long("It is a yellowish glowing mass of superheated rock. There "+
	"seem to be tiny sparkles of something glimmering deep within.\n");

    add_prop(OBJ_I_VALUE, 2);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 2);
    add_prop(OBJ_M_NO_GET, "It is too hot to touch!\n");
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!to->query_prop(ROOM_I_IS) && !living(to))
    {
	add_prop(OBJ_I_VOLUME, to->volume_left());
	add_prop(OBJ_I_WEIGHT,
	    to->query_prop(CONT_I_MAX_WEIGHT) - to->weight());
    }
}
