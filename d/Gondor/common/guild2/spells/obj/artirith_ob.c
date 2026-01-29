/*
 * /d/Gondor/common/guild2/spells/obj/artirith_ob.c
 *
 * It is used with the 'artirith' spell of the Morgul Mages.
 *
 * Olorin, 01-nov-1994
 * Revision history:
 */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

object  shadow;

void
create_object()
{
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    set_no_show();
}

int
no_get(string str)
{
    if ((ENV(TO) != TP) || !objectp(shadow))
	return 0;
    write("You cannot "+query_verb()
      + " anything while you are in the realm of the shadows, "
      + "so you materialize again.\n");
    shadow->stop_effect();
    return 0;
}

void
set_shadow_obj(object x)
{
    shadow = x;
}

void
init()
{
    ::init();
    add_action(no_get, "get");
    add_action(no_get, "pick");
    add_action(no_get, "take");
    add_action(no_get, "wield");
    add_action(no_get, "draw");
    add_action(no_get, "steal");
}

