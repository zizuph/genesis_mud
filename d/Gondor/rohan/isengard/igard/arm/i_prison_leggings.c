/*
 *  IGARD_ARM + "i_prison_leggings.c"
 *  Rags worn by prisoners of Isengard.
 *    Modified from: /d/Gondor/common/arm/gleggings.c
 *
 *    Last modified by Alto, 07 October 2001
 *
 */

#pragma strict_types

inherit "/std/armour";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include "../igard_defs.h"

void
create_armour()
{
    set_name("leggings");
    add_name(({ "pair of leggings" }));
    set_pname("leggingses");
    set_adj("musty");
    add_adj("tattered");
    set_short("pair of tattered leggings");
    set_pshort("pairs of tattered leggings");
    set_long("The pair of tattered leggings is musty and saturated with "
        + "the stench of offal and grime.\n");

    set_default_armour(20, A_LEGS, ({ 1, 1, -2 }), 0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_LEGS));
    add_prop(OBJ_I_VOLUME, 2000); 
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20)+random(100)-50);

}
