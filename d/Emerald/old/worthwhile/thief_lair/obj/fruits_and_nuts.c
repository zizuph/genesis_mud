/* Nuts and fruits, found in quantity in 
   Code (c) 1999 to Damian Horton (BKA Casimir)
*/

inherit "/std/food";

#include <stdproperties.h>

create_food()
{
    set_name("handful");
    add_name("nuts");
    add_name("dried fruits");
    set_adj("handful");
    add_adj("dried");
    set_short("handful of dried fruits and nuts");
    set_long("A large handful of dried fruits and assorted nuts. Perfect "+
	     "for snacking on during an arduous journey.\n");

    set_amount(75); 
    add_prop(OBJ_I_WEIGHT, 75);  
    add_prop(OBJ_I_VOLUME, 25);
}





