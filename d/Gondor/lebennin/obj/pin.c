inherit "/std/weapon.c";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

/* standard belaying pin for use by corsairs: Xeros of GondorMud 26 Nov 1993 */

void
create_weapon() {
    set_name("pin");
    add_name("weapon");
    set_short("heavy belaying pin");
    set_adj("heavy");
    add_adj("belaying");
    set_long(BSN("A common wooden pin found on ships, oft grabbed by "+
        "combatants in need of a handy yet effective weapon."));
    set_default_weapon(12,13,W_CLUB,W_BLUDGEON,W_NONE,0); 
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(12,13)+random(100));
    add_prop(OBJ_I_VOLUME,3000+random(789));
    add_prop(OBJ_I_WEIGHT,3000+random(567));
}
query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
