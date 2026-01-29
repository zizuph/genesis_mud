inherit "/std/weapon.c";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>

/* standard cutlass for use by corsairs Xeros of GondorMud 26 Nov 1993 */

void
create_weapon() {
    set_name("cutlass");
    add_name("weapon");
    set_short("grey cutlass");
    set_adj("grey");
    set_long(BSN("A standard issue cutlass made of a shiny grey metal. "+ 
        "It has a C shaped guard over the hilt and a slightly curving blade."));
    set_default_weapon(18,21,W_SWORD,W_SLASH,W_NONE,0);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(18,21)+random(100));
    add_prop(OBJ_I_WEIGHT,6000+random(500));
    add_prop(OBJ_I_VOLUME,850);
}
query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
