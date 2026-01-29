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
    set_amount(100);
    set_name("noodles");
    set_pname("noodles");
    set_adj(({"black"}));
    set_short("black noodles");
    set_pshort("black noodles");
    set_long("A bowl of noodles flavoured with the ink of a giant " +
        "squid, giving it a rich briny flavour with the faint hint " +
        "of sea saltiness.\n");
}

