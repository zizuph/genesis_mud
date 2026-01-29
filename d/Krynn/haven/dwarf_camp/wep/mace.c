
inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include "/d/Krynn/haven/local.h"

public void
create_weapon()
{
    set_name("mace");
    add_name(({"weapon","club"}));
    set_pname("mace");
    set_pname("maces");
    add_pname(({"clubs","weapons"}));
    set_adj(({"weighted", "iron"}));
    set_short("weighted iron mace");
    set_pshort("weighted iron maces");
    set_long("This is an iron mace, weighted towards the end to "+
      "lend power to the swing. Such weapons are often used by "+
      "dwarves. It's rather unwieldy, because of it, but a true "+
      "swing with this mace should be quite unpleasant for the "+
      "one on the receiving end.\n");
    set_default_weapon(23, 28, W_CLUB, W_BLUDGEON, W_ANYH);

    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(23,26));
}

