/* Mulberry pie from Kendermore, Gwyneth, June 1999 */

inherit "/std/food";
#include <stdproperties.h>

void
create_food()
{
    set_name("pie");
    set_pname("pies");
    set_adj("mulberry");
    add_adj("baked");
    set_short("piece of mulberry pie");
    set_pshort("pieces of mulberry pie");
    set_long("A piece of freshly baked mulberry pie! \n");
    set_amount(75);
}

