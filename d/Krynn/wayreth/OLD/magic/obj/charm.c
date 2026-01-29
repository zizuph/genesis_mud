/*
 * The charm object, used by 'winvite'
 */

#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../../local.h"

inherit "/std/object";
inherit "/d/Krynn/rastlin/open/spells2/magic.object";

object gTarget;

public void
create_object()
{
    set_name("_charm_object");
    set_no_show();

    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
}

public void
init_spell(object caster, object target, object prev)
{
    target->add_subloc("_krynn_charm", TO, "forehead");

    target->add_prop(LIVE_I_AM_INVITED, 1);

    gTarget = target;
}

public void
notify_dispel_magic(object ob)
{
    gTarget->remove_prop(LIVE_I_AM_INVITED);
    gTarget->remove_subloc("_krynn_charm");

    gTarget->catch_msg("You suddenly get the feeling of something that " +
		       "has left you.\n");
}

public string
show_subloc(string subloc, object me, object looker)
{
    string str = "There is a red spot in ";
    string poss = POSSESSIVE(me);

    if (me == looker)
        poss = "your";


    return str + poss + " forehead.\n";
}






