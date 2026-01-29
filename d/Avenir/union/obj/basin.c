/*
 * Revisions:
 * 	Lucius, Jul 2017: Re-Code
 */
#pragma strict_types
inherit "/std/container";

#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

#include "../defs.h"

public string
basin_inv(void)
{
    object *stuff = FILTER_DEAD(all_inventory(TO));
    if (!sizeof(stuff))
	return "";

    return " Sitting in the water is "+ COMPOSITE_DEAD(stuff);
}

public void
create_container()
{
    set_name("basin");
    set_long("It is a large basin made from jet black obsidian "
      +"and streaked with thin red veins of adamantine. It is "
      +"filled with cool and somewhat dirty water.@@basin_inv@@\n");

    remove_prop(CONT_I_TRANSP);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_M_NO_GET, "It is far too big.\n");
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_CONTAIN_WATER, 1);

    set_no_show_composite(1);
}
