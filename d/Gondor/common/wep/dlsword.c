inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon()
{
    set_name(({"longsword","sword"}));
    set_pname("swords");
    add_pname("longswords");
    set_adj("steel");
    add_adj("long");
    add_adj("elven");
    add_adj("fine");
    set_short("steel longsword");
    set_pshort("steel longswords");
    set_long("This solid steel longsword was crafted by elves, and looks to be\n"+
        "a very fine weapon.\n");
    set_default_weapon(30,26,W_SWORD,W_SLASH | W_IMPALE,W_NONE,0);
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(30,26) + random(150) - 75);
}

