inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("hat");
    set_short("silly hat");
    set_long("A silly-looking hat which a hobbit might wear.\n");
    set_ac(1);
    set_at(A_HEAD);

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 100);
}

