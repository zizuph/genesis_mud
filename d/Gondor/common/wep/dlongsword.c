/* Increased hit/pen, Eowul, 2009 */
/* longsword  */
inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name(({"longsword","sword","weapon"}));
    set_pname("swords");
    add_pname("longswords");
    set_short("blue steel longsword");
    set_pshort("longswords");
    set_long("A large Gondorian long sword, made of alloyed blue steel.\n");
    set_adj(({"long", "blue", "steel", "large", "gondorian", }));
    set_default_weapon(35,30,W_SWORD,W_SLASH | W_IMPALE,W_RIGHT,0);
    add_prop(OBJ_I_WEIGHT,7000);
    add_prop(OBJ_I_VOLUME,1280);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(35,30)+random(200)-100);
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}
