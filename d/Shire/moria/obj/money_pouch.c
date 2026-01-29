/*
 * Money pouch by Altrus, July 2005
 *
 * Adapted for use with money.h by Mercade.
 */

inherit "/std/container";

#include <stdproperties.h>
#include <money.h>

void
create_container()
{
    set_name("pouch");
    set_adj("ragged");
    set_adj("leather");
    set_short("ragged leather pouch");
    set_pshort("ragged leather pouches");
    set_long("This leather pouch doesn't look that well taken care of, but it still seems capable of holding things. It isn't large though, so it probably wouldn't hold much.\n");
    
    add_prop(CONT_I_WEIGHT,      500); 	
    add_prop(CONT_I_VOLUME,     2000);
    add_prop(CONT_I_MAX_WEIGHT, 2500); 	
    add_prop(CONT_I_MAX_VOLUME, 4000);
    add_prop(OBJ_I_VALUE,        150);

    setuid(); seteuid(getuid());
    MONEY_MAKE_HERE_GC(100 + random(25));
    MONEY_MAKE_HERE_PC(25 + random(10));
}
