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
    set_name("broadsword");
    add_name(({"weapon","sword"}));
    set_pname("broadswords");
    add_pname(({"weapons","swords"}));
    set_adj("steel");
    set_short("steel broadsword");
    set_pshort("steel broadswords");
    set_long("A solid, steel broadsword. The blade looks very " +
        "sharp, but other then that, you see nothing special about " +         "this heavy and unwieldy sword. In addition, the very " +
        "tip of it has been snapped off, making it virtually " +
        "impossible to stab with the weapon.\n");
    set_default_weapon(35, 35, W_SWORD, W_SLASH, W_ANYH);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_WEIGHT, 8500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20,20));

    set_wf(TO); 
    seteuid(getuid(TO));    
}
