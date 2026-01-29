/*
 * /d/Gondor/anorien/cairandros/arm/ca_helm.c
 *
 * Armour for Cair Andros soldiers in the basement
 *
 * Varian - February, 2020
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <files.h>
#include <wa_types.h>
#include "../../defs.h"

void
create_armour()
{
    set_name("helmet");
    add_name( ({"armour", "helm"}) );
    set_short("Gondorian steel helmet");
    set_adj("gondorian");
    add_adj("steel");
    set_long("This helmet has been forged from the " +
        "finest steel, inricately etched with seven " +
        "stars sparkling above the white tree of " +
        "Gondor. It looks like this helm would provide " +
        "strong protection for your head in battle.\n");
    
    set_at(A_HEAD);
    set_ac(38);
    
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
    add_prop(GONDOR_M_RANGERS_NO_SELL,1);   
}
