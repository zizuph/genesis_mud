// Command soul for the vengeance sphere.
#include "defs.h"
inherit SPHERE_SOUL;

/* Id and autoload */
public string
get_soul_id(void)
{
    return "Union Sphere of "+ SPHERES[SPH_VENGEANCE];
}

/* Commands */
public mapping
query_cmdlist(void)
{
    mapping cmd_map = ([ ]);

    cmd_map += query_sphere_cmdlist(SPH_VENGEANCE);
    cmd_map += query_union_cmdlist(SPH_VENGEANCE);

    return cmd_map;
}
