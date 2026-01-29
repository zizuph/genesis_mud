inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

void
create_armour()
{
    set_name("mail");
    set_ac(46);
    set_at(A_BODY);
    set_am( ({ 5, 4, 3 }) );
    set_adj("banded");
    add_adj("silver");
    set_short("silver banded mail");
    set_pshort("silver banded mails");
    set_long("This is a beautiful silver banded mail. Forged "+
             "from the purest of silver and reinforced with "+
             "strong steel. The mail is actually quite light "+
             "considering all the different layers of metal "+
             "that was used to forge it. There is no doubt "+
             "that this armour will grant one good "+
             "protection.\n");    

    add_prop(OBJ_I_VOLUME, 6050);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(46, A_BODY));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(60));
}
