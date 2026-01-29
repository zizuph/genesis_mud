/* Navarre July 3rd 2006, fixed typo */

inherit "/std/object";
#include "local.h"
#include <stdproperties.h>

void
create_object()
{
    set_name("ticket");
    add_name(TICKET_NAME);
    add_adj("tattered");
    add_adj("leather");
    set_long("It is just a piece of leather with few marks on it. " +
      "It might work as a ticket for some minotaur ship.\n");
    add_prop(OBJ_I_VALUE, 17);
}
