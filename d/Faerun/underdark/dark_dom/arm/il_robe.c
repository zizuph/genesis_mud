/* 
 * Originally coded as /d/Kalad/common/wild/pass/arm/mfrobe.c by Antharanos
 * for the mind flayers of Kalad.
 * Converted over by Finwe for illithids in the Underdark
 * -- Finwe, July 2006
 */ 

#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit FAERUN_ARM_BASE;

void create_faerun_armour()
{
    set_name("robe");
    set_adj("fine");
    add_adj("red");
    set_short("fine red robe");
    set_long("A long full robe, colored the deepest crimson. Cryptic " +
        "sigils have been sewn into the robe. The sleaves are long, " +
        "extending down to the wrists. The collar is turned up, fanning " +
        "out behind and around the back of the head.\n");
    
    add_item(({"sigils", "sigil"}),
        "They are magical signs sewn into the robe. They are cryptic " +
        "looking and their meaning unknown.\n");

    set_ac(6);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,1200);
    add_prop(OBJ_I_VOLUME,2500);
    add_prop(OBJ_I_WEIGHT,2500);
}
