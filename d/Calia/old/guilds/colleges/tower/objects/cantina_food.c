
/*
    A generic food item for the cantina in the Marble Tower.
    
    Bishop, July 2003.
    
*/

inherit "/std/food";

#include <stdproperties.h>

create_food() 
{
   set_name("generic_food");
   set_long("This meal is surprisingly generic.\n");
   add_prop(OBJ_I_VALUE, 0);
   set_amount(500);
}

public string
query_recover()
{
    return 0;
}
   
 