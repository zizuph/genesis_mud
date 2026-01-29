/* A piece of fried chicken -- created by Stevenson */

inherit "/std/food";
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

create_food()
{
    set_name("chicken");
    add_name("icechicken");
    set_short("piece of chicken");
    set_pshort("pieces of chicken");
    set_long("It is a juicy piece of deepfried chicken. "
	     + "Don't worry though, it was cooked in canola oil.\n");
    set_amount(123);
}

consume_text(object * arr, string vb) 
{
    write("You eat some juicy fried chicken, bones and all. "
	  + "\nAhhh. . .  Finger-licking good!\n");
    say(QCTNAME(TP)+" devours a piece of chicken like a pig.\n");
}
