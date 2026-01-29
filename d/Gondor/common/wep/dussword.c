/* The typical shortsword of the Dunlendings */
#include "/sys/stdproperties.h"
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_weapon()
{
    set_name(({"sword","weapon","short sword"}));
    set_short("dunlending short sword");
    set_pname("swords");
    add_pname("shortswords");
    set_pshort("swords");
    set_long("This is a short sword with a sharp, black blade. Swords like this are often used by the \n"+
        "dunlendings.\n");
    set_adj("dunlending");
    add_adj("black");
    add_adj("short");
    set_default_weapon(25,20,W_SWORD,W_SLASH|W_BLUDGEON,W_RIGHT,0);
}
