/* shortsword  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_weapon()
{
    set_name(({"shortsword","sword"}));
    set_pname("shortswords");
    add_pname("swords");
    set_short("bluegrey steel shortsword");
    set_pshort("bluegrey steel shortswords");
    set_long("A small dunedain stabbing sword, made of alloyed bluegrey steel.\n");
    set_adj("stabbing");
    add_adj("bluegrey");
    add_adj("steel");
    add_adj("small");
    add_adj("dunedain");
    set_default_weapon(12,18,W_SWORD,W_SLASH|W_IMPALE,W_ANYH,0);
    add_prop(OBJ_I_WEIGHT,4000);
    add_prop(OBJ_I_VOLUME,640);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(12,18)+random(400)-100);
}
