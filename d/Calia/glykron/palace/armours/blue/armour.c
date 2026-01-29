/* 	blue platemail for the good knight in the crystalline palace

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
    set_name( ({ "suit", "armor", "armour", "mail", "plate", "platemail" }) );
    set_pname( ({ "suits", "armor", "armour", "mail", "plate", "platemail" }) );
    set_adj( ({ "plate", "platemail", "blue" }) );
    set_short("suit of blue platemail");
    set_pshort("suits of blue platemail");
    set_long(BS(
	"This suit of blue platemail has an image of a pair of hands shaking " +
	"on the front.  " +
	"\n"));
    set_ac(25);
    set_at(A_BODY);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 6000);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}