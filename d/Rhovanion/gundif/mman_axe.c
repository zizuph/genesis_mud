inherit "/std/weapon";
 
#include <stdproperties.h>
#include <wa_types.h>
#include "/d/Rhovanion/defs.h"
 
#define AXE_HIT 25
#define AXE_PEN 31
 
void
create_weapon()
{
    set_name(({ "axe", "_mirk_man_axe_" }));
    set_adj(({ "large", "cutting", "wood" }));
    set_short("large axe");
 
    set_long("A woodsman's axe. Used mainly for cutting down the "+
             "trees, well, at least in usual forests. Being a "+
             "Mirkwood man's axe it seems to be used also for "+
             "chopping off spider legs, its black blade having "+
             "some interesting stains of unknown origin.\n");
 
    set_wt(W_AXE);
    set_dt(W_SLASH || W_BLUDGEON);
    set_hit(AXE_HIT);
    set_pen(AXE_PEN);
 
    set_likely_corr(1);
    set_likely_dull(10);
    set_likely_break(5);
 
    add_prop(OBJ_I_WEIGHT,10000);
 
    update_prop_settings();
}
