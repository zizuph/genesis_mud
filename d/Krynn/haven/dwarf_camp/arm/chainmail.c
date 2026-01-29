inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>

#include "../../local.h"

public void
create_armour()
{
    set_name("chainmail");
    set_pname("chainmails");
    add_name(({"armour","chain","mail"}));
    add_pname(({"armours","chains","mails"}));
    set_adj(({"iron", "bulky"}));
    set_short("bulky iron chainmail");
    set_pshort("bulky iron chainmails");
    set_ac(33);
    set_at(A_BODY);
    set_am( ({0,0,0}) );
    set_long("This is definitely dwarven in construction. It is " +
        "smaller, but heavier, than most human-sized armour. " +
        "It is made of thick iron chains, interwoven to create an " +
        "extremely strong, yet bulky, armour. This armour is " +
        "favoured by dwarves.\n");
    add_prop(OBJ_I_VOLUME, 7000);
    add_prop(OBJ_I_WEIGHT, 9500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(33));
}

