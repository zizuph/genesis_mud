inherit "/std/weapon";
inherit "/lib/keep";

#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>

object wielder;

public void
create_weapon()
{
    set_name("longsword");
    add_name(({"weapon","sword"}));
    set_pname("longswords");
    add_pname(({"weapons","swords"}));
    add_adj("slender");
    set_short("slender longsword");
    set_pshort("slender longswords");
    set_long("A prime example of human talents at blacksmithing, " +
      "this longsword has a long, thin blade, and a solid handle. " +
      "The sword's guard forms a simple, unadorned cross. " +
      "Though forged from light alloy, the " +
      "sword is lighter still, as circular sections have been " +
      "cut out from the middle of the blade. The hollow-back " +
      "design runs " +
      "from the guard up to about half of the weapon's length. " +
      "It appears that the sword has been custom made for someone " +
      "of considerable sword skill, but weak arm, like a child " +
      "perhaps?\n");
    set_default_weapon(35, 35, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(37,35));

    set_wf(TO); 
    seteuid(getuid(TO));    
}

mixed
wield(object what)
{
    wielder = TP;

    wielder->catch_msg("The sword is extremely light... But " +
      "handles well.\n");
    return 0;
}      
