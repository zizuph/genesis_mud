#include "../default.h"
inherit (STD + "armour");

#include <wa_types.h>

void
create_armour()
{
    ::create_armour();

    set_name("tanned leather vest");
    add_name("vest");
    set_long("A sturdy-looking vest that appears to be made of tanned "+
      "horse skin.\n");
    set_ac(6);
    set_at(A_BODY);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_WEIGHT, 2000);
}
