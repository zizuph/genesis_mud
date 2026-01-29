inherit "/std/armour.c";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

/* standard light armour for corsairs: Xeros of GondorMud 29 Nov 1993 */

void
create_armour() {
    set_name("pantaloons");
    set_adj("quilted");
    set_short("pair of quilted pantaloons");
    set_long(BSN("These baggy "+short()+" provide the type of protection a "+
        "sailor needs, light, warm, but effective enough for the weight."));
    set_default_armour(12,A_LEGS,({-1,-1,2}),0);
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_ARMOUR(12,A_LEGS));
    add_prop(OBJ_I_VOLUME,1500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(12)+random(50)-29);
}
query_recover() { return MASTER+":"+query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); } 
