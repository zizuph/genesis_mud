/* 	the suit of banded mail worn by the guardian knight in the
	crystalline palace

    coder(s):   Glykron

    history:    25. 2.92    recovery added                  Glykron
                 9. 2.92    header added                    Glykron

*/

#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name( ({ "mail", "armor", "armour" }) );
    set_adj("banded");
    set_short("suit of banded mail");
    set_pshort("suits of banded mail");
    set_long(
	"This is a suit of banded mail.\n"
    );
    set_ac(25);
    set_at(A_BODY);
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 4000);
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