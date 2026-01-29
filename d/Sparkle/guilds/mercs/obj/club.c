inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include "../merc.h"

public void
create_weapon()
{
    set_name("mace");
    add_name(({"weapon","club"}));
    set_pname("mace");
    add_pname(({"maces","weapons"}));
    set_adj(({"black", "steel"}));
    set_short("black steel mace");
    set_pshort("black steel maces");
    set_long("The black steel mace has a long, slender shaft, wrapped "+
	"on one end with heavy leather to give the wielder a good grip. "+
	"The striking end has five flanges that give the head a diamond "+
	"shape, and are slightly sharpened at their peaks.\n");
    set_default_weapon(30,30, W_CLUB, W_BLUDGEON, W_ANYH);
    
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30,30));
}

