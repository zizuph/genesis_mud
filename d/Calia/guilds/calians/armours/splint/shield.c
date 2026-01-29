/* 	splint shield for the training knight in the crystalline palace

    coder(s):   Glykron

    history:    25. 2.92    recovery added                  Glykron
                25. 2.92    header added                    Glykron

*/

#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_armour()
{
    set_name("shield");
    set_adj("splint");
    set_short("splint shield");
    set_long(BS(
	"This is a shield fashioned in the same way as splint mail.  " +
    "\n"));
    set_ac(20);
    set_at(A_SHIELD);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
}