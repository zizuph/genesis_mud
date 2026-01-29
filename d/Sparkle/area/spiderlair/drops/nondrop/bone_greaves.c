/*
 * /d/Sparkle/area/spiderlair/drops/nondrop/bone_greaves.c
 *
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
    set_name("greaves");
    add_name("leggings");
    set_adj("bone");
    set_adj("white");
    set_short("pair of white bone greaves");
    set_pshort("pairs of white bone greaves");
    set_long("These white bone greaves gives excellent " +
    "protection to your legs, and partically the top of " +
    "the legs. They are white-painted and seems to be made of " +
    "melted bone fused together.\n");
    set_ac(40);
    set_at(A_LEGS);
    add_prop(OBJ_I_VOLUME, 3500);
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VALUE, 1500);
}



