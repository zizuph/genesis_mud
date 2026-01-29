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
    set_adj("elven");
    add_adj("slender");
    set_short("slender elven longsword");
    set_pshort("slender elven longswords");
    set_long("A prime example of elven talents at blacksmithing, " +
      "this longsword has a long, thin blade, and a solid handle. " +
      "The sword's guard forms a simple cross with green gems " +
      "set at both ends. Though forged from light alloy, the " +
      "sword is lighter still, as leaf-shaped sections have been " +
      "cut out from the middle of the blade. The hollow-back " +
      "leaf design runs " +
      "from the guard up to about half of the weapon's length. " +
      "It appears that the sword has been custom made for someone " +
      "of considerable sword skill, but weak arm, like an elven " +
      "child, or perhaps, a magic user? If so, the blade could be " +
      "enchanted as well...\n");
    set_default_weapon(47, 45, W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(47,45));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO,
      "This sword has been crafted in Silvanesti for a certain " +
      "promising magic user of rich standing. However, found a " +
      "user of black arts, and a traitor, he was banned from " +
      "Silvanesti, and fled with many a magic item, this sword " +
      "included.\n");
    add_prop(MAGIC_AM_ID_INFO,
      ({"This weapon is magically enchanted.\n", 5,
	"The blade was forged in Silvanesti, and seems quite " +
	"potent.\n", 20,
	"This was the blade of Fael-theas, traitor of " +
        "Silvanesti. The sword has been masterfully " +
        "enchanted, and is a potent battle artifact.\n", 45}));
    add_prop(MAGIC_AM_MAGIC,({60,"enchantment"}));

    set_wf(TO); 
    seteuid(getuid(TO));    
}

mixed
wield(object what)
{
    wielder = TP;

    wielder->catch_msg("The sword is extremely light... But the " +
      "blade's edges gleam with deadly light as you wield it.\n");
    say("The elven sword's edges gleam with deadly light as " +              QCTNAME(wielder) + " wraps " + HIS(TP) + " hand around " +
      "its hilt.\n");
    return 0;
}      
