#include "../guild.h"
#include <wa_types.h>

inherit GUILD_OBJ + "rack";

void
create_rack()
{
    add_adj(({"miscellaneous", "misc"}));
    add_name("rack_misc");
    set_short("miscellaneous rack");
}
