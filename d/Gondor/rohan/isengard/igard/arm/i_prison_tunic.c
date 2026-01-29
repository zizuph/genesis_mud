/*
 *  IGARD_ARM + "i_prison_tunic.c"
 *  Rags worn by prisoners of Isengard.
 *    Modified from: /d/Gondor/common/arm/releather.c
 *
 *    Last modified by Alto, 11 October 2001
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
    set_name("tunic");
    set_pname("tunics");
    set_short("ragged moldy tunic");
    set_pshort("ragged moldy tunics");
    set_adj("ragged");
    add_adj("moldy");
    set_long("This is a standard tunic issued to prisoners of Isengard. "
        + "It is torn, filthy and stinks of mildew.\n");
    set_default_armour(7, A_BODY, ({ 0, 1, -1}), 0);
    add_prop(OBJ_I_WEIGHT, 3800);
    add_prop(OBJ_I_VOLUME, 1100);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(7) + random(24));

}
