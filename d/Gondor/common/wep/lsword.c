/* longsword  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon()
{
    set_name(({"longsword","sword","weapon"}));
    set_pname("longswords");
    add_pname("swords");
    set_short("blue steel longsword");
    set_pshort("blue steel longswords");
    set_long("A large dunedain long sword, made of alloyed blue steel.\n");
    set_adj("long");
    add_adj("blue");
    add_adj("steel");
    add_adj("large");
    add_adj("dunedain");
    set_default_weapon(18,20,W_SWORD,W_SLASH,W_RIGHT,0);
    add_prop(OBJ_I_WEIGHT,8000);
    add_prop(OBJ_I_VOLUME,1280);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(18,20)+random(400)-100);
}

query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
