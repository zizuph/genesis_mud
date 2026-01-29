/*
 * A torch
 *
 * Made by Nick
 */

inherit "/std/torch";

#include <macros.h>

/*
 * Function name: create_object
 * Description:   The standard create routine.
 */
void
create_torch()
{
    set_name("torch");
    set_pname("torches");	   /* The plural name. */
   set_adj("large");
   set_long("A large torch that seems as though it could work fairly well.\n");
   set_strength(4);
   set_short("large torch");
   set_pshort("large torches");
   add_name("_vladimir_shop_");
}

