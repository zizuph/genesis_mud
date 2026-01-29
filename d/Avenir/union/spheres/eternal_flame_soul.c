// Command soul for the beauty sphere.
#include "defs.h"
inherit SPHERE_SOUL;

/* Id and autoload */
public string
get_soul_id(void)
{
    return "Union Sphere of "+ SPHERES[SPH_ETERNAL];
}

/* Commands */
public mapping
query_cmdlist(void)
{
    mapping cmd_map = ([ ]);

    return cmd_map;
}
