/*
 * /d/Sparkle/area/spiderlair/drops/nondrop/bone_bracers.c
 * 
 * Nerull, 21/2/09.
 */
 
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "../../defs.h";

inherit "/std/armour";

void
create_armour()
{
    set_name("bracers");
    set_adj("bone");
    set_adj("white");
    set_short("pair of white bone bracers");
    set_pshort("pairs of white bone bracers");
    set_long("These pair of white bone bracers gives good " +
    "protection of the underarms, and they are adjustable to fit " +
    "anyone of normal size. They are white-painted and seems " +
    "to be made of melted bone fused together.\n");
    set_ac(40);
    set_at(A_ARMS);
    add_prop(OBJ_I_VOLUME, 3500);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VALUE, 1500);
}



