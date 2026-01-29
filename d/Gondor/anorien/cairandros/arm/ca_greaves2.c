/*
 * /d/Gondor/anorien/cairandros/arm/ca_greaves2.c
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
    set_name("greaves");
    add_name("armour");
    set_short("black iron greaves");
    set_pname("pairs of black iron greaves");
    set_adj("black");
    add_adj("iron");
    set_long("These greaves has been forged from black " +
        "iron by the smiths of Gondor. It looks like " +
        "they would offer good protection to your legs " +
        "in battle.\n");
    
    set_at(A_LEGS);
    set_ac(33);
    
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
    add_prop(GONDOR_M_RANGERS_NO_SELL,1);   
}
