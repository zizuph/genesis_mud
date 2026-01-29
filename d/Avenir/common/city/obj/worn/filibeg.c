
#pragma strict_types
#pragma save_binary

inherit "/d/Avenir/inherit/cloth_arm";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Avenir/include/defs.h"

void
create_armour()
{
    set_name("filibeg");
    add_name(({"skirt", "kilt"}));    
    set_short("white linen filibeg");
    set_pshort("white linen filibegs");
    set_adj(({"white","linen"}));
    set_long("This is a short, pleated skirt made of white "+
        "linen. It is worn by men and women in place of a "+
        "loin-wrap for the sake of modesty or aesthetics. "+
        "It scarcely reaches to mid thigh, but the pleats "+
        "are crisp and well-made.\n");
    set_ac(5);
    set_at(A_WAIST); 
}

