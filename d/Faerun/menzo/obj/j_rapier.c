/*
 * Clyptas - 2017
 */

inherit "/std/weapon";

#include <wa_types.h>
#include <formulas.h>        
#include <stdproperties.h>

void
create_weapon()
{

    set_name("rapier");

    add_name("sword");

    set_short("long gold rapier");

    set_adj("long");

    add_adj("gold");

    set_long("This ornate rapier has been crafted by a skilled smith. The blade " +
        "is slighty flexible, mirror polished and the pommel is perfectly " +
		"balanced.\n");
    	    
    set_wt(W_SWORD);

    set_dt(W_IMPALE);

    set_hands(W_ANYH);

    set_hit(20);

    set_pen(20);
}