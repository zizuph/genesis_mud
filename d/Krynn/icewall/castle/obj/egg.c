/* A piece of hardboiled egg -- Kessie */

inherit "/std/food";
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>

create_food()
{
    set_name("egg");
    add_name("iceegg");
    set_short("hardboiled egg");
    set_pshort("hardboiled eggs");
    set_long("This egg has been hardboiled in water. It is a perfect " +
             "snack for a long journey, and one that won't rot quickly.\n");
    set_amount(60);
}

consume_text(object * arr, string vb) 
{
    write("You break and discard the shell, biting into the delicious egg inside. "
	  + "\nAhhh. . .  Finger-licking good!\n");
    say(QCTNAME(TP)+" devours a hardboiled egg like a pig.\n");
}
