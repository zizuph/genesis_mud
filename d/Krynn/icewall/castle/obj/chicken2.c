/* A stuffed and baked chicken -- Kessie */

inherit "/std/food";
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

create_food()
{
    set_name("chicken");
    add_name("icestuffed chicken");
    add_adj("stuffed");
    add_adj("baked");
    set_short("stuffed and baked chicken");
    set_pshort("stuffed and baked chickens");
    set_long("This chicken has been stuffed with potatoe mash, herbs, " +
             "and breadcrumbs and then baked in a hot oven. It smells " +
             "delicious, better eat while it is still hot!\n");
    set_amount(256);
}

consume_text(object * arr, string vb) 
{
    write("You bite into the stuffed and baked chicken, tearing it apart " +
          "with bare hands! "
	  + "\nAhhh. . .  Finger-licking good!\n");
    say(QCTNAME(TP)+" devours a stuffed and baked chicken like a pig.\n");
}
