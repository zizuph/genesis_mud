/*
 * /d/Gondor/anorien/cairandros/arm/ca_shield.c
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
    set_name("shield");
    add_name("armour");
    set_short("strong Gondorian shield");
    set_adj("strong");
    add_adj("gondorian");
    set_long("This wooden shield has been rimmed " +
        "with bright steel while proudly displaying " +
        "the seven stars above the white tree of " +
        "Gondor painted on the face.\n");
    
    set_at(A_SHIELD);
    set_ac(39);
    
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
    add_prop(GONDOR_M_RANGERS_NO_SELL,1);   
}
