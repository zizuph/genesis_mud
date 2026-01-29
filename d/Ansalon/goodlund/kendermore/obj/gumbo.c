/* Rabbit gumbo for Kendermore, Gwyneth, May 1999 */

inherit "/std/food";
#include "/sys/stdproperties.h"

void
create_food()
{
    set_name("gumbo");
    add_name("bowl");
    set_pname("gumbos");
    add_pname("bowls");
    set_adj("rabbit");
    set_short("bowl of rabbit gumbo");
    set_pshort("bowls of rabbit gumbo");
    set_long("A steamy hot bowl of rabbit gumbo.\n");
    set_amount(150);
}
