inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Krynn/common/defs.h"

create_weapon()
{
    set_name("shortsword");
    set_pname("shortswords");
    set_adj("tarnished");
    set_long(BS("This is a standard shortsword though the metal " +
        "no longer shines.",70));
    set_default_weapon(18, 15, W_SWORD, W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 300);
}
