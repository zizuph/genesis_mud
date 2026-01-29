inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include "../merc.h"

public void
create_armour()
{
    set_name("chainmail");
    add_name(({"mail","chain","armour"}));
    set_pname("chainmails");
    add_pname(({"mails","chains","armours"}));
    set_adj("mercenary");
    add_adj(({"black","steel","chain"}));
    set_short("black chainmail");
    set_pshort("black chainmails");
    set_long("The standard chainmail is blackened, with "+
	"a crest of a red dragon adorning the chest area. "+
	"The armour seems to be of good quality.\n");
    set_ac(27);
    set_am( ({-2,3,-1}) );
    set_at(A_BODY);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(27));
}

