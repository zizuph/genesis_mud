#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

inherit "/std/weapon";
string *knifelooks=({"silvery","sleek","leaf-shaped","sharp"});
string *knifetype=({"dagger","knife"});
int attack = 0;

create_weapon()
{
    set_name(knifetype[random(2)]);
    add_adj(knifelooks[random(4)]);
    set_long("It's a "+short()+". Looks like a decent enough weapon.\n");
    set_default_weapon(25, 25, W_KNIFE, W_SLASH, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1000);
}


