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
    set_amount(10);
    set_name("stick");
    set_pname("sticks");
    set_adj(({"fried", "crab"}));
    set_short("fried crab stick");
    set_pshort("fried crab sticks");
    set_long("The famous Bishon lightly fried crab sticks. " +
        "Cheap seafood goodness. You could literally eat " +
        "hundreds of these babies.\n");
}

