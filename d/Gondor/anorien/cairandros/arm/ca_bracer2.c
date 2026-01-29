/*
 * /d/Gondor/anorien/cairandros/arm/bracer.2c
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
    set_name("bracers");
    add_name("armour");
    set_pname("pairs of black iron bracers");
    set_short("black iron bracers");
    set_adj("black");
    add_adj("iron");
    set_long("These bracers has been forged from black " +
        "iron by the smiths of Gondor. It looks like " +
        "they would offer good protection to your arms " +
        "in battle.\n");
    
    set_at(A_ARMS);
    set_ac(33);
    
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
    add_prop(GONDOR_M_RANGERS_NO_SELL,1);   
}
