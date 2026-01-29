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
    set_amount(210);
    set_name("platter");
    set_pname("platters");
    set_adj(({"fish"}));
    set_short("fish platter");
    set_pshort("fish platters");
    set_long("A plate of fish meats, ranging from Balifor bonito " +
        "to the Bloodsea barracuda, lightly cooked in lemon juice.\n");
}

