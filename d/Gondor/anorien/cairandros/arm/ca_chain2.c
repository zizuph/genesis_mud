/*
 * /d/Gondor/anorien/cairandros/arm/ca_chain2.c
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
    set_name("chainmail");
    add_name("armour");
    set_short("black iron chainmail");
    set_adj("black");
    add_adj("iron");
    set_long("This heavy suit of chainmail has been " +
        "crafted by the smiths of Gondor. Forged from " +
        "hundreds of black iron links, it looks " +
        "like it would give good protection in combat.\n");
    
    set_at(A_BODY);
    set_ac(33);
    
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
    add_prop(GONDOR_M_RANGERS_NO_SELL,1);   
}
