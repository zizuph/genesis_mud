/*
 * Clyptas - 2017
 */

inherit "/std/weapon";

#include <wa_types.h>
#include <formulas.h>        
#include <stdproperties.h>

#define HIT /*hit value*/
#define PEN /*penetration value*/

void
create_weapon()
{

    set_name("scimitar");

    add_name("sword");

    set_short("scimitar with a long, curved single edged blade.");
	
    set_adj("long");

    add_adj("gold");

    set_long("A cruel looking sword with a curved blade, made of " +
	     "adamantine metal.\n");
    	    
    set_wt(W_SWORD);

    set_dt(W_IMPALE);

    set_hands(W_ANYH);

    set_hit(30);

    set_pen(21);
	
	
}