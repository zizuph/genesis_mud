/*
 * /d/Gondor/anorien/cairandros/arm/ca_helm2.c
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
    set_short("black iron helmet");
    set_adj("black");
    add_adj("iron");
    set_long("This helmet has been forged from black " +
        "iron by the smiths of Gondor. It looks like " +
        "it would offer good protection in battle.\n");
    
    set_at(A_HEAD);
    set_ac(33);
    
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
    add_prop(GONDOR_M_RANGERS_NO_SELL,1);   
}
