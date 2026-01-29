/*
 * Armour for Troll patrolls in Underdark
 * by Finwe, July 2005
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define AC 35 + random(5)

void create_faerun_armour()
{
    set_name(({"armour","platemail","mail"}));
    set_short("dented steel platemail");
    set_adj(({"steel","dented"}));
    set_long("This is a " + short() + ". It is made of plates of steel " +
        "and fused together. It is dented from countless battles and " +
        "looks slightly rust. There is some dried blood on it.\n");
    
    set_ac(AC);
    set_at(A_BODY);
    set_am(({ 0, 0, 0 }));
    set_af(TO);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC,A_BODY));
    
}
