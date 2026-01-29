inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("iron scale-mail");
    add_name("mail");
    set_ac(32);
    set_at(A_BODY);
    add_adj( ({ "well-tended" }) );
    set_short("well-tended iron scale-mail");
    set_pshort("well-tended iron scale-mails");
    set_long("A tough, well wrought piece of armour that has been " +
             "carefully oiled, cleaned and looked after. It is quite " +
             "obvious that it's previous owner depended closely on the " +
             "state of his equipment for survival in combat. It is crafted " +
             "from overlapping scales of iron sewn to a tough leather vest.\n");
    
    add_prop(OBJ_I_VOLUME, 3100);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(32, A_BODY));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(32));
}

