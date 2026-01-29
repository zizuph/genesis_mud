
/* This is a magic light, that lights up the medal. It's cloned by the
 * radiance spell.
 * made by percy.
 * adapted to the new spell system by Aridor, 10/95
 */
#include "../../guild.h"
#include "../local.h"

inherit "/std/object";
inherit MAGIC_OBJECT;

#include <stdproperties.h>

void
create_object()
{
    set_name("lightobj");
    set_adj("magic");
    set_no_show();
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_VOLUME, 0);
}

void
init_spell(object caster, object target, object prev)
{
    add_prop(OBJ_I_LIGHT, 2);
    find_living("aridor")->catch_msg("RADIANCE P:" + query_power() + " D:" +
				     query_duration() + ".\n");
}

void 
remove_object() 
{
    write("Your medal's light dims then goes out.\n");
    say("The light from the medal goes out.\n");
    ::remove_object();
}



