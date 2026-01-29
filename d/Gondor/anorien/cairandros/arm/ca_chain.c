/*
 * /d/Gondor/anorien/cairandros/arm/ca_chain.c
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
    set_short("heavy steel chainmail");
    set_adj("heavy");
    add_adj("steel");
    set_long("This heavy suit of chainmail has been crafted " +
        "by linking together hundreds of small steel rings. " +
        "It is clearly the work of the finest smiths in " +
        "Gondor, and it looks like it would give you " +
        "very good protection.\n");
    
    set_at(A_BODY);
    set_ac(38);
    
    add_prop(GONDOR_M_TIRITH_NO_SELL,1);
    add_prop(GONDOR_M_RANGERS_NO_SELL,1);   
}
