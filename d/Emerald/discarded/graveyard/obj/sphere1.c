/*
 * SPHERE1.c
 * This is one of the glowing blue spheres used in the Emerald Tomb Quest.
 * - Alaron October 2, 1996
 * For a list of which shapes are shown inside which sphere's reflection,
 * check out the file /d/Emerald/kroad/graveyard/gquest.h for the item
 * SHAPE_DESCS. The sphere_num here is the INDEX into that item array.
 */

#include "../default.h"
#include "../gquest.h"
#include "/d/Emerald/defs.h"

inherit BASE_SPHERE;

void
create_sphere()
{
    set_sphere_num(0);
}
