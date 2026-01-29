inherit "/std/armour";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name(({"chainmail","chain mail","mail"}));
    set_pname("chainmails");
    add_pname("mails");
    set_short("grey chainmail");
    set_pshort("grey chainmails");
    set_long("The grey chainmail is made of small iron rings.\n");
    set_default_armour(19,A_BODY,0,0);
    add_prop(OBJ_I_WEIGHT,5500);
    add_prop(OBJ_I_VOLUME,700);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(19)+random(200)-100);
 }

