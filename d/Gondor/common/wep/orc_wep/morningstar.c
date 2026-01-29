/* Weapon coded by Arren, April 94 */ 

inherit "/std/weapon";
inherit "/lib/keep.c";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("morning-star");
    add_name(({ "club", "morningstar", "star" }));
    set_pname("morning-stars");
    add_pname("clubs");
    add_pname("morningstars");
    add_pname("stars");
    set_adj(({ "orc", "nine-spiked", "nine", "spiked", "morning", }));
    set_short("nine-spiked morning-star"); 
    set_long(BSN("A wooden handle with a chain and a ball, with nine "+
    "large vicious spikes, fastened to the chain."));

    set_default_weapon(24, 27, W_CLUB, W_BLUDGEON, W_ANYH, 0);
    
    add_prop(OBJ_I_VOLUME, 1100);  
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(24,27)+random(150)-75);
}
