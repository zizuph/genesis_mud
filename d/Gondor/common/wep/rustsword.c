/* sword on ground  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_weapon()
{
    set_name(({"sword","longsword"}));
    add_name("long sword");
    set_pname("swords");
    add_pname("longswords");
    set_adj(({"rusty","battle-torn"}));
    set_short("rusty and battle-torn longsword");
    set_pshort("rusty and battle-torn longswords");
    set_long("This is a rusty iron longsword, made to fight with.\n");
    set_dull(2);
    set_corroded(2);
    set_likely_corr(3);
    set_default_weapon(24,18,W_SWORD,W_SLASH|W_IMPALE,W_RIGHT,0);
    add_prop(OBJ_I_WEIGHT,4567);
    add_prop(OBJ_I_VOLUME,1000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(24,18)+random(10)-5);
}
