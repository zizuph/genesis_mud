/*
 * Clyptas - July 2017
 */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

void
create_armour()
{ 

    set_name("vest");

    add_name("vest");

    set_short("ornate laced vest");

    set_adj("ornate");

    add_adj("laced");

    set_long("This vest is laced loosley, covered in a black beaded brocade " +
        "it looks simple, but the designs and webs woven throughout it give " +
		"the notion that much time and thought went into this.\n");
    
    set_at(A_CHEST);

    set_ac(20);

}