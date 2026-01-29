inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>

#include "/d/Krynn/haven/local.h"

public void
create_armour()
{
    set_name("leather");
    set_pname("leathers");
    add_name("armour");
    add_pname("armours");
    set_adj(({"studded", "leather"}));
    set_short("studded leather armour");
    set_pshort("studded leather armours");
    set_ac(25);
    set_at(A_BODY);
    set_am( ({0,0,0}) );
    set_long("The leather of which this armour is made has "+
      "been hardened, to strengthen it. It also has small studs "+
      "on it, making it much more protective than most leather "+
      "armours, and yet still lightweight.\n");
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30));
}

