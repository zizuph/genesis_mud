inherit "/std/armour";

#include "../default.h"
#include <macros.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("overalls");
    set_short("blue overalls");
    add_adj("blue");
    set_long("These overalls are quite baggy and seem to have "+
       "tons of legroom as well as some very fashionable flower "+
       "stains and torn knees in them.\n");
    set_ac(13);
    set_at(A_ROBE);
}

string
query_recover()
{
    return MASTER;
}
