// Command soul for the isolation sphere.
#include "defs.h"
inherit SPHERE_SOUL;

/* Id and autoload */
public string
get_soul_id(void)
{
    return "Union Sphere of "+ SPHERES[SPH_ISOLATION];
}

/* Commands */
public mapping
query_cmdlist(void)
{
    mapping cmd_map = ([ ]);

    cmd_map += query_sphere_cmdlist(SPH_ISOLATION);
    cmd_map += query_union_cmdlist(SPH_ISOLATION);

    return cmd_map;
}
