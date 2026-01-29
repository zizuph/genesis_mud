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

#define AC 30 + random(5)

void create_faerun_armour()
{
    set_name(({"gauntlets"}));
    set_short("pair of battered gauntlets");
    set_pshort("pairs of battered gauntlets");
    set_adj(({"steel","battered"}));
    set_long("This is a " + short() + ". They fit over the arms and " +
        "seen many wars. They are scratched and have streaks of blood on " +
        "them.\n");
    
    set_ac(AC);
    set_at(A_ARMS);
    set_am(({ 0, 2, -2}));
    set_af(TO);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC,A_ARMS));
    
}
