/* Arman March 2021
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>
#include "../../local.h"

public void
create_food()
{
    set_amount(70);
    set_name("soup");
    set_pname("soups");
    set_adj(({"shark", "fin"}));
	set_short("shark fin soup");
    set_pshort("shark fin soups");
    set_long("A seafood broth containing shredded shark fin and " +
        "crab meat.\n");
}

