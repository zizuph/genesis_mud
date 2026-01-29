
inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include "../merc.h"

public void
create_weapon()
{
    set_name("longsword");
    add_name(({"weapon","sword"}));
    set_pname("longswords");
    add_pname(({"swords","weapons"}));
    set_adj(({"black", "steel"}));
    set_short("black steel longsword");
    set_pshort("black steel longsword");
    set_long("The longsword has a tapering blade, in which a blood "+
	"groove has been shaped, allowing blood to flow out of a "+
	"would while the sword is still in it. The handle has been "+
	"wrapped with leather to give the wielder a good grip.\n");
    set_default_weapon(30,30, W_SWORD, W_SLASH || W_IMPALE, W_ANYH);
    
    add_prop(OBJ_I_VOLUME, 2400);
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30,30));
}

