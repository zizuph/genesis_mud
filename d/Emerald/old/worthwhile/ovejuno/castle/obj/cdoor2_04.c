/* Basic door with lock, coded by Shiva. Used by Marisol
 * (02/25/99) in the Castle at Ovejuno in Emerald. */

#include "../../defs.h"

inherit CASTLE_DOOR2;

void
create_castle_door()
{
    set_long("A plain-looking black door.\n");
    set_adj(({ "plain-looking", "black" }));
}

public mixed
query_key_id()
{
    return "NONE";
}
