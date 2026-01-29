#pragma save_binary

inherit "/std/armour";
#include <formulas.h>
#include <stdproperties.h>

void
create_armour()
{
    set_name(({"suit", "armor", "armour", "mail", "chainmail"}));
    set_pname(({"suits", "armor", "armour", "mail", "chainmail"}));
    set_adj(({"chain", "chainmail", "iron"}));
    set_short("suit of iron chainmail");
    set_pshort("suits of iron chainmail");
    set_long("This is a suit of armor made of large iron chain links.\n");
    set_ac(15);
    set_at(A_BODY);
    set_am(({-1, 0, 1}));
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 3000);
}